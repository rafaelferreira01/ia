#include "Marker.h"

#include <vector>

#include "Input.h"
#include "InventoryHandling.h"
#include "Input.h"
#include "ActorPlayer.h"
#include "Attack.h"
#include "Log.h"
#include "Look.h"
#include "Throwing.h"
#include "Renderer.h"
#include "Map.h"
#include "ItemFactory.h"
#include "LineCalc.h"
#include "Utils.h"
#include "Config.h"

using namespace std;

namespace Marker {

namespace {

Pos pos_;

void setPosToClosestEnemyIfVisible() {
  vector<Actor*> spottedEnemies;
  Map::player->getSpottedEnemies(spottedEnemies);
  vector<Pos> spottedEnemiesPositions;

  Utils::getActorPositions(spottedEnemies, spottedEnemiesPositions);

  //If player sees enemies, suggest one for targeting
  if(!spottedEnemiesPositions.empty()) {
    pos_ = Utils::getClosestPos(Map::player->pos, spottedEnemiesPositions);

    Map::player->target = Utils::getFirstActorAtPos(pos_);
  }
}

void tryMove(const Dir dir) {
  const Pos newPos(pos_ + DirUtils::getOffset(dir));
  if(Utils::isPosInsideMap(newPos)) {pos_ = newPos;}
}

bool setPosToTargetIfVisible() {
  const Actor* const target = Map::player->target;

  if(target) {
    vector<Actor*> spottedEnemies;
    Map::player->getSpottedEnemies(spottedEnemies);

    if(!spottedEnemies.empty()) {
      for(auto* const actor : spottedEnemies) {
        if(target == actor) {
          pos_ = actor->pos;
          return true;
        }
      }
    }
  }
  return false;
}

} //namespace

void run(const MarkerDrawTail drawTrail, const MarkerUsePlayerTarget useTarget,
         function<void(const Pos&)> onMarkerAtPos,
         function<MarkerDone(const Pos&, const KeyData&)> onKeyPress) {

  pos_ = Map::player->pos;

  if(useTarget == MarkerUsePlayerTarget::yes) {
    //First, attempt to place marker at target.
    if(!setPosToTargetIfVisible()) {
      //If no target available, attempt to place marker at closest visible monster.
      //This sets a new target if successful.
      Map::player->target = nullptr;
      setPosToClosestEnemyIfVisible();
    }
  }

  MarkerDone isDone = MarkerDone::no;

  while(isDone == MarkerDone::no) {
    Log::clearLog();

    //Print info such as name of actor at current position, etc.
    onMarkerAtPos(pos_);

    Renderer::drawMapAndInterface(false);

    vector<Pos> trail;

    if(drawTrail == MarkerDrawTail::yes) {
      const Pos origin(Map::player->pos);
      LineCalc::calcNewLine(origin, pos_, true, INT_MAX, false, trail);
    }

    Renderer::drawMarker(pos_, trail, INT_MAX);

    Renderer::updateScreen();

    const KeyData& d = Input::readKeysUntilFound();

    if(d.sdlKey == SDLK_RIGHT    || d.key == '6' || d.key == 'l') {
      if(d.isShiftHeld) {
        tryMove(Dir::upRight);
      } else if(d.isCtrlHeld) {
        tryMove(Dir::downRight);
      } else {
        tryMove(Dir::right);
      }
      continue;
    }
    if(d.sdlKey == SDLK_UP       || d.key == '8' || d.key == 'k') {
      tryMove(Dir::up);
      continue;
    }
    if(d.sdlKey == SDLK_LEFT     || d.key == '4' || d.key == 'h') {
      if(d.isShiftHeld) {
        tryMove(Dir::upLeft);
      } else if(d.isCtrlHeld) {
        tryMove(Dir::downLeft);
      } else {tryMove(Dir::left);}
      continue;
    }
    if(d.sdlKey == SDLK_DOWN     || d.key == '2' || d.key == 'j') {
      tryMove(Dir::down);
      continue;
    }
    if(d.sdlKey == SDLK_PAGEUP   || d.key == '9' || d.key == 'u') {
      tryMove(Dir::upRight);
      continue;
    }
    if(d.sdlKey == SDLK_HOME     || d.key == '7' || d.key == 'y') {
      tryMove(Dir::upLeft);
      continue;
    }
    if(d.sdlKey == SDLK_END      || d.key == '1' || d.key == 'b') {
      tryMove(Dir::downLeft);
      continue;
    }
    if(d.sdlKey == SDLK_PAGEDOWN || d.key == '3' || d.key == 'n') {
      tryMove(Dir::downRight);
      continue;
    }

    //Run custom keypress events (firing ranged weapon, casting spell, etc)
    isDone = onKeyPress(pos_, d);

    if(isDone == MarkerDone::yes) {
      Renderer::drawMapAndInterface();
    }
  }
}

} //Marker

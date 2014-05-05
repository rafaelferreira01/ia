#include "MapGen.h"

#include <vector>

#include "ActorPlayer.h"
#include "FeatureFactory.h"
#include "ActorFactory.h"
#include "ActorMonster.h"
#include "Map.h"
#include "FeatureWall.h"
#include "Utils.h"
#include "ActorFactory.h"

using namespace std;

namespace MapGen {

namespace EgyptTomb {

bool run() {
  Map::resetMap();

  MapGenUtils::buildFromTemplate(Pos(0, 0), MapTemplateId::pharaohsChamber);

  Map::player->pos = Pos(40, 11);

  for(int y = 0; y < MAP_H; y++) {
    for(int x = 0; x < MAP_W; x++) {
      Feature* const f = Map::cells[x][y].featureStatic;
      if(f->getId() == FeatureId::wall) {
        dynamic_cast<Wall*>(f)->wallType = WallType::egypt;
      }
    }
  }

  if(Rnd::coinToss()) {
    FeatureFactory::spawn(FeatureId::stairs, Pos(4, 2), NULL);
  } else {
    FeatureFactory::spawn(FeatureId::stairs, Pos(4, 19), NULL);
  }


  vector<Actor*> actors;

  actors.push_back(ActorFactory::spawn(actor_mummy,     Pos(12, 10)));
  actors.push_back(ActorFactory::spawn(actor_khephren,  Pos(11, 11)));
  actors.push_back(ActorFactory::spawn(actor_mummy,     Pos(12, 12)));
  actors.push_back(ActorFactory::spawn(actor_cultist,   Pos(17, 10)));
  actors.push_back(actorFactory::spawn(actor_cultist,   Pos(17, 12)));

  for(Actor * a : actors) {dynamic_cast<Monster*>(a)->isRoamingAllowed_ = true;}

  return true;
}

} //EgyptTomb

} //MapGen

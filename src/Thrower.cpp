#include "Thrower.h"

#include "Engine.h"

#include "Item.h"
#include "ItemPotion.h"
#include "ActorData.h"
#include "ActorPlayer.h"
#include "Renderer.h"
#include "Map.h"
#include "Log.h"
#include "FeatureFactory.h"
#include "Explosion.h"
#include "ItemDrop.h"
#include "Inventory.h"
#include "ItemFactory.h"
#include "Attack.h"
#include "LineCalc.h"

void Thrower::playerThrowLitExplosive(const Pos& aimCell) {
  const int DYNAMITE_FUSE = eng.player->dynamiteFuseTurns;
  const int FLARE_FUSE = eng.player->flareFuseTurns;

  eng.player->explosiveThrown();

  vector<Pos> path;
  eng.lineCalc->calcNewLine(eng.player->pos, aimCell, true,
                             THROWING_RANGE_LIMIT, false, path);

  //Remove cells after blocked cells
  for(unsigned int i = 1; i < path.size(); i++) {
    const Pos curPos = path.at(i);
    const Feature* featureHere =
      eng.map->cells[curPos.x][curPos.y].featureStatic;
    if(featureHere->isProjectilesPassable() == false) {
      path.resize(i);
      break;
    }
  }

  //Render
  if(path.size() > 1) {
    const char glyph = eng.itemDataHandler->dataList[item_dynamite]->glyph;
    SDL_Color clr = DYNAMITE_FUSE != -1 ? clrRedLgt : clrYellow;
    for(unsigned int i = 1; i < path.size() - 1; i++) {
      eng.renderer->drawMapAndInterface(false);
      if(eng.map->cells[path[i].x][path[i].y].isSeenByPlayer) {
        eng.renderer->drawGlyph(glyph, panel_map, path[i], clr);
        eng.renderer->updateScreen();
        eng.sleep(eng.config->delayProjectileDraw);
      }
    }
  }

  Feature* const featureAtDest =
    eng.map->cells[path.back().x][path.back().y].featureStatic;
  const bool IS_DEST_FEAT_BOTTOMLESS = featureAtDest->isBottomless();

  if(DYNAMITE_FUSE != -1) {
    eng.log->addMsg("I throw a lit dynamite stick.");
    if(IS_DEST_FEAT_BOTTOMLESS == false) {
      eng.featureFactory->spawnFeatureAt(
        feature_litDynamite, path.back(),
        new DynamiteSpawnData(DYNAMITE_FUSE));
    }
  } else if(FLARE_FUSE != -1) {
    eng.log->addMsg("I throw a lit flare.");
    if(IS_DEST_FEAT_BOTTOMLESS == false) {
      eng.featureFactory->spawnFeatureAt(
        feature_litFlare, path.back(), new DynamiteSpawnData(FLARE_FUSE));
    }
    eng.gameTime->updateLightMap();
    eng.player->updateFov();
    eng.renderer->drawMapAndInterface();
  } else {
    eng.log->addMsg("I throw a lit Molotov Cocktail.");
    if(IS_DEST_FEAT_BOTTOMLESS == false) {
      eng.explosionMaker->runExplosion(
        path.back(), sfxExplosionMolotov, false,
        new PropBurning(eng, propTurnsStandard));
    }
  }

  eng.gameTime->actorDidAct();
}

void Thrower::throwItem(Actor& actorThrowing, const Pos& targetCell,
                        Item& itemThrown) {
  MissileAttackData* data = new MissileAttackData(
    actorThrowing, itemThrown, targetCell, actorThrowing.pos, eng);

  const ActorSizes_t aimLevel = data->intendedAimLevel;

  vector<Pos> path;
  eng.lineCalc->calcNewLine(actorThrowing.pos, targetCell, false,
                             THROWING_RANGE_LIMIT, false, path);

  const ItemData& itemThrownData = itemThrown.getData();

  const string itemName_a =
    eng.itemDataHandler->getItemRef(itemThrown, itemRef_a, true);
  if(&actorThrowing == eng.player) {
    eng.log->clearLog();
    eng.log->addMsg("I throw " + itemName_a + ".");
  } else {
    const Pos& p = path.front();
    if(eng.map->cells[p.x][p.y].isSeenByPlayer) {
      eng.log->addMsg(
        actorThrowing.getNameThe() + " throws " + itemName_a + ".");
    }
  }
  eng.renderer->drawMapAndInterface(true);

  int blockedInElement = -1;
  bool isActorHit = false;

  const char glyph = itemThrown.getGlyph();
  const SDL_Color clr = itemThrown.getColor();

  int chanceToDestroyItem = 0;

  Pos curPos(-1, -1);

  for(unsigned int i = 1; i < path.size(); i++) {
    eng.renderer->drawMapAndInterface(false);

    curPos.set(path.at(i));

    Actor* const actorHere = eng.basicUtils->getActorAtPos(curPos);
    if(actorHere != NULL) {
      if(
        curPos == targetCell ||
        actorHere->getData().actorSize >= actorSize_humanoid) {

        delete data;
        data = new MissileAttackData(actorThrowing, itemThrown, targetCell,
                                     curPos, eng, aimLevel);

        if(
          data->attackResult >= successSmall &&
          data->isEtherealDefenderMissed == false) {
          if(eng.map->cells[curPos.x][curPos.y].isSeenByPlayer) {
            eng.renderer->drawGlyph('*', panel_map,
                                     curPos, clrRedLgt);
            eng.renderer->updateScreen();
            eng.sleep(eng.config->delayProjectileDraw * 4);
          }
          const SDL_Color hitMessageClr =
            actorHere == eng.player ? clrMessageBad : clrMessageGood;
          eng.log->addMsg(
            actorHere->getNameThe() + " is hit.", hitMessageClr);
          actorHere->hit(data->dmg, dmgType_physical, true);
          isActorHit = true;

          //If throwing a potion on an actor, let it make stuff happen...
          if(itemThrownData.isPotion) {
            dynamic_cast<Potion*>(&itemThrown)->collide(curPos, actorHere);
            delete &itemThrown;
            delete data;
            eng.gameTime->actorDidAct();
            return;
          }

          blockedInElement = i;
          chanceToDestroyItem = 25;
          break;
        }
      }
    }

    if(eng.map->cells[curPos.x][curPos.y].isSeenByPlayer) {
      eng.renderer->drawGlyph(glyph, panel_map, curPos, clr);
      eng.renderer->updateScreen();
      eng.sleep(eng.config->delayProjectileDraw);
    }

    const Feature* featureHere =
      eng.map->cells[curPos.x][curPos.y].featureStatic;
    if(featureHere->isProjectilesPassable() == false) {
      blockedInElement = itemThrownData.isPotion ? i : i - 1;
      break;
    }

    if(curPos == targetCell) {
      blockedInElement = i;
      break;
    }
  }

  //If potion, collide it on the landscape
  if(itemThrownData.isPotion) {
    if(blockedInElement >= 0) {
      dynamic_cast<Potion*>(&itemThrown)->collide(
        path.at(blockedInElement), NULL);
      delete &itemThrown;
      delete data;
      eng.gameTime->actorDidAct();
      return;
    }
  }

  if(eng.dice.percentile() < chanceToDestroyItem) {
    delete &itemThrown;
  } else {
    const int DROP_ELEMENT = blockedInElement == -1 ?
                             path.size() - 1 : blockedInElement;
    const Pos dropPos = path.at(DROP_ELEMENT);
    const MaterialType_t materialAtDropPos =
      eng.map->cells[dropPos.x][dropPos.y].featureStatic->getMaterialType();
    if(materialAtDropPos == materialType_hard) {
      const bool IS_ALERTING_MONSTERS = &actorThrowing == eng.player;
      if(isActorHit == false) {
        Sound snd(itemThrownData.landOnHardSurfaceSoundMsg,
                  itemThrownData.landOnHardSurfaceSfx, true, dropPos, false,
                  IS_ALERTING_MONSTERS);
        eng.soundEmitter->emitSound(snd);
      }
    }
    eng.itemDrop->dropItemOnMap(dropPos, itemThrown);
  }

  delete data;
  eng.renderer->drawMapAndInterface();
  eng.gameTime->actorDidAct();
}

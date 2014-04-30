#ifndef ATTACK_H
#define ATTACK_H

#include <vector>
#include <math.h>
#include <iostream>

#include "AbilityValues.h"
#include "ItemData.h"
#include "ActorData.h"
#include "Art.h"

class Actor;
class Weapon;

class AttData {
public:
  Actor* attacker;
  Actor* curDefender;
  AbilityRollResult attackResult;
  int dmgRolls, dmgSides, dmgPlus;
  int dmgRoll, dmg;
  bool isIntrinsicAttack;
  bool isEtherealDefenderMissed;

protected:
  AttData(Actor& attacker_, const Item& itemAttackedWith_);
};

class MeleeAttData: public AttData {
public:
  MeleeAttData(Actor& attacker_, const Weapon& wpn_,
               Actor& defender_);
  bool isDefenderDodging;
  bool isBackstab;
  bool isWeakAttack;

};

class RangedAttData: public AttData {
public:
  RangedAttData(Actor& attacker_, const Weapon& wpn_, const Pos& aimPos_,
                const Pos& curPos_,
                ActorSize intendedAimLevel_ = actorSize_none);
  int           hitChanceTot;
  ActorSize  intendedAimLevel;
  ActorSize  curDefenderSize;
  std::string        verbPlayerAttacks;
  std::string        verbOtherAttacks;
};

class MissileAttData: public AttData {
public:
  MissileAttData(Actor& attacker_, const Item& item_, const Pos& aimPos_,
                 const Pos& curPos_,
                 ActorSize intendedAimLevel_ = actorSize_none);
  int       hitChanceTot;
  ActorSize intendedAimLevel;
  ActorSize curDefenderSize;
};

struct Projectile {
  Projectile() : pos(Pos(-1, -1)), isObstructed(false),
    isVisibleToPlayer(true), actorHit(NULL), obstructedInElement(-1),
    isDoneRendering(false), glyph(-1), tile(tile_empty), clr(clrWhite),
    attackData(NULL) {}

  ~Projectile() {if(attackData != NULL) {delete attackData;}}

  void setAttData(RangedAttData* attackData_) {
    if(attackData != NULL) {delete attackData;}
    attackData = attackData_;
  }

  void setTile(const TileId tileToRender, const SDL_Color clrToRender) {
    tile = tileToRender;
    clr = clrToRender;
  }

  void setGlyph(const char GLYPH_TO_RENDER, const SDL_Color clrToRender) {
    glyph = GLYPH_TO_RENDER;
    clr = clrToRender;
  }

  Pos pos;
  bool isObstructed;
  bool isVisibleToPlayer;
  Actor* actorHit;
  int obstructedInElement;
  bool isDoneRendering;
  char glyph;
  TileId tile;
  SDL_Color clr;
  RangedAttData* attackData;
};

enum class MeleeHitSize {small, medium, hard};

namespace Attack {

void melee(Actor& attacker, const Weapon& wpn, Actor& defender);

bool ranged(Actor& attacker, Weapon& wpn, const Pos& aimPos);

void getRangedHitChance(const Actor& attacker, const Actor& defender,
                        const Weapon& wpn);

} //Attack

#endif


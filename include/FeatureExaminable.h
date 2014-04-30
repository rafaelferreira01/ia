#ifndef FEATURE_EXAMINABLE_H
#define FEATURE_EXAMINABLE_H

#include "Feature.h"

#include "FeatureDoor.h"

class Item;

class ItemContainerFeature {
public:
  ItemContainerFeature();

  ~ItemContainerFeature();

  void setRandomItemsForFeature(const FeatureId featureId,
                                const int NR_ITEMS_TO_ATTEMPT);

  void dropItems(const Pos& pos);

  void destroySingleFragile();

  std::vector<Item*> items_;
};

enum class TombTrait {
  stench,                 //Fumes, Ooze-type monster
  auraOfUnrest,           //Ghost-type monster
  forebodingCarvedSigns,  //Cursed
  endOfTombTraits
};

enum class TombAppearance {
  common,
  ornate,     //Good items
  marvelous,  //Excellent items
  endOfTombAppearance
};

class Tomb: public FeatureStatic {
public:
  Tomb(FeatureId id, Pos pos);

  void bump(Actor& actorBumping)  override;
  bool open()                     override;
  void examine()                  override;

  std::string getDescr(const bool DEFINITE_ARTICLE)  const override;
  SDL_Color getClr()                            const override;

private:
  void triggerTrap(Actor& actor) override;

  void trySprainPlayer();

  bool isContentKnown_, isTraitKnown_;

  ItemContainerFeature itemContainer_;

  int pushLidOneInN_;
  TombAppearance appearance_;
  TombTrait trait_;
};

enum ChestMtrl {
  chestMtrl_wood,
  chestMtrl_iron,
  endOfChestMaterial
};

class Chest: public FeatureStatic {
public:
  Chest(FeatureId id, Pos pos);
  ~Chest() {}

  void bump(Actor& actorBumping)  override;
  bool open()                     override;
  void examine()                  override;
  void bash(Actor& actorTrying)   override;
  void disarm()                   override;

  SDL_Color getClr() const override {
    return material == chestMtrl_wood ? clrBrownDrk : clrGray;
  }

  std::string getDescr(const bool DEFINITE_ARTICLE) const override {
    const std::string a = DEFINITE_ARTICLE ?
                     "the " : (material == chestMtrl_wood ? "a " : "an ");

    return a + (material == chestMtrl_wood ? "wooden " : "iron ") + "chest";
  }

private:
  void triggerTrap(Actor& actor) override;

  void trySprainPlayer();

  ItemContainerFeature itemContainer_;

  bool isContentKnown_;
  bool isLocked_, isTrapped_, isTrapStatusKnown_;
  ChestMtrl material;
};

class Cabinet: public FeatureStatic {
public:
  Cabinet(FeatureId id, Pos pos);
  ~Cabinet() {}

  void bump(Actor& actorBumping) override;
  bool open()                     override;

private:
  ItemContainerFeature itemContainer_;
  bool isContentKnown_;
};

enum class FountainType {
  dry, //This must be at first position!
  tepid,
  refreshing,
  bless,
  curse,
  spirit,
  vitality,
  disease,
  poison,
  frenzy,
  paralyze,
  blind,
  faint,
  rFire,
  rCold,
  rElec,
  rFear,
  rConfusion,
  endOfFountainTypes
};

enum class FountainMaterial {stone, gold};

class Fountain: public FeatureStatic {
public:
  Fountain(FeatureId id, Pos pos);
  ~Fountain() {}

  void bump(Actor& actorBumping)                override;
  SDL_Color getClr()                            const override;
  std::string getDescr(const bool DEFINITE_ARTICLE)  const override;

private:
  FountainType fountainType_;
  FountainMaterial fountainMaterial_;
};

class Cocoon: public FeatureStatic {
public:
  Cocoon(FeatureId id, Pos pos);
  ~Cocoon() {}

  void bump(Actor& actorBumping)  override;
  bool open()                     override;

private:
  void triggerTrap(Actor& actor) override;

  bool isContentKnown_;

  ItemContainerFeature itemContainer_;
};

//class Altar: public FeatureStatic {
//};

//class CarvedPillar: public FeatureStatic {
//};

//class Barrel: public FeatureStatic {
//};

#endif

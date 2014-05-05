#include "PopulateTraps.h"

#include <algorithm>

#include "Map.h"
#include "MapGen.h"
#include "FeatureFactory.h"
#include "MapParsing.h"
#include "Utils.h"

using namespace std;

void PopulateTraps::populateRoomAndCorridorLevel() const {
  trace << "PopulateTraps::populateRoomAndCorridorLevel()..." << endl;

  bool blockers[MAP_W][MAP_H];
  MapParse::parse(CellPred::BlocksMoveCmn(false), blockers);

  //Put traps in non-plain rooms
  for(Room * const room : Map::rooms) {
    const RoomThemeId theme = room->roomTheme;

    if(theme != RoomThemeId::plain) {

      int chanceForTrappedRoom = 0;

      switch(theme) {
        case RoomThemeId::human:   chanceForTrappedRoom = 25; break;
        case RoomThemeId::ritual:  chanceForTrappedRoom = 25; break;
        case RoomThemeId::spider:  chanceForTrappedRoom = 75; break;
        case RoomThemeId::crypt:   chanceForTrappedRoom = 75; break;
        case RoomThemeId::monster: chanceForTrappedRoom = 25; break;
        case RoomThemeId::plain:                              break;
        case RoomThemeId::flooded:                            break;
        case RoomThemeId::muddy:                              break;
        case RoomThemeId::endOfRoomThemes:                    break;
      }

      if(Rnd::range(1, 100) < chanceForTrappedRoom) {
        trace << "PopulateTraps: Trapping non-plain room" << endl;

        vector<Pos> trapPosBucket;

        const Pos& x0y0 = room->getX0Y0();
        const Pos& x1y1 = room->getX1Y1();
        for(int y = x0y0.y; y <= x1y1.y; y++) {
          for(int x = x0y0.x; x <= x1y1.x; x++) {
            if(
              blockers[x][y] == false &&
              Map::cells[x][y].featureStatic->canHaveStaticFeature()) {
              trapPosBucket.push_back(Pos(x, y));
            }
          }
        }

        int nrPosCand = int(trapPosBucket.size());
        const bool IS_SPIDER_ROOM = theme == RoomThemeId::spider;
        const int NR_BASE_TRAPS = min(nrPosCand / 2, IS_SPIDER_ROOM ? 3 : 1);
        for(int i = 0; i < NR_BASE_TRAPS; i++) {
          if(nrPosCand == 0) {break;}

          const TrapId trapType = IS_SPIDER_ROOM ?
                                  trap_spiderWeb :
                                  TrapId(Rnd::range(0, int(endOfTraps) - 1));

          const int ELEMENT = Rnd::range(0, trapPosBucket.size() - 1);
          const Pos& pos = trapPosBucket.at(ELEMENT);

          trace << "PopulateTraps: Placing base trap" << endl;
          spawnTrapAt(trapType, pos);
          blockers[pos.x][pos.y] = true;
          trapPosBucket.erase(trapPosBucket.begin() + ELEMENT);
          nrPosCand--;

          //Spawn up to N traps in nearest cells (not necessarily adjacent)
          IsCloserToOrigin sorter(pos);
          sort(trapPosBucket.begin(), trapPosBucket.end(), sorter);
          const int NR_ADJ = min(Rnd::range(1, 3), nrPosCand);
          trace << "PopulateTraps: Placing adjacent traps" << endl;
          for(int i_adj = 0; i_adj < NR_ADJ; i_adj++) {
            const Pos& adjPos = trapPosBucket.front();
            spawnTrapAt(trapType, adjPos);
            blockers[adjPos.x][adjPos.y] = true;
            trapPosBucket.erase(trapPosBucket.begin());
            nrPosCand--;
          }
          trace << "PopulateTraps: Placing adjacent traps [DONE]" << endl;
        }
      }
    }
  }

  const int CHANCE_FOR_ALLOW_TRAPPED_PLAIN_AREAS =
    min(85, 30 + (Map::dlvl * 5));
  if(Rnd::percentile() < CHANCE_FOR_ALLOW_TRAPPED_PLAIN_AREAS) {
    trace << "PopulateTraps: Trapping plain room" << endl;

    vector<Pos> trapPosBucket;
    for(int y = 1; y < MAP_H - 1; y++) {
      for(int x = 1; x < MAP_W - 1; x++) {
        if(
          blockers[x][y] == false &&
          RoomThemeMaker::themeMap[x][y] == RoomThemeId::plain &&
          Map::cells[x][y].featureStatic->canHaveStaticFeature()) {
          trapPosBucket.push_back(Pos(x, y));
        }
      }
    }

    int nrPosCand = int(trapPosBucket.size());
    const int NR_BASE_TRAPS = min(nrPosCand / 2, Rnd::range(1, 3));
    for(int i = 0; i < NR_BASE_TRAPS; i++) {
      if(nrPosCand == 0) {break;}

      const TrapId trapType = TrapId(Rnd::range(0, int(endOfTraps) - 1));

      const int ELEMENT = Rnd::range(0, trapPosBucket.size() - 1);
      const Pos& pos = trapPosBucket.at(ELEMENT);

      trace << "PopulateTraps: Placing base trap" << endl;
      spawnTrapAt(trapType, pos);
      trapPosBucket.erase(trapPosBucket.begin() + ELEMENT);
      nrPosCand--;

      //Spawn up to N traps in nearest cells (not necessarily adjacent)
      IsCloserToOrigin sorter(pos);
      sort(trapPosBucket.begin(), trapPosBucket.end(), sorter);
      const int NR_ADJ = min(Rnd::range(1, 3), nrPosCand);
      trace << "PopulateTraps: Placing adjacent traps..." << endl;
      for(int i_adj = 0; i_adj < NR_ADJ; i_adj++) {
        const Pos& adjPos = trapPosBucket.front();
        spawnTrapAt(trapType, adjPos);
        trapPosBucket.erase(trapPosBucket.begin());
        nrPosCand--;
      }
      trace << "PopulateTraps: Placing adjacent traps [DONE]" << endl;
    }
  }
  trace << "PopulateTraps::populateRoomAndCorridorLevel() [DONE]" << endl;
}

void PopulateTraps::spawnTrapAt(const TrapId id, const Pos& pos) const {
  FeatureStatic* const f = Map::cells[pos.x][pos.y].featureStatic;
  const FeatureDataT* const d = FeatureData::getData(f->getId());
  FeatureFactory::spawn(FeatureId::trap, pos, new TrapSpawnData(d, id));
}

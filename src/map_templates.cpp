#include "map_templates.hpp"

#include "init.hpp"
#include "game_time.hpp"

#include <vector>

namespace map_templ_handling
{

namespace
{

MapTempl templates_[size_t(MapTemplId::END)];

MapTemplCell ch_to_cell(const char ch,
                          const std::vector<MapTemplCell>& prototypes)
{
    for (const MapTemplCell& proto : prototypes)
    {
        if (proto.ch == ch)
        {
            return proto;
        }
    }

    TRACE << "Failed to make map template cell from char: " <<  ch << std::endl;
    ASSERT(false);
    return MapTemplCell(0);
}

void mk_templ(const std::string& str,
              const MapTemplId id,
              const std::vector<MapTemplCell>& prototypes)
{
    MapTempl& templ = templates_[size_t(id)];

    std::vector<MapTemplCell> inner;

    for (const auto ch : str)
    {
        switch (ch)
        {
        case ';':
        {
            //Delimiting character (";") found, inner vector is pushed to outer
            templ.add_row(inner);
            inner.clear();
        }
        break;

        case ' ':
        {
            inner.push_back(MapTemplCell(0));
        }
        break;

        default:
        {
            MapTemplCell templ_cell = ch_to_cell(ch, prototypes);

            inner.push_back(templ_cell);
        }
        break;
        }
    }
}

void init_templs()
{
    //Blank level with correct dimensions to copy/paste when making new templates
//  "################################################################################;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "#..............................................................................#;"
//  "################################################################################;";

    //Filled version
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;"
//  "################################################################################;";

    //----------------------------------------------------------------- FOREST
    std::string str =
        "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt;"
        "tttttttttttttttttt,,,,,,,,,,tttttttt~~~~~~~~tttttttttt,,,tt,t,,t,,ttt,,ttttttttt;"
        "tttt,=,,,,ttttttt,,,,,t,,,,tttt~,~,~~~,,,~~~~,,~~ttttttt,,,,,,________,,,ttttttt;"
        "ttt,,,@,,,,,tttttt,,,,,,,,,,,,,,~,~~~,,t,,~,~~,,,,,,,,,,,,,,___________,,,,,,ttt;"
        "ttt,,,,=,,,,,tttttttt,,,,,,,,,,,,~~,~~,,,~~,~,,,,,,,,,,,,,_____######____,,ttttt;"
        "tt,,,,,,=,,,,tttttttttttt,,,,,,,,,~,~~,~~~,~,,,,,______________#....#_____,,,,tt;"
        "tt,,,,,,,=,t,tt,ttt,tttt,,,,,,,,,,,,,,,,,,,,,,,,_____________###....###____,,,tt;"
        "tttt,t,,,,=,,,,,,,,,t,,,,,,,,,,,,,,,,,,,,,,,,,,,__#####_#__#_#.#....#.#______,,t;"
        "tttttttt,,,========,,,,t,t,,,,,,,,,,,,,,,,,,t,,,__#...########.#....#.######_,tt;"
        "ttttttttt,,,,,,,,,,===,,tt,,,,,,,,,,,,,,,t,,,,,,__#...#...................##_,,t;"
        "ttttt,,ttttt,tt,tt,,,,=,,tt,,,,,,,,,tt,,,,,,&,&___#.#.#..[.[.[.[...[.[....>#_,tt;"
        "tt,,,,,,,,tttttttttt,,,=,,t,,tttt,,t,,,,,,,=======+...+*****************-..#_,tt;"
        "tttt,,,,,,,,,t,,,tttt,,&=,,,,,,ttt,ttt,,,,=,t,,___#.#.#..[.[.[.[...[.[.....#_,,t;"
        "ttttt,,,,,t,,,,,,,,,,,,,,=&,,,ttttttt,,,,=&,t,,,__#...#...................##_,tt;"
        "ttttt,,,,,,,t,,t,,,,,t,,,,=&,,,,tttttt,&=,,t,t,,__#...########.#....#.######_,tt;"
        "tttttt,,,t,,,,,,,,,,,,t,,,,=,t,ttt,tt,,=,,,tt,,,__#####_#__#_#,#....#.#_____,,,t;"
        "tttttt,,,,,,,,,tttt,,,,,,,,,===========,,,,ttt,,_____________###....###____,,ttt;"
        "tttttt,,,t,,,tttttt,,,,ttt,ttt,,t,t,,ttt,,,,t,,,,______________#....#_____,,,ttt;"
        "ttttttt,,,,,,,ttt,,,,,,,,tttt,,,,tt,t,,,,,,,,,,,,,,,,,,,,______######____,,,tttt;"
        "ttttttt,ttt,tttt,,,,,,,,,,,tttt,,,,tt,,,,tt,,t,,,,,,,,,,,,,,___________,,,t,,,tt;"
        "ttttttttttttttttt,,,t,,,ttttttttt,,,,,,,,,ttttt,,,,ttt,,t,,,,,,,,,,,,,,,tttttttt;"
        "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt;";

    mk_templ(str, MapTemplId::intro_forest, std::vector<MapTemplCell>
    {
        {'@', FeatureId::floor},           //Start pos + stone path
        {'.', FeatureId::floor},           //Stone floor with some grass/shrubs
        {'#', FeatureId::wall},            //Stone wall with some low/high rubble
        {',', FeatureId::grass},           //Random grass and bushes
        {'&', FeatureId::grass},           //Graves, or random grass and bushes
        {'_', FeatureId::grass},           //Withered grass
        {'=', FeatureId::floor},           //Stone path
        {'~', FeatureId::liquid_shallow},  //Shallow water
        {'t', FeatureId::tree},
        {'v', FeatureId::brazier},
        {'[', FeatureId::church_bench},
        {'-', FeatureId::altar},
        {'*', FeatureId::carpet},
        {'>', FeatureId::stairs},
        {'+', FeatureId::floor}            //Doors
    });

    //----------------------------------------------------------------- EGYPT
    str =
        "################################################################################;"
        "###...################################........................##################;"
        "###.1.###############################..######################..#################;"
        "###...##############################..#########################.################;"
        "####.##############################..####v....################|....|############;"
        "####.#############################..####..###v..##############......############;"
        "####.##########################.....####..######.v############|....|############;"
        "#####.####.#.#.#.#.###########..######v..#######..###############.##############;"
        "######.##|C........|#########.#######..##########..############..###############;"
        "#######.#...........##.....##.#####...############v.##########..################;"
        "########....M...C....#.#.#.#..####..###...#########..########..#################;"
        "#########..P.....C.#..........####.####.@...........v#######..##################;"
        "########....M...C....#.#.#.#..##|..|###...#################.v###################;"
        "#######.#...........##.....##.##....######################...###################;"
        "######.##|C........|#########.##|..|########......#######.v##.##################;"
        "#####.####.#.#.#.#.##########.####.########..###v..#####..####.#################;"
        "####.########################.####...#####..#####v..###..######.################;"
        "####.########################..#####..###..#######v.....########.###############;"
        "###...########################...####.....#############.#########.###|...|######;"
        "###.2.##########################...##################v..##########........######;"
        "###...############################v....................##############|...|######;"
        "################################################################################;";

    mk_templ(str, MapTemplId::egypt, std::vector<MapTemplCell>
    {
        {'@', FeatureId::floor},
        {'.', FeatureId::floor},
        {'#', FeatureId::wall},
        {'v', FeatureId::brazier},
        {'|', FeatureId::pillar},
        {'S', FeatureId::statue},
        {'P', FeatureId::floor, ActorId::khephren},
        {'M', FeatureId::floor, ActorId::mummy},
        {'C', FeatureId::floor, ActorId::croc_head_mummy},
        {'1', FeatureId::floor},   //Stair candidate #1
        {'2', FeatureId::floor}    //Stair candidate #2
    });

    //----------------------------------------------------------------- LENG
    str =
        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##################################;"
        "%%%%%%%%%%-%%--%--%%--%%%--%%--%%-%-%%%--%-%%-#.....#.....#.....#..............#;"
        "%@----%--------%---%---%--------%----%-----%--#.....#.....#.....#..............#;"
        "%%--------------------------------------------###.#####.#####.###..............#;"
        "%-------------%--------------------------%----#.................#..............#;"
        "%%------------%-------------------------------#...###.#####.###................#;"
        "%%---------------------%%%--------------%-----#...#.....#.....##################;"
        "%%%----%%---------------S%--------------------#...#.....#.....##################;"
        "%%%------------------%%-S%S------%------------#...################............##;"
        "%%%%-----------------%--%%-%----%%------------#......#...#......##.....$......##;"
        "%%%--------------------%%S--------------------##.###.#...#......###.$.....$...##;"
        "%%------------------%-%%S---------------------+......#...######...1.........E.##;"
        "%%%-------------------S%%S-%------------------##.###.#...#......###.$.....$...##;"
        "%%-------------------%-S%%-%----%-------------#...#..###.#.#######.....$......##;"
        "%%---------------------S%%S-------------------#...#......#......##............##;"
        "%%%------------------%-%%---------------%-----#.###############.#############2##;"
        "%%-----%---------------------------%----------#.#...............#############.##;"
        "%%%---------%---------------------------------#.#.###.###.###.#.####....#####..#;"
        "%%--%-----------------------------------------#.#.###.###.###.#.##...##...####.#;"
        "%%%--------------%----------------%---%-----%-#.#.###.###.###.#.#..######....#.#;"
        "%%%%%%--%---%--%%%-%--%%%%%%%-%-%%%--%%--%-%%%#...............#...##########...#;"
        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##################################;";

    mk_templ(str, MapTemplId::leng, std::vector<MapTemplCell>
    {
        {'@', FeatureId::floor},
        {'%', FeatureId::wall},
        {'.', FeatureId::floor},
        {'#', FeatureId::wall},
        {'E', FeatureId::floor, ActorId::leng_elder},
        {'1', FeatureId::floor},
        {'2', FeatureId::wall},
        {'$', FeatureId::altar},
        {'-', FeatureId::grass},
        {'+', FeatureId::floor}, //Door
        {'S', FeatureId::grass, ActorId::leng_spider}
    });

    //----------------------------------------------------------------- RATS IN THE WALLS
    str =
        "################################################################################;"
        "##@#################,##,##xxxxxxxxx###xxxxxxxxxxx######rr#,##########,#,########;"
        "##.##############,,,,,,,,,x,,,,,,,xrrrxrr,rrr,rrxr,rrrr,,,,,,##,,#,,,,,,,#######;"
        "##...&##########,,,,xxxxxxx,,,,,,,xr,rxr,,,,,,,rxrrr,,,,,:,,,,,,,,,,,:,,,,######;"
        "###..:#########,,:,,x,,,,,,,,,,,,,,,,rrrrxx,xxrrxr,r,,,,,,,,,,,,,,,,,,,,,,,,,###;"
        "###:...#######,,,,,,xx,xxxx,,,,,,,xrrrxrrx,,,xrrxrrr,,,,,,,,:,,,,,,:,,,,,,######;"
        "##&..:..#####,,,,,,,,,,,,,xxxx,xxxx,r,xxxx,,,x,xx,,,,,,,,,,,,,,,,,,,,,,,,,######;"
        "####.&.:####,,,,,,,,,,,,,,,:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:,,,,,####;"
        "####..##&:1.,,,,,,,,,:,,,,,,,,,,:,,,,,,,,,,,|,,,:,,,xxx,xx,xxx,,,,,,,,,,,,,#####;"
        "#####..&:.#,,,,,,,,,,,,,,,x,x,x,x,x,x,,,,|,,,,,|,,,rx,,,,,,,,x,,,,:,,,,,,,######;"
        "###########,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,x,rrrrr,,x,,,,,,,,,,,#######;"
        "###########,,,,,,,,|,,,,,,,,,,,,,,,,:,,,|,,,,,,,|,,rr,,,,,r,,,,,,,#,,,,,########;"
        "###########,,,,,|,,,,,|,,,,,,,,,,,,,,,,,,,,,,,,,,,,,x,r,rr,,,x,,####,,,,,#######;"
        "###########,,,,,,,,,,,,,,,x,x,x,x,x,x,,,,|,,,,,|,,,rx,,rrr,,,x,,,,##############;"
        "############,,,|,,,,,,,|,,,,,,,,,,,,,,,,,,,,|,,,,,x,x,r,,r,,,x,,,###############;"
        "############,,,,,,,,,,,,,,,,,,,,:,,,,,,,,,,,,,,,,,rr,,,rr,,,,x,:##xxxxxx########;"
        "#############,,,|,,,,,|,,,xxx,xxxxx,xxx,,,:,,,,r,,,rx,rr,,,,,x,,,,x....x########;"
        "##############,,,,,|,,,,,,x,,,,,xrrrrrx,,,,,,,,,,,r,x,r,,,,,rx,,,,...>.x########;"
        "#################,,,,,,:,,x,,,,,xrr,,rxrr,rr,rr,r,,,xxxxxxxxxx,:,,x....x########;"
        "################:,,,,,,,,,x,,,,,xrrrrrxrrrr##rrr,r,,rr,rr,rr,r,##:xxxxxx########;"
        "###################:,,####xxxxxxxxxxxxx##r#####rr###r###r#rrr###################;"
        "################################################################################;";

    mk_templ(str, MapTemplId::rats_in_the_walls, std::vector<MapTemplCell>
    {
        {'@', FeatureId::floor},
        {'.', FeatureId::floor},
        {'#', FeatureId::wall},
        {'x', FeatureId::wall},                    //Constructed walls
        {'&', FeatureId::bones},
        {'1', FeatureId::floor},                   //Discovery event
        {',', FeatureId::floor},                   //Random bones
        {'r', FeatureId::floor, ActorId::rat},    //Random bones + rat
        {'>', FeatureId::stairs},
        {'|', FeatureId::monolith},
        {':', FeatureId::stalagmite}
    });

    //----------------------------------------------------------------- BOSS LEVEL
    str =
        "################################################################################;"
        "############################...................................................#;"
        "############################...................................................#;"
        "############################...#.....#...#.....#...#.....#...#.....#...........#;"
        "############################...###.###...###.###...###.###...###.###...........#;"
        "##############....#########......###.......###.......###.......###.............#;"
        "##############....#########....###.###...###.###...###.###...###.###...........#;"
        "############.#....#.#######....#.....#...#.....#...#.....#...#.....#...........#;"
        "#...########.#....#.#######.................................................####;"
        "#...#...................#.#.......|....|....|....|....|....|....#...#...#...####;"
        "#.#.#.............................................................v...v...v..###;"
        "#@..............................................................#.....M......###;"
        "#.#.#.............................................................v...v...v..###;"
        "#...#...................#.#.......|....|....|....|....|....|....#...#...#...####;"
        "#...########.#....#.#######.................................................####;"
        "############.#....#.#######....#.....#...#.....#...#.....#...#.....#...........#;"
        "##############....#########....###.###...###.###...###.###...###.###...........#;"
        "##############....#########......###.......###.......###.......###.............#;"
        "############################...###.###...###.###...###.###...###.###...........#;"
        "############################...#.....#...#.....#...##...##...#.....#...........#;"
        "############################...................................................#;"
        "################################################################################;";

    mk_templ(str, MapTemplId::boss_level, std::vector<MapTemplCell>
    {
        {'@', FeatureId::floor},
        {'.', FeatureId::floor},
        {'#', FeatureId::wall},
        {'M', FeatureId::floor, ActorId::the_high_priest},
        {'|', FeatureId::pillar},
        {'v', FeatureId::brazier},
        {'>', FeatureId::stairs}
    });

    //----------------------------------------------------------------- BOSS LEVEL
    str =
        "################################################################################;"
        "#####################################...|...####################################;"
        "#####################################.|...|.####################################;"
        "#####################################...|...####################################;"
        "####################################..|...|..###################################;"
        "###################################.....|.....##################################;"
        "##################################....|...|....#################################;"
        "#################################...#.......#...################################;"
        "#######.......................##..#.#.##.##.#.#..##.......######################;"
        "#######.|.|.|.|.|.|.|.|.|.|.|.#v..|.v.|...|.v.|..v#.|.|.|.######################;"
        "#######..@..............................o.................######################;"
        "#######.|.|.|.|.|.|.|.|.|.|.|.#v..|.v.|...|.v.|..v#.|.|.|.######################;"
        "#######.......................##..#.#.##.##.#.#..##.......######################;"
        "#################################...#.......#...################################;"
        "##################################....|...|....#################################;"
        "###################################.....|.....##################################;"
        "####################################..|...|..###################################;"
        "#####################################...|...####################################;"
        "#####################################.|...|.####################################;"
        "#####################################...|...####################################;"
        "################################################################################;"
        "################################################################################;";

    mk_templ(str, MapTemplId::trapez_level, std::vector<MapTemplCell>
    {
        {'@', FeatureId::floor},
        {'.', FeatureId::floor},
        {'#', FeatureId::wall},
        {'|', FeatureId::pillar},
        {'v', FeatureId::brazier},
        {'o', FeatureId::floor, ActorId::END, ItemId::trapez}
    });
}

} //namespace

void init()
{
    init_templs();
}

const MapTempl& templ(const MapTemplId id)
{
    ASSERT(id != MapTemplId::END);
    return templates_[int(id)];
}

} //map_templ_handling

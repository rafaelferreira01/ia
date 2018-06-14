#ifndef GFX_HPP
#define GFX_HPP

#include <string>
#include <unordered_map>

// NOTE: When updating this, also update the two maps below
enum class TileId
{
    player_firearm,
    player_melee,
    zombie_unarmed,
    zombie_armed,
    zombie_bloated,
    cultist_firearm,
    cultist_dagger,
    witch_or_warlock,
    ghoul,
    mummy,
    deep_one,
    shadow,
    leng_elder,
    fiend,
    ape,
    croc_head_mummy,
    the_high_priest,
    floating_skull,
    crawling_hand,
    crawling_intestines,
    raven,
    armor,
    potion,
    ammo,
    scroll,
    elder_sign,
    chest_closed,
    chest_open,
    amulet,
    ring,
    lantern,
    medical_bag,
    gas_mask,
    void_traveler,
    snake,
    rat,
    spider,
    wolf,
    phantasm,
    rat_thing,
    hound,
    bat,
    byakhee,
    mass_of_worms,
    ooze,
    gas_spore,
    polyp,
    fungi,
    amoeba,
    tentacles,
    vortex,
    ghost,
    wraith,
    mantis,
    locust,
    bog_tcher,
    mi_go_armor,
    horn,
    clockwork,
    crystal,
    pistol,
    tommy_gun,
    shotgun,
    dynamite,
    dynamite_lit,
    molotov,
    incinerator,
    mi_go_gun,
    flare,
    flare_gun,
    flare_lit,
    orb,
    zombie_dust,
    dagger,
    crowbar,
    rod,
    axe,
    club,
    hammer,
    machete,
    pitchfork,
    sledge_hammer,
    rock,
    iron_spike,
    pharaoh_staff,
    spiked_mace,
    lockpick,
    hunting_horror,
    giant_spider,
    chthonian,
    leech,
    mi_go,
    floor,
    aim_marker_head,
    aim_marker_line,
    excl_mark,
    wall_top,
    wall_front_alt1,
    wall_front_alt2,
    wall_front,
    square_checkered_sparse,
    rubble_high,
    rubble_low,
    stairs_down,
    lever_left,
    lever_right,
    device1,
    device2,
    chains,
    cabinet_closed,
    cabinet_open,
    pillar_broken,
    pillar,
    pillar_carved,
    barrel,
    sarcophagus,
    cave_wall_front,
    cave_wall_top,
    square_checkered,
    egypt_wall_front,
    egypt_wall_top,
    monolith,
    bookshelf_full,
    bookshelf_empty,
    alchemist_bench_full,
    alchemist_bench_empty,
    brazier,
    altar,
    web,
    door_closed,
    door_open,
    door_broken,
    gate_closed,
    gate_open,
    fountain,
    tree,
    bush,
    church_bench,
    grave_stone,
    tomb_open,
    tomb_closed,
    pylon,
    water1,
    water2,
    trap_general,
    cocoon_open,
    cocoon_closed,
    blast1,
    blast2,
    corpse,
    corpse2,
    projectile_std_front_slash,
    projectile_std_back_slash,
    projectile_std_dash,
    projectile_std_vertical_bar,
    vines,
    grate,
    gore1,
    gore2,
    gore3,
    gore4,
    gore5,
    gore6,
    gore7,
    gore8,
    smoke,
    trapez,
    pit,
    hangbridge_ver,
    hangbridge_hor,
    scorched_ground,
    stalagmite,
    heart,
    brain,
    weight,
    spirit,
    stopwatch,

    END
};

const std::unordered_map<std::string, TileId> str_to_tile_id_map = {
    {"player_firearm", TileId::player_firearm},
    {"player_melee", TileId::player_melee},
    {"zombie_unarmed", TileId::zombie_unarmed},
    {"zombie_armed", TileId::zombie_armed},
    {"zombie_bloated", TileId::zombie_bloated},
    {"cultist_firearm", TileId::cultist_firearm},
    {"cultist_dagger", TileId::cultist_dagger},
    {"witch_or_warlock", TileId::witch_or_warlock},
    {"ghoul", TileId::ghoul},
    {"mummy", TileId::mummy},
    {"deep_one", TileId::deep_one},
    {"shadow", TileId::shadow},
    {"leng_elder", TileId::leng_elder},
    {"fiend", TileId::fiend},
    {"ape", TileId::ape},
    {"croc_head_mummy", TileId::croc_head_mummy},
    {"the_high_priest", TileId::the_high_priest},
    {"floating_skull", TileId::floating_skull},
    {"crawling_hand", TileId::crawling_hand},
    {"crawling_intestines", TileId::crawling_intestines},
    {"raven", TileId::raven},
    {"armor", TileId::armor},
    {"potion", TileId::potion},
    {"ammo", TileId::ammo},
    {"scroll", TileId::scroll},
    {"elder_sign", TileId::elder_sign},
    {"chest_closed", TileId::chest_closed},
    {"chest_open", TileId::chest_open},
    {"amulet", TileId::amulet},
    {"ring", TileId::ring},
    {"lantern", TileId::lantern},
    {"medical_bag", TileId::medical_bag},
    {"gas_mask", TileId::gas_mask},
    {"void_traveler", TileId::void_traveler},
    {"snake", TileId::snake},
    {"rat", TileId::rat},
    {"spider", TileId::spider},
    {"wolf", TileId::wolf},
    {"phantasm", TileId::phantasm},
    {"rat_thing", TileId::rat_thing},
    {"hound", TileId::hound},
    {"bat", TileId::bat},
    {"byakhee", TileId::byakhee},
    {"mass_of_worms", TileId::mass_of_worms},
    {"ooze", TileId::ooze},
    {"gas_spore", TileId::gas_spore},
    {"polyp", TileId::polyp},
    {"fungi", TileId::fungi},
    {"amoeba", TileId::amoeba},
    {"tentacles", TileId::tentacles},
    {"vortex", TileId::vortex},
    {"ghost", TileId::ghost},
    {"wraith", TileId::wraith},
    {"mantis", TileId::mantis},
    {"locust", TileId::locust},
    {"bog_tcher", TileId::bog_tcher},
    {"mi_go_armor", TileId::mi_go_armor},
    {"horn", TileId::horn},
    {"clockwork", TileId::clockwork},
    {"crystal", TileId::crystal},
    {"pistol", TileId::pistol},
    {"tommy_gun", TileId::tommy_gun},
    {"shotgun", TileId::shotgun},
    {"dynamite", TileId::dynamite},
    {"dynamite_lit", TileId::dynamite_lit},
    {"molotov", TileId::molotov},
    {"incinerator", TileId::incinerator},
    {"mi_go_gun", TileId::mi_go_gun},
    {"flare", TileId::flare},
    {"flare_gun", TileId::flare_gun},
    {"flare_lit", TileId::flare_lit},
    {"orb", TileId::orb},
    {"zombie_dust", TileId::zombie_dust},
    {"dagger", TileId::dagger},
    {"crowbar", TileId::crowbar},
    {"rod", TileId::rod},
    {"axe", TileId::axe},
    {"club", TileId::club},
    {"hammer", TileId::hammer},
    {"machete", TileId::machete},
    {"pitchfork", TileId::pitchfork},
    {"sledge_hammer", TileId::sledge_hammer},
    {"rock", TileId::rock},
    {"iron_spike", TileId::iron_spike},
    {"pharaoh_staff", TileId::pharaoh_staff},
    {"spiked_mace", TileId::spiked_mace},
    {"lockpick", TileId::lockpick},
    {"hunting_horror", TileId::hunting_horror},
    {"giant_spider", TileId::giant_spider},
    {"chthonian", TileId::chthonian},
    {"leech", TileId::leech},
    {"mi_go", TileId::mi_go},
    {"floor", TileId::floor},
    {"aim_marker_head", TileId::aim_marker_head},
    {"aim_marker_line", TileId::aim_marker_line},
    {"excl_mark", TileId::excl_mark},
    {"wall_front", TileId::wall_front},
    {"square_checkered_sparse", TileId::square_checkered_sparse},
    {"rubble_high", TileId::rubble_high},
    {"rubble_low", TileId::rubble_low},
    {"pylon", TileId::pylon},
    {"stairs_down", TileId::stairs_down},
    {"brazier", TileId::brazier},
    {"altar", TileId::altar},
    {"web", TileId::web},
    {"door_closed", TileId::door_closed},
    {"door_open", TileId::door_open},
    {"door_broken", TileId::door_broken},
    {"fountain", TileId::fountain},
    {"gate_closed", TileId::gate_closed},
    {"gate_open", TileId::gate_open},
    {"tree", TileId::tree},
    {"bush", TileId::bush},
    {"church_bench", TileId::church_bench},
    {"grave_stone", TileId::grave_stone},
    {"tomb_open", TileId::tomb_open},
    {"tomb_closed", TileId::tomb_closed},
    {"water1", TileId::water1},
    {"water2", TileId::water2},
    {"cocoon_open", TileId::cocoon_open},
    {"cocoon_closed", TileId::cocoon_closed},
    {"blast1", TileId::blast1},
    {"blast2", TileId::blast2},
    {"corpse", TileId::corpse},
    {"corpse2", TileId::corpse2},
    {"projectile_std_front_slash", TileId::projectile_std_front_slash},
    {"projectile_std_back_slash", TileId::projectile_std_back_slash},
    {"projectile_std_dash", TileId::projectile_std_dash},
    {"projectile_std_vertical_bar", TileId::projectile_std_vertical_bar},
    {"vines", TileId::vines},
    {"grate", TileId::grate},
    {"gore1", TileId::gore1},
    {"gore2", TileId::gore2},
    {"gore3", TileId::gore3},
    {"gore4", TileId::gore4},
    {"gore5", TileId::gore5},
    {"gore6", TileId::gore6},
    {"gore7", TileId::gore7},
    {"gore8", TileId::gore8},
    {"smoke", TileId::smoke},
    {"wall_front_alt1", TileId::wall_front_alt1},
    {"wall_front_alt2", TileId::wall_front_alt2},
    {"trapez", TileId::trapez},
    {"pit", TileId::pit},
    {"lever_right", TileId::lever_right},
    {"lever_left", TileId::lever_left},
    {"device1", TileId::device1},
    {"device2", TileId::device2},
    {"chains", TileId::chains},
    {"cabinet_closed", TileId::cabinet_closed},
    {"cabinet_open", TileId::cabinet_open},
    {"pillar_broken", TileId::pillar_broken},
    {"pillar", TileId::pillar},
    {"pillar_carved", TileId::pillar_carved},
    {"barrel", TileId::barrel},
    {"sarcophagus", TileId::sarcophagus},
    {"cave_wall_front", TileId::cave_wall_front},
    {"cave_wall_top", TileId::cave_wall_top},
    {"wall_top", TileId::wall_top},
    {"square_checkered", TileId::square_checkered},
    {"egypt_wall_front", TileId::egypt_wall_front},
    {"egypt_wall_top", TileId::egypt_wall_top},
    {"monolith", TileId::monolith},
    {"bookshelf_full", TileId::bookshelf_full},
    {"bookshelf_empty", TileId::bookshelf_empty},
    {"hangbridge_ver", TileId::hangbridge_ver},
    {"hangbridge_hor", TileId::hangbridge_hor},
    {"scorched_ground", TileId::scorched_ground},
    {"stalagmite", TileId::stalagmite},
    {"trap_general", TileId::trap_general},
    {"alchemist_bench_full", TileId::alchemist_bench_full},
    {"alchemist_bench_empty", TileId::alchemist_bench_empty},
    {"heart", TileId::heart},
    {"brain", TileId::brain},
    {"weight", TileId::weight},
    {"spirit", TileId::spirit},
    {"stopwatch", TileId::stopwatch},
    {"none", TileId::END}
};

const std::unordered_map<TileId, std::string> tile_id_to_str_map = {
    {TileId::player_firearm, "player_firearm"},
    {TileId::player_melee, "player_melee"},
    {TileId::zombie_unarmed, "zombie_unarmed"},
    {TileId::zombie_armed, "zombie_armed"},
    {TileId::zombie_bloated, "zombie_bloated"},
    {TileId::cultist_firearm, "cultist_firearm"},
    {TileId::cultist_dagger, "cultist_dagger"},
    {TileId::witch_or_warlock, "witch_or_warlock"},
    {TileId::ghoul, "ghoul"},
    {TileId::mummy, "mummy"},
    {TileId::deep_one, "deep_one"},
    {TileId::shadow, "shadow"},
    {TileId::leng_elder, "leng_elder"},
    {TileId::fiend, "fiend"},
    {TileId::ape, "ape"},
    {TileId::croc_head_mummy, "croc_head_mummy"},
    {TileId::the_high_priest, "the_high_priest"},
    {TileId::floating_skull, "floating_skull"},
    {TileId::crawling_hand, "crawling_hand"},
    {TileId::crawling_intestines, "crawling_intestines"},
    {TileId::raven, "raven"},
    {TileId::armor, "armor"},
    {TileId::potion, "potion"},
    {TileId::ammo, "ammo"},
    {TileId::scroll, "scroll"},
    {TileId::elder_sign, "elder_sign"},
    {TileId::chest_closed, "chest_closed"},
    {TileId::chest_open, "chest_open"},
    {TileId::amulet, "amulet"},
    {TileId::ring, "ring"},
    {TileId::lantern, "lantern"},
    {TileId::medical_bag, "medical_bag"},
    {TileId::gas_mask, "gas_mask"},
    {TileId::void_traveler, "void_traveler"},
    {TileId::snake, "snake"},
    {TileId::rat, "rat"},
    {TileId::spider, "spider"},
    {TileId::wolf, "wolf"},
    {TileId::phantasm, "phantasm"},
    {TileId::rat_thing, "rat_thing"},
    {TileId::hound, "hound"},
    {TileId::bat, "bat"},
    {TileId::byakhee, "byakhee"},
    {TileId::mass_of_worms, "mass_of_worms"},
    {TileId::ooze, "ooze"},
    {TileId::gas_spore, "gas_spore"},
    {TileId::polyp, "polyp"},
    {TileId::fungi, "fungi"},
    {TileId::amoeba, "amoeba"},
    {TileId::tentacles, "tentacles"},
    {TileId::vortex, "vortex"},
    {TileId::ghost, "ghost"},
    {TileId::wraith, "wraith"},
    {TileId::mantis, "mantis"},
    {TileId::locust, "locust"},
    {TileId::bog_tcher, "bog_tcher"},
    {TileId::mi_go_armor, "mi_go_armor"},
    {TileId::horn, "horn"},
    {TileId::clockwork, "clockwork"},
    {TileId::crystal, "crystal"},
    {TileId::pistol, "pistol"},
    {TileId::tommy_gun, "tommy_gun"},
    {TileId::shotgun, "shotgun"},
    {TileId::dynamite, "dynamite"},
    {TileId::dynamite_lit, "dynamite_lit"},
    {TileId::molotov, "molotov"},
    {TileId::incinerator, "incinerator"},
    {TileId::mi_go_gun, "mi_go_gun"},
    {TileId::flare, "flare"},
    {TileId::flare_gun, "flare_gun"},
    {TileId::flare_lit, "flare_lit"},
    {TileId::orb, "orb"},
    {TileId::zombie_dust, "zombie_dust"},
    {TileId::dagger, "dagger"},
    {TileId::crowbar, "crowbar"},
    {TileId::rod, "rod"},
    {TileId::axe, "axe"},
    {TileId::club, "club"},
    {TileId::hammer, "hammer"},
    {TileId::machete, "machete"},
    {TileId::pitchfork, "pitchfork"},
    {TileId::sledge_hammer, "sledge_hammer"},
    {TileId::rock, "rock"},
    {TileId::iron_spike, "iron_spike"},
    {TileId::pharaoh_staff, "pharaoh_staff"},
    {TileId::spiked_mace, "spiked_mace"},
    {TileId::lockpick, "lockpick"},
    {TileId::hunting_horror, "hunting_horror"},
    {TileId::giant_spider, "giant_spider"},
    {TileId::chthonian, "chthonian"},
    {TileId::leech, "leech"},
    {TileId::mi_go, "mi_go"},
    {TileId::floor, "floor"},
    {TileId::aim_marker_head, "aim_marker_head"},
    {TileId::aim_marker_line, "aim_marker_line"},
    {TileId::excl_mark, "excl_mark"},
    {TileId::wall_front, "wall_front"},
    {TileId::square_checkered_sparse, "square_checkered_sparse"},
    {TileId::rubble_high, "rubble_high"},
    {TileId::rubble_low, "rubble_low"},
    {TileId::pylon, "pylon"},
    {TileId::stairs_down, "stairs_down"},
    {TileId::brazier, "brazier"},
    {TileId::altar, "altar"},
    {TileId::web, "web"},
    {TileId::door_closed, "door_closed"},
    {TileId::door_open, "door_open"},
    {TileId::door_broken, "door_broken"},
    {TileId::fountain, "fountain"},
    {TileId::gate_closed, "gate_closed"},
    {TileId::gate_open, "gate_open"},
    {TileId::tree, "tree"},
    {TileId::bush, "bush"},
    {TileId::church_bench, "church_bench"},
    {TileId::grave_stone, "grave_stone"},
    {TileId::tomb_open, "tomb_open"},
    {TileId::tomb_closed, "tomb_closed"},
    {TileId::water1, "water1"},
    {TileId::water2, "water2"},
    {TileId::cocoon_open, "cocoon_open"},
    {TileId::cocoon_closed, "cocoon_closed"},
    {TileId::blast1, "blast1"},
    {TileId::blast2, "blast2"},
    {TileId::corpse, "corpse"},
    {TileId::corpse2, "corpse2"},
    {TileId::projectile_std_front_slash, "projectile_std_front_slash"},
    {TileId::projectile_std_back_slash, "projectile_std_back_slash"},
    {TileId::projectile_std_dash, "projectile_std_dash"},
    {TileId::projectile_std_vertical_bar, "projectile_std_vertical_bar"},
    {TileId::vines, "vines"},
    {TileId::grate, "grate"},
    {TileId::gore1, "gore1"},
    {TileId::gore2, "gore2"},
    {TileId::gore3, "gore3"},
    {TileId::gore4, "gore4"},
    {TileId::gore5, "gore5"},
    {TileId::gore6, "gore6"},
    {TileId::gore7, "gore7"},
    {TileId::gore8, "gore8"},
    {TileId::smoke, "smoke"},
    {TileId::wall_front_alt1, "wall_front_alt1"},
    {TileId::wall_front_alt2, "wall_front_alt2"},
    {TileId::trapez, "trapez"},
    {TileId::pit, "pit"},
    {TileId::lever_right, "lever_right"},
    {TileId::lever_left, "lever_left"},
    {TileId::device1, "device1"},
    {TileId::device2, "device2"},
    {TileId::chains, "chains"},
    {TileId::cabinet_closed, "cabinet_closed"},
    {TileId::cabinet_open, "cabinet_open"},
    {TileId::pillar_broken, "pillar_broken"},
    {TileId::pillar, "pillar"},
    {TileId::pillar_carved, "pillar_carved"},
    {TileId::barrel, "barrel"},
    {TileId::sarcophagus, "sarcophagus"},
    {TileId::cave_wall_front, "cave_wall_front"},
    {TileId::cave_wall_top, "cave_wall_top"},
    {TileId::wall_top, "wall_top"},
    {TileId::square_checkered, "square_checkered"},
    {TileId::egypt_wall_front, "egypt_wall_front"},
    {TileId::egypt_wall_top, "egypt_wall_top"},
    {TileId::monolith, "monolith"},
    {TileId::bookshelf_full, "bookshelf_full"},
    {TileId::bookshelf_empty, "bookshelf_empty"},
    {TileId::hangbridge_ver, "hangbridge_ver"},
    {TileId::hangbridge_hor, "hangbridge_hor"},
    {TileId::scorched_ground, "scorched_ground"},
    {TileId::stalagmite, "stalagmite"},
    {TileId::trap_general, "trap_general"},
    {TileId::alchemist_bench_full, "alchemist_bench_full"},
    {TileId::alchemist_bench_empty, "alchemist_bench_empty"},
    {TileId::heart, "heart"},
    {TileId::brain, "brain"},
    {TileId::weight, "weight"},
    {TileId::spirit, "spirit"},
    {TileId::stopwatch, "stopwatch"},
    {TileId::END, "none"}
};

class P;

namespace gfx
{

P character_pos(const char character);

} // gfx

#endif // GFX_HPP

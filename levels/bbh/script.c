#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/bbh/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bbh_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x07, _bbh_segment_7SegmentRomStart, _bbh_segment_7SegmentRomEnd), 
	LOAD_MIO0(0x0A, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0_TEXTURE(0x09, _spooky_mio0SegmentRomStart, _spooky_mio0SegmentRomEnd), 
	LOAD_MIO0(0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x06, _group14_mio0SegmentRomStart, _group14_mio0SegmentRomEnd), //add skeeter to group 14
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(0x16, warp_pipe_geo), 
	LOAD_MODEL_FROM_GEO(0x35, barrel_geo), 
	LOAD_MODEL_FROM_GEO(0x38, jetski_geo2), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bbh_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0c, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_JRB, 0x02, 0x0D, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0E, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0F, LEVEL_JRB, 0x03, 0x0C, WARP_NO_CHECKPOINT),
		WARP_NODE(0x12, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xE5, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xD5, WARP_NO_CHECKPOINT),
		WARP_NODE(0x14, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x1B, LEVEL_BBH, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BBH, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_DL_CANNON_LID, -1800, 3272, -2899, 0, -90, 0, (0xA1 << 16), bhvCannonClosed),
		OBJECT(MODEL_KOOPA_WITH_SHELL, -1647, 0, -223, 0, 0, 0, 0x00270000, bhvKoopaTalk),
		OBJECT(MODEL_KOOPA_WITH_SHELL, 3392, 800, -4537, 0, -59, 0, 0x00280000, bhvKoopaTalk),
		OBJECT(MODEL_KOOPA_WITH_SHELL, -1975, 679, -1570, 0, 0, 0, 0x002A0000, bhvKoopaTalk),
		OBJECT(MODEL_KOOPA_WITH_SHELL, -1243, 1540, -5081, 0, 67, 0, 0x002B0000, bhvKoopaTalk),
		OBJECT(MODEL_KOOPA_WITH_SHELL, 4725, -280, 4405, 0, -173, 0, 0x002C0000, bhvKoopaTalk),
		OBJECT(MODEL_KOOPA_WITH_SHELL, -3261, 0, -3813, 0, 0, 0, 0x002E0000, bhvKoopaTalk),
		OBJECT(0x38, -3783, -305, 4075, 0, 178, 0, 0x00010000, bhvJetski2),
		OBJECT_WITH_ACTS(MODEL_KOOPA_WITHOUT_SHELL, 1433, 418, 1187, 0, -173, 0, 0x01000000, bhvSurfKoopa, ACT_1 | ACT_2),
		OBJECT(MODEL_NONE, -4472, -280, 4078, 0, -180, 0, 0x000a0000, bhvAirborneWarp),
		OBJECT(MODEL_NONE, -3552, -280, 1360, 0, 0, 0, (0x14 << 16), bhvAirborneWarp),
		OBJECT(MODEL_NONE, -50, 1155, -2874, 0, 21, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3780, -280, 2444, 0, 0, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3545, -280, 2011, 0, 0, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1623, -129, 911, 0, 90, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, 596, 316, -1339, 0, 90, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, -4955, 1252, 216, 0, 0, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, -4873, 601, -2116, 0, 0, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2021, 1170, -3992, 0, 0, 0, 0x00100000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 631, 464, 4605, 0, 21, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -4512, -293, 5089, 0, 21, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3201, -86, -2782, 0, 0, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3010, 800, -1689, 0, 11, 0, 0, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1206, 1849, -3532, 0, 21, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 1860, 1367, -255, 0, 21, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4888, 951, -337, 0, 21, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3371, -305, 4911, 0, 21, 0, 0x00120000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2575, -305, 4513, 0, 21, 0, 0x00120000, bhvCoinFormation),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 3860, 418, 918, 0, 0, 0, 0, bhvBlueCoinSwitch),
		OBJECT(MODEL_BLUE_COIN, 3654, 418, 1181, 0, 0, 0, 0, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 4091, 418, 1181, 0, 0, 0, 0, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 4356, 1001, 1220, 0, 0, 0, 0, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, 3356, 1001, 1193, 0, 0, 0, 0, bhvHiddenBlueCoin),
		OBJECT(MODEL_BOBOMB_BUDDY, 3948, 1434, -4082, 0, -49, 0, 0x00000000, bhvBobombBuddyOpensCannon),
		OBJECT(MODEL_STAR, 1566, 3849, 7546, 0, -180, 0, 0x02000000, bhvStar),
		OBJECT(MODEL_STAR, 3576, 1004, -3784, 0, -180, 0, 0x05000000, bhvStar),
		OBJECT(MODEL_STAR, -6063, 4140, -1211, 0, -180, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_RED_COIN, 5039, 1085, 1392, 0, -180, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2053, 2308, -4919, 0, -180, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 4905, 1797, -369, 0, -180, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1946, 1309, -1426, 0, -180, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3490, 2042, -4280, 0, -180, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1516, 2105, -2149, 0, -180, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 698, 667, 393, 0, -180, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 602, 2504, -4600, 0, -180, 0, 0x00000000, bhvRedCoin),
		OBJECT(0x16, 2295, 2602, 1043, 0, -180, 0, 0x000d0000, bhvWarpPipe),
		OBJECT(0, 2295, 2602, 886, 0, -180, 0, 0x000d0000, bhvWarpPipe),
		OBJECT(0, -162, 200, -320, 0, -180, 0, (0x04 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_STAR, 2296, 2924, 874, 0, -180, 0, 0x03000000, bhvStar),
		OBJECT(0x35, -4612, 27, -3859, 0, 0, 0, 0x00000000, bhvBarrelRoll),
		OBJECT(0x35, -4743, 1434, -4001, 0, 0, 0, 0x00000000, bhvBarrelRoll),
		OBJECT(0x35, -4731, 739, 1487, 0, -180, 0, 0x00010000, bhvBarrelRoll),
		OBJECT(0x35, -4341, -69, -1366, 0, 0, 0, 0x00000000, bhvBarrelRoll),
		OBJECT(0x35, -4547, 650, -1160, 0, -180, 0, 0x00010000, bhvBarrelRoll),
		OBJECT(0x35, -5124, 579, -2779, 0, -180, 0, 0x00010000, bhvBarrelRoll),
		OBJECT(0x35, -5198, 1361, -2622, 0, 0, 0, 0x00000000, bhvBarrelRoll),
		OBJECT(0x35, -4621, 1301, -956, 0, 0, 0, 0x00000000, bhvBarrelRoll),
		OBJECT(0x35, -5158, 2101, 1066, 0, -180, 0, 0x00010000, bhvBarrelRoll),
		OBJECT(0x35, -4905, 2035, -521, 0, -180, 0, 0x00010000, bhvBarrelRoll),
		OBJECT(0x35, -5346, 2813, -3503, 0, 0, 0, 0x00000000, bhvBarrelRoll),
		OBJECT(0x35, -5328, 2724, -1350, 0, 0, 0, 0x00000000, bhvBarrelRoll),
		OBJECT(0, 855, 2143, 7382, 0, -180, 0, 0x00870000, bhvPoleGrabbing),
		OBJECT(0x35, -5307, 3344, -2182, 0, -180, 0, 0x00010000, bhvBarrelRoll),
		OBJECT(0x35, -5009, 2659, 279, 0, 0, 0, 0x00000000, bhvBarrelRoll),
		OBJECT(MODEL_NONE, -3374, -1474, 494, 0, -180, 0, 0x400b0000, bhvWarp),
		OBJECT(MODEL_NONE, -3374, -1370, 494, 0, -180, 0, 0x400b0000, bhvWarp),
		OBJECT(MODEL_NONE, -3374, -1246, 494, 0, -180, 0, 0x400b0000, bhvWarp),
		OBJECT(MODEL_NONE, -3374, -1125, 494, 0, -180, 0, 0x400b0000, bhvWarp),
		TERRAIN(bbh_area_1_collision),
		MACRO_OBJECTS(bbh_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GREEK),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, bbh_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xE5, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xD5, WARP_NO_CHECKPOINT),
		WARP_NODE(0x14, LEVEL_BBH, 0x01, 0x14, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_BBH, 0x01, 0x0D, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -167, -156, 1046, 0, -180, 0, 0x000a0000, bhvAirborneWarp),
		OBJECT(0x16, 11686, 948, -12250, 0, 0, 90, 0x000d0000, bhvWarpPipe),
		OBJECT(MODEL_SKEETER, -300, -353, -673, 0, 104, 0, 0x000a0000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 270, -432, -4027, 0, 104, 0, 0x000a0000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 1414, -156, -5333, 0, 104, 0, 0x000a0000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 3283, -432, -5985, 0, 104, 0, 0x000a0000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 5395, -432, -5457, 0, 104, 0, 0x000a0000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 5981, -156, -10015, 0, 104, 0, 0x000a0000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 6696, -432, -11686, 0, 104, 0, 0x000a0000, bhvSkeeter),
		OBJECT(MODEL_SKEETER, 10540, 600, -12254, 0, 104, 0, 0x000a0000, bhvSkeeter),
		OBJECT(MODEL_NONE, -158, -136, 1875, 0, -180, 0, (0x40 << 24) | (0x14 << 16), bhvWarp),
		TERRAIN(bbh_area_2_collision),
		MACRO_OBJECTS(bbh_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_UNDERGROUND),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, bbh_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0b, LEVEL_BBH, 0x01, 0x0C, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0c, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_BBH, 0x01, 0x0D, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0E, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0F, LEVEL_JRB, 0x03, 0x0C, WARP_NO_CHECKPOINT),
		WARP_NODE(0x10, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x11, LEVEL_JRB, 0x03, 0x0E, WARP_NO_CHECKPOINT),
		WARP_NODE(0x12, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xE5, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xD5, WARP_NO_CHECKPOINT),
		WARP_NODE(0x13, LEVEL_JRB, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x14, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(0x38, -1900, 0, 7723, 0, 90, 0, 0x00010000, bhvJetski2),
		OBJECT(MODEL_KOOPA_WITHOUT_SHELL, -1879, 0, 7288, 0, 76, 0, 0x01020000, bhvSurfKoopa),
		OBJECT(MODEL_NONE, -1881, 500, 7736, 0, 90, 0, 0x000a0000, bhvAirborneWarp),
		OBJECT(0, -622, 0, 7837, 0, 178, 0, 0x00000000, bhvWaypoint),
		OBJECT(0, 3401, 0, -3614, 0, 178, 0, 0x00000003, bhvWaypoint),
		OBJECT(0, 3787, 0, 6216, 0, 178, 0, 0x00000001, bhvWaypoint),
		OBJECT(0, 6210, 0, 590, 0, 178, 0, 0x00000002, bhvWaypoint),
		OBJECT(0, -1989, 0, -5921, 0, 178, 0, 0x00000003, bhvWaypoint),
		OBJECT(0, -6432, 0, -4127, 0, 178, 0, 0x00000004, bhvWaypoint),
		OBJECT(0, -6512, 0, 1094, 0, 178, 0, 0x00000005, bhvWaypoint),
		OBJECT(0, -2421, 0, 7777, 0, 178, 0, 0x00000006, bhvWaypoint),
		TERRAIN(bbh_area_3_collision),
		MACRO_OBJECTS(bbh_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SLIDE),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};

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

#include "make_const_nonconst.h"
#include "levels/hmc/header.h"

const LevelScript level_hmc_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x07, _hmc_segment_7SegmentRomStart, _hmc_segment_7SegmentRomEnd), 
	LOAD_MIO0(0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0xb, _effect_mio0SegmentRomStart, _effect_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(0x35, tikiflying_geo), 
	LOAD_MODEL_FROM_GEO(0x36, tikigoomba_geo), 
	LOAD_MODEL_FROM_GEO(0x37, tikispear_geo), 
	LOAD_MODEL_FROM_GEO(0x38, tikiguy_geo), 
	LOAD_MODEL_FROM_GEO(0x39, easterhead_geo), 
	LOAD_MODEL_FROM_GEO(0x3A, totempole_geo), 
	LOAD_MODEL_FROM_GEO(0x3B, boss1_geo), 
	LOAD_MODEL_FROM_GEO(0x3C, boss2_geo), 
	LOAD_MODEL_FROM_GEO(0x3D, boss3_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_THI_WARP_PIPE, warp_pipe_geo), 

	AREA(1, hmc_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_HMC, 0x02, 0x0A, WARP_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_HMC, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 1128, 845, 82, 0, 167, 0, 0x000a0000, bhvAirborneWarp),
		OBJECT(MODEL_NONE, -969, 0, 20307, 0, 0, 0, 0x00000000, bhvTextureAnims),
		OBJECT(0x35, 8795, 3698, -5042, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, 8971, 3247, -4675, 0, 0, 0, 0x00010000, bhvFlyingTiki),
		OBJECT(0x35, -368, 845, -4456, 0, -66, 0, 0x00020030, bhvFlyingTiki),
		OBJECT(0x35, 8214, 2844, -4651, 0, 0, 0, 0x00030000, bhvFlyingTiki),
		OBJECT(MODEL_STAR, 8705, 4269, -4654, 0, -151, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_RED_FLAME, 6650, 2083, -4760, 0, 0, 0, 0x00030000, bhvFlame2),
		OBJECT(MODEL_RED_FLAME, 6612, 2085, -4459, 0, 0, 0, 0x00030000, bhvFlame2),
		OBJECT(MODEL_RED_FLAME, 2031, 2085, -5035, 0, 0, 0, 0x00030000, bhvFlame2),
		OBJECT(MODEL_RED_FLAME, 2069, 2084, -5336, 0, 0, 0, 0x00030000, bhvFlame2),
		OBJECT(0x35, -8166, 1054, -4047, 0, 65, 0, 0x00020025, bhvFlyingTiki),
		OBJECT(0x35, 657, 937, -590, 0, -119, 0, 0x00020070, bhvFlyingTiki),
		OBJECT(0, 838, 370, 591, 0, -69, 0, 0x04000000, bhvHiddenRedCoinStar),
		OBJECT(0x35, -6827, 1114, 934, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -1961, 1020, -4109, 0, 65, 0, 0x00010000, bhvFlyingTiki),
		OBJECT(0x35, -5806, 1114, 392, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -5323, 1114, -55, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -4851, 1114, -537, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -4355, 1203, -1102, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -3942, 1215, -1421, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -6335, 1114, 669, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -7287, 1114, 1190, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x36, -6286, 840, 2082, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -5253, 306, 5292, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -5021, 306, 4205, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -10716, 1435, 1545, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -8766, 990, 1733, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -11426, 2164, 3877, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -8767, 2076, 2634, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -10103, 2333, 4007, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -7108, 2182, 3001, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x38, 7441, 1885, -6502, 0, -91, 0, 0x42030000, bhvTikiGuy),
		OBJECT(0x38, 9853, 2124, -3946, 0, -152, 0, 0x46030064, bhvTikiGuy),
		OBJECT(0x38, 8900, 1968, -6112, 0, -54, 0, 0x41030022, bhvTikiGuy),
		OBJECT(0x38, 7251, 1989, -4361, 0, 112, 0, 0x45030022, bhvTikiGuy),
		OBJECT(0x38, 8480, 2082, -3661, 0, -31, 0, 0x44030022, bhvTikiGuy),
		OBJECT(0x36, 5323, 974, 8707, 0, 27, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(MODEL_NONE, -8261, 2633, 4401, 0, -119, 0, 0x000C0000, bhvAirborneWarp),
		OBJECT(MODEL_NONE, 3544, 114, 3613, 0, 21, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4583, 114, -3817, 0, 98, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4388, 1625, -4884, 0, 83, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -3692, 114, 5588, 0, 67, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -9211, 2076, 3411, 0, 67, 0, 0x00020000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 1351, 649, 261, 0, 67, 0, 0x00020000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4405, 412, 7526, 0, 67, 0, 0x00020000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -6145, 1085, -10463, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5884, 1557, -10735, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -4598, 2504, -11476, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 6962, 241, -3478, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 3084, 51, -2966, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -4775, 51, 282, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2349, 51, 2600, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -8446, 672, -5830, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 12495, -1082, 2757, 0, 67, 0, 0x00020000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1319, -976, 2921, 0, 67, 0, 0x00020000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -6660, 51, -6422, 0, 67, 0, 0x00110000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 1745, 114, 5412, 0, 111, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_RED_COIN, -4849, 1349, -550, 0, -69, 0, 0x00020050, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3155, 1053, -2717, 0, -69, 0, 0x00020050, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 630, 863, -4869, 0, -69, 0, 0x00020050, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 757, 643, -2423, 0, -69, 0, 0x00020050, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -8813, 1207, -4217, 0, -69, 0, 0x00020050, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -5185, 633, -3742, 0, -69, 0, 0x00020050, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -6800, 1201, -3451, 0, -69, 0, 0x00020050, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 329, 614, -322, 0, -69, 0, 0x00020050, bhvRedCoin),
		OBJECT(MODEL_STAR, -3884, 2112, -8593, 0, -69, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_RED_FLAME, 8627, 2522, -5069, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 9127, 2522, -4477, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 8359, 2522, -4308, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 4382, 897, 7410, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(0x39, 3655, 576, 8352, 0, -139, 0, 0x05000047, bhvEasterhead),
		OBJECT(0x39, 2909, 250, 6792, 0, -139, 0, 0x00010048, bhvEasterhead),
		OBJECT(0x39, 4306, 224, 5733, 0, -177, 0, 0x00020049, bhvEasterhead),
		OBJECT(0x39, 5589, 444, 7010, 0, 92, 0, 0x0003004A, bhvEasterhead),
		OBJECT(0x39, 5285, 445, 8653, 0, -159, 0, 0x0004004B, bhvEasterhead),
		OBJECT(MODEL_BREAKABLE_BOX, 2520, 234, 6390, 0, -139, 0, 0x00030000, bhvBreakableBox),
		OBJECT(MODEL_YELLOW_COIN, 4284, 626, 5536, 0, -177, 0, 0x00020000, bhvYellowCoin),
		OBJECT(MODEL_RED_FLAME, 1178, 1075, -454, 0, 0, 0, 0x00030000, bhvFlame2),
		OBJECT(MODEL_RED_FLAME, 1437, 1075, -529, 0, 0, 0, 0x00030000, bhvFlame2),
		OBJECT(MODEL_RED_FLAME, 295, 1075, -4456, 0, 0, 0, 0x00030000, bhvFlame2),
		OBJECT(MODEL_RED_FLAME, 37, 1075, -4381, 0, 0, 0, 0x00030000, bhvFlame2),
		OBJECT(MODEL_RED_FLAME, -8311, 1521, 723, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -6051, 1233, 2171, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -2087, 913, -1588, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -7534, 3747, 3568, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -6349, 3747, 4250, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -8593, 3747, 5409, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -7409, 3747, 6092, 0, 0, 0, 0x00030000, bhvFlame),
		OBJECT(0, 9986, 230, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 280, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 330, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 380, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 430, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 480, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 530, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 580, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 630, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 680, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 730, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, 9986, 780, -7286, 0, -25, 0, 0x400B0000, bhvWarp),
		OBJECT(0, -7617, 2633, 4745, 0, -25, 0, 0x400D0000, bhvWarp),
		TERRAIN(hmc_area_1_collision),
		MACRO_OBJECTS(hmc_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_TIKI),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(2, hmc_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_HMC, 0x04, 0x0A, WARP_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_BOB, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 5125, 2948, 2613, 0, -168, 0, 0x000a0000, bhvAirborneWarp),
		OBJECT(0x35, 1157, 2948, -1732, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -10931, 3778, 3479, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x16, -7426, 5203, -8477, 0, -151, 0, 0x000B0000, bhvWarpPipe),
		OBJECT(0x35, 49, 3054, -1989, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -485, 3304, -2211, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0, -2909, 3659, -2207, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(0, 3338, 2948, -1189, 0, 90, 0, 0x00020000, bhvCoinFormation),
		OBJECT(0, 470, 4914, 5582, 0, 90, 0, 0x00020000, bhvCoinFormation),
		OBJECT(0x35, -1346, 6070, -8679, 0, -151, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, 2120, 5135, -4426, 0, 0, 0, 0x00010000, bhvFlyingTiki),
		TERRAIN(hmc_area_2_collision),
		MACRO_OBJECTS(hmc_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_HOT),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(3, hmc_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_HMC, 0x01, 0x0C, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_BOB, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -9, -667, -1563, 0, 0, 0, 0x000a0000, bhvAirborneWarp),
		OBJECT(0x36, -777, -592, -507, 0, 164, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, 744, -120, 2365, 0, 141, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, 2339, 219, 8815, 0, 6, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -4579, 590, 9747, 0, 92, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -3330, 848, 5611, 0, -1, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(0x36, -6312, 1321, 1230, 0, -1, 0, 0x00000000, bhvTikiGoomba),
		OBJECT(MODEL_NONE, -170, -493, -2493, 0, 0, 0, 0x200B0000, bhvWarp),
		OBJECT(MODEL_NONE, 128, -493, -2493, 0, 0, 0, 0x200B0000, bhvWarp),
		OBJECT(MODEL_NONE, -1625, 219, 9803, 0, 90, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 4038, 728, 2050, 0, 118, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_STAR, -8099, -596, 7002, 0, -69, 0, 0x02000000, bhvStar),
		OBJECT(MODEL_RED_FLAME, -1313, 111, 222, 0, 0, -32, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 3309, 532, 1321, 90, -58, -90, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 5934, 311, 4766, 0, -180, 32, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 3786, 311, 4766, 0, 0, -32, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -1707, 404, 8143, 90, -58, -90, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -4629, 860, 6260, 0, 0, -32, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -6952, 166, 6690, 0, -180, 32, 0x00030000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -8998, 166, 6690, 0, 0, -32, 0x00030000, bhvFlame),
		TERRAIN(hmc_area_3_collision),
		MACRO_OBJECTS(hmc_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_UNDERGROUND),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(4, hmc_area_4),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_BOB, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 1, -1868, -1707, 0, 0, 0, 0x000a0000, bhvAirborneWarp),
		OBJECT(MODEL_NONE, 0, -1868, 0, 0, -180, 0, 0x00000000, bhvTotemBoss),
		OBJECT(0x35, 0, -473, 1239, 0, 0, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, 1179, -473, 383, 0, 72, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, 728, -473, -1002, 0, 144, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -728, -473, -1002, 0, -144, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -1178, -473, 383, 0, -72, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x3A, 2619, -4648, 2321, 0, 162, 0, 1, bhvTotemPole),
		OBJECT(0x3A, 2907, -4648, 1435, 0, 162, 0, 2, bhvTotemPole),
		OBJECT(0x3A, 3195, -4648, 548, 0, 162, 0, 3, bhvTotemPole),
		OBJECT(0x3A, 3483, -4648, -339, 0, 162, 0, 4, bhvTotemPole),
		OBJECT(0x3A, 3771, -4648, -1225, 0, -162, 0, 5, bhvTotemPole),
		OBJECT(0x3A, 3017, -4648, -1773, 0, -126, 0, 6, bhvTotemPole),
		OBJECT(0x3A, 2263, -4648, -2321, 0, -126, 0, 7, bhvTotemPole),
		OBJECT(0x3A, 1509, -4648, -2869, 0, -126, 0, 8, bhvTotemPole),
		OBJECT(0x3A, 754, -4648, -3417, 0, -126, 0, 9, bhvTotemPole),
		OBJECT(0x3A, 0, -4648, -3965, 0, -90, 0, 10, bhvTotemPole),
		OBJECT(0x3A, -754, -4648, -3417, 0, -54, 0, 11, bhvTotemPole),
		OBJECT(0x3A, -1509, -4648, -2869, 0, -54, 0, 12, bhvTotemPole),
		OBJECT(0x3A, -2263, -4648, -2321, 0, -54, 0, 13, bhvTotemPole),
		OBJECT(0x3A, -3017, -4648, -1773, 0, -54, 0, 14, bhvTotemPole),
		OBJECT(0x3A, -3771, -4648, -1225, 0, -18, 0, 15, bhvTotemPole),
		OBJECT(0x3A, -3483, -4648, -339, 0, 18, 0, 16, bhvTotemPole),
		OBJECT(0x3A, -3195, -4648, 548, 0, 18, 0, 17, bhvTotemPole),
		OBJECT(0x3A, -2907, -4648, 1435, 0, 18, 0, 18, bhvTotemPole),
		OBJECT(0x3A, -2619, -4648, 2321, 0, 18, 0, 19, bhvTotemPole),
		OBJECT(0x3A, -2331, -4648, 3208, 0, 54, 0, 20, bhvTotemPole),
		OBJECT(0x3A, -1398, -4648, 3208, 0, 90, 0, 21, bhvTotemPole),
		OBJECT(0x3A, -466, -4648, 3208, 0, 90, 0, 22, bhvTotemPole),
		OBJECT(0x3A, 466, -4648, 3208, 0, 90, 0, 23, bhvTotemPole),
		OBJECT(0x3A, 1398, -4648, 3208, 0, 90, 0, 24, bhvTotemPole),
		OBJECT(0x3A, 2331, -4648, 3208, 0, 126, 0, 0, bhvTotemPole),
		OBJECT(0x35, 364, -273, 501, 0, 36, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, 589, -273, -191, 0, 108, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, 0, -273, -620, 0, -180, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -589, -273, -191, 0, -108, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(0x35, -364, -273, 501, 0, -36, 0, 0x00000000, bhvFlyingTiki),
		OBJECT(MODEL_YELLOW_COIN, 1511, -273, 2079, 0, 72, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, -1511, -273, 2079, 0, 72, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, -2444, -273, -794, 0, 72, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, 0, -273, -2570, 0, 72, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, 2444, -273, -794, 0, 72, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, 2021, -273, 657, 0, 108, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, 0, -273, 2125, 0, 108, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, -2021, -273, 657, 0, 108, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, -1249, -273, -1719, 0, 108, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_YELLOW_COIN, 1249, -273, -1719, 0, 108, 0, 0x00000000, bhvOneCoin),
		TERRAIN(hmc_area_4_collision),
		MACRO_OBJECTS(hmc_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_HOT),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
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
#include "levels/bitfs/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bitfs_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x07, _bitfs_segment_7SegmentRomStart, _bitfs_segment_7SegmentRomEnd), 
	LOAD_MIO0_TEXTURE(0x09, _sky_mio0SegmentRomStart, _sky_mio0SegmentRomEnd), 
	LOAD_MIO0(0x0A, _bitfs_skybox_mio0SegmentRomStart, _bitfs_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0(0x0B, _effect_mio0SegmentRomStart, _effect_mio0SegmentRomEnd), 
	LOAD_MIO0(0x05, _group2_mio0SegmentRomStart, _group2_mio0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group2_geoSegmentRomStart, _group2_geoSegmentRomEnd), 
	LOAD_MIO0(0x06, _group17_mio0SegmentRomStart, _group17_mio0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd), 
	LOAD_MIO0(0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_3), 
	JUMP_LINK(script_func_global_18), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(0x35, blockgolem_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bitfs_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, -250, 1000, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -121, 45, -1016, 0, -180, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, -7250, 0, -2250, 0, 0, 0, (0 << 24) | (0 << 16), bhvStar),
		OBJECT(0x35, 250, 0, -250, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -250, 0, -250, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -6500, 250, -2500, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -6500, 250, -3000, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -6500, 250, -2000, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -6500, 250, -1500, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -7000, 250, -2500, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -7000, 250, -3000, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -7000, 250, -2000, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -7000, 250, -1500, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -7500, 250, -2500, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -7500, 250, -3000, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -7500, 250, -2000, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -7500, 250, -1500, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -8000, 250, -2500, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -8000, 250, -3000, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -8000, 250, -2000, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -8000, 250, -1500, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, 250, 500, -250, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		OBJECT(0x35, -250, 500, -250, 0, -180, 0, (0x01 << 16), bhvGolemBlock),
		TERRAIN(bitfs_area_1_collision),
		MACRO_OBJECTS(bitfs_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, bitfs_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, -250, 3500, -6250, 0, 0, 0, (1 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitfs_area_2_collision),
		MACRO_OBJECTS(bitfs_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, bitfs_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 100, 250, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(0, 750, 800, -1000, 0, 0, 0, (2 << 24) | (0 << 16) | (0 << 8) | (0), bhvHiddenRedCoinStar),
		OBJECT(MODEL_RED_COIN, -2750, 1300, 2500, 0, 0, 0, (0 << 24) | (0 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 0, 1400, -4750, 0, 0, 0, (0 << 24) | (0 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 500, 1243, 4000, 0, 0, 0, (0 << 24) | (0 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1553, 183, -2478, 0, 0, 0, (0 << 24) | (0 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 2382, 900, 1250, 0, 0, 0, (0 << 24) | (0 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -605, 550, 985, 0, 0, 0, (0 << 24) | (0 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1250, 150, -4000, 0, 0, 0, (0 << 24) | (0 << 16), bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2500, 550, -500, 0, 0, 0, (0 << 24) | (0 << 16), bhvRedCoin),
		TERRAIN(bitfs_area_3_collision),
		MACRO_OBJECTS(bitfs_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, bitfs_area_4),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(0, 500, 1093, -2500, 0, 0, 0, (3 << 24) | (0 << 16), bhvHiddenStar),
		OBJECT(0, -250, 1643, -3500, 0, 0, 0, (3 << 24) | (0 << 16), bhvHiddenStarTrigger),
		OBJECT(MODEL_YELLOW_COIN, -250, 1643, -3500, 0, 0, 0, (3 << 24) | (0 << 16), bhvOneCoin),
		OBJECT(0, -2250, 1643, -2533, 0, 0, 0, (3 << 24) | (0 << 16), bhvHiddenStarTrigger),
		OBJECT(MODEL_YELLOW_COIN, -2250, 1643, -2533, 0, 0, 0, (3 << 24) | (0 << 16), bhvOneCoin),
		OBJECT(0, -4482, 1893, -4029, 0, 0, 0, (3 << 24) | (0 << 16), bhvHiddenStarTrigger),
		OBJECT(MODEL_YELLOW_COIN, -4482, 1893, -4029, 0, 0, 0, (3 << 24) | (0 << 16), bhvOneCoin),
		OBJECT(0, -1505, 1893, -4700, 0, 0, 0, (3 << 24) | (0 << 16), bhvHiddenStarTrigger),
		OBJECT(MODEL_YELLOW_COIN, -1505, 1893, -4700, 0, 0, 0, (3 << 24) | (0 << 16), bhvOneCoin),
		OBJECT(0, -2942, 1643, -5537, 0, 0, 0, (3 << 24) | (0 << 16), bhvHiddenStarTrigger),
		OBJECT(MODEL_YELLOW_COIN, -2942, 1643, -5537, 0, 0, 0, (3 << 24) | (0 << 16), bhvOneCoin),
		TERRAIN(bitfs_area_4_collision),
		MACRO_OBJECTS(bitfs_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(5, bitfs_area_5),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, 250, 3289, -5500, 0, 0, 0, (4 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitfs_area_5_collision),
		MACRO_OBJECTS(bitfs_area_5_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(6, bitfs_area_6),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, -500, 3400, -2750, 0, 0, 0, (0 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitfs_area_6_collision),
		MACRO_OBJECTS(bitfs_area_6_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
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

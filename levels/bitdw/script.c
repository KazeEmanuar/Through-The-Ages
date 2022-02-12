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
#include "levels/bitdw/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bitdw_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x07, _bitdw_segment_7SegmentRomStart, _bitdw_segment_7SegmentRomEnd), 
	LOAD_MIO0(0x0A, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0_TEXTURE(0x09, _sky_mio0SegmentRomStart, _sky_mio0SegmentRomEnd), 
	LOAD_MIO0(0x05, _group11_mio0SegmentRomStart, _group11_mio0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group11_geoSegmentRomStart, _group11_geoSegmentRomEnd), 
	LOAD_MIO0(0x06, _group17_mio0SegmentRomStart, _group17_mio0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group17_geoSegmentRomStart, _group17_geoSegmentRomEnd), 
	LOAD_MIO0(0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_12), 
	JUMP_LINK(script_func_global_18), 
	JUMP_LINK(script_func_global_1), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03, geo_bitdw_0003C0), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04, geo_bitdw_0003D8), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_05, geo_bitdw_0003F0), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_06, geo_bitdw_000408), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_07, geo_bitdw_000420), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_08, geo_bitdw_000438), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_09, geo_bitdw_000450), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0A, geo_bitdw_000468), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0B, geo_bitdw_000480), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0C, geo_bitdw_000498), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0D, geo_bitdw_0004B0), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0E, geo_bitdw_0004C8), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0F, geo_bitdw_0004E0), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_10, geo_bitdw_0004F8), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_11, geo_bitdw_000510), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_WARP_PIPE, warp_pipe_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_SQUARE_PLATFORM, geo_bitdw_000558), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_SEESAW_PLATFORM, geo_bitdw_000540), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_SLIDING_PLATFORM, geo_bitdw_000528), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_FERRIS_WHEEL_AXLE, geo_bitdw_000570), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_BLUE_PLATFORM, geo_bitdw_000588), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE_FRAME4, geo_bitdw_0005A0), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE_FRAME3, geo_bitdw_0005B8), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE_FRAME2, geo_bitdw_0005D0), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE_FRAME1, geo_bitdw_0005E8), 
	LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE, geo_bitdw_000600), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bitdw_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, -180, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, 250, 2750, -6250, 0, 0, 0, (0 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitdw_area_1_collision),
		MACRO_OBJECTS(bitdw_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, bitdw_area_2),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, 250, 2750, -6250, 0, 0, 0, (1 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitdw_area_2_collision),
		MACRO_OBJECTS(bitdw_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, bitdw_area_3),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, 500, 1643, -7500, 0, 0, 0, (2 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitdw_area_3_collision),
		MACRO_OBJECTS(bitdw_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, bitdw_area_4),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, 500, 1643, -6500, 0, 0, 0, (3 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitdw_area_4_collision),
		MACRO_OBJECTS(bitdw_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(5, bitdw_area_5),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, -500, 3400, -1250, 0, 0, 0, (4 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitdw_area_5_collision),
		MACRO_OBJECTS(bitdw_area_5_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SECRET),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(6, bitdw_area_6),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE_GROUNDS, 0x01, 0xA0, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xA1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 250, 0, 500, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, (0x01 << 16), bhvTextureAnims),
		OBJECT(MODEL_STAR, -500, 3400, -2750, 0, 0, 0, (5 << 24) | (0 << 16), bhvStar),
		TERRAIN(bitdw_area_6_collision),
		MACRO_OBJECTS(bitdw_area_6_macro_objs),
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

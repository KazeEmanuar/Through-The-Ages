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
#include "levels/bits/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bits_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x07, _bits_segment_7SegmentRomStart, _bits_segment_7SegmentRomEnd), 
	LOAD_MIO0(0x0A, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0_TEXTURE(0x09, _sky_mio0SegmentRomStart, _sky_mio0SegmentRomEnd), 
	LOAD_MIO0(0x06, _group14_mio0SegmentRomStart, _group14_mio0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_MIO0(0x08, _common0_mio0SegmentRomStart, _common0_mio0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(0x35, toadlawyertw_geo), 
	LOAD_MODEL_FROM_GEO(0x36, courtDK_geo), 
	LOAD_MODEL_FROM_GEO(0x37, wariocourt_geo), 
	LOAD_MODEL_FROM_GEO(0x38, waluigi_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bits_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_ENDING, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE_GROUNDS, 0x01, 0xF1, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 425, 0, -526, 0, -90, 0, (0x0A << 16), bhvSwimmingWarp),
		OBJECT(0x35, 425, 40, -350, 0, -90, 0, (0 << 16), bhvCourtActor),
		OBJECT(0x36, 0, 0, -1030, 0, 0, 0, (1 << 16), bhvCourtActor),
		OBJECT(0x37, -433, 0, -273, 0, 90, 0, (2 << 16), bhvCourtActor),
		OBJECT(0x38, -438, 0, -473, 0, 90, 0, (3 << 16), bhvCourtActor),
		OBJECT(0, 215, 0, -1048, 0, 0, 0, (4 << 16), bhvCourtActor),
		TERRAIN(bits_area_1_collision),
		MACRO_OBJECTS(bits_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, 0x31),
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

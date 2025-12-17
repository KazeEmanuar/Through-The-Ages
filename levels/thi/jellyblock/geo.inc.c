#include "src/game/envfx_snow.h"

const GeoLayout jellyblock_geo_opt_1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, jellyblock_Bone_002_mesh_layer_4_opt_1_with_layer_4_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout jellyblock_geo_opt_2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, jellyblock_Bone_002_mesh_layer_4_opt_2_with_layer_4_revert),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout jellyblock_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, jellyblock_Bone_mesh_layer_5),
		GEO_SWITCH_CASE(3, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, jellyblock_Bone_002_mesh_layer_4),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, jellyblock_geo_opt_1),
			GEO_BRANCH(1, jellyblock_geo_opt_2),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

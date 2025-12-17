#include "src/game/envfx_snow.h"

const GeoLayout retropiranha_Armature_001[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, retropiranha_Bone_Bone_001_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout retropiranha_geo[] = {
	GEO_CULLING_RADIUS(520),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(2, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, retropiranha_Bone_Bone_001_mesh_layer_4),
			GEO_DISPLAY_LIST(LAYER_ALPHA, retropiranha_Bone_002_mesh_layer_4),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, retropiranha_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

#include "src/game/envfx_snow.h"

const GeoLayout fliptiles_Armature_002[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, fliptiles_Bone_bonie_mesh),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout fliptiles_Armature_003[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, fliptiles_Bone_boneface_mesh),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout fliptiles_Armature_004[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, fliptiles_Bone_boneboy_mesh),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout fliptiles_geo[] = {
   GEO_CULLING_RADIUS(1000),
   GEO_OPEN_NODE(),
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(4, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, fliptiles_Bone_001_mesh),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, fliptiles_Armature_002),
			GEO_BRANCH(1, fliptiles_Armature_003),
			GEO_BRANCH(1, fliptiles_Armature_004),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, fliptiles_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_OPEN_NODE(),
	GEO_END(),
};

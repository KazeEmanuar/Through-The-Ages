#include "src/game/envfx_snow.h"

const GeoLayout booguy_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 0, 0, booguy_Bone_mesh_layer_5),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, booguy_Bone_001_skinned_mesh_layer_5),
			GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 71, 0, booguy_Bone_001_mesh_layer_5),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, booguy_Bone_003_skinned_mesh_layer_5),
			GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, 38, -42, booguy_Bone_003_mesh_layer_5),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, booguy_arm_l_skinned_mesh_layer_5),
			GEO_ANIMATED_PART(LAYER_TRANSPARENT, 27, 56, 11, booguy_arm_l_mesh_layer_5),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, booguy_arm_r_skinned_mesh_layer_5),
			GEO_ANIMATED_PART(LAYER_TRANSPARENT, -27, 56, 11, booguy_arm_r_mesh_layer_5),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

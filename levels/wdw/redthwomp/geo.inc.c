#include "src/game/envfx_snow.h"

const GeoLayout redthwomp_Bone_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, redthwomp_Bone_001_mesh_layer_1_mat_override_Q_Diamonds_v4_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout redthwomp_Bone_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, redthwomp_Bone_001_mesh_layer_1_mat_override_J_Diamond_v4_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout redthwomp_Bone_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, redthwomp_Bone_001_mesh_layer_1_mat_override_A_Diamond_v4_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout redthwomp_Bone_opt4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, redthwomp_Bone_001_mesh_layer_1_mat_override_K_Hearts_v4_3),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout redthwomp_Bone_opt5[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, redthwomp_Bone_001_mesh_layer_1_mat_override_Q_Hearts_v4_4),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout redthwomp_Bone_opt6[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, redthwomp_Bone_001_mesh_layer_1_mat_override_J_Hearts_v4_5),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout redthwomp_Bone_opt7[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, redthwomp_Bone_001_mesh_layer_1_mat_override_A_Hearts_v4_6),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout redthwomp_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(8, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 100, 0, redthwomp_Bone_001_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, redthwomp_Bone_opt1),
			GEO_BRANCH(1, redthwomp_Bone_opt2),
			GEO_BRANCH(1, redthwomp_Bone_opt3),
			GEO_BRANCH(1, redthwomp_Bone_opt4),
			GEO_BRANCH(1, redthwomp_Bone_opt5),
			GEO_BRANCH(1, redthwomp_Bone_opt6),
			GEO_BRANCH(1, redthwomp_Bone_opt7),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, redthwomp_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
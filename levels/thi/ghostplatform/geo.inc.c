#include "src/game/envfx_snow.h"

// custom edited
const GeoLayout ghostplatform_geo[] = {
	GEO_CULLING_RADIUS(1500),
	GEO_OPEN_NODE(),
		GEO_ASM(1, geo_GhostPlatform),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ghostplatform_Bone_mesh_layer_1),
		GEO_SWITCH_CASE(2, geo_switch_anim_state),
		GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ghostplatform_Bone_002_mesh_layer_5),
				GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mat_revert_ghostplatform_f3d_material_002),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

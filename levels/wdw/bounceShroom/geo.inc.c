#include "src/game/envfx_snow.h"

const GeoLayout bounceShroom_geo[] = {
	GEO_CULLING_RADIUS(700),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, bounceShroom_Bone_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_ASM(0, geo_set_prim),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 278, 0, bounceShroom_Bone_002_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bounceShroom_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

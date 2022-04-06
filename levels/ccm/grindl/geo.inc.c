#include "src/game/envfx_snow.h"

const GeoLayout grindl_geo[] = {
	GEO_CULLING_RADIUS(700),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, grindl_skinned_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, grindl_skinned_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, grindl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, grindl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

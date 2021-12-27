#include "src/game/envfx_snow.h"

const GeoLayout wigglerhead2_geo[] = {
	GEO_CULLING_RADIUS(7000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wigglerhead2_Cube_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, wigglerhead2_Cube_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wigglerhead2_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, wigglerhead2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

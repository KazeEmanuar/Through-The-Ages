#include "src/game/envfx_snow.h"

const GeoLayout wigglerhead_geo[] = {
	GEO_CULLING_RADIUS(7000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wigglerhead_Cube_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, wigglerhead_Cube_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wigglerhead_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, wigglerhead_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

#include "src/game/envfx_snow.h"

const GeoLayout totempole_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, totempole_Cube_mesh_layer_1),
		GEO_DISPLAY_LIST(1, totempole_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
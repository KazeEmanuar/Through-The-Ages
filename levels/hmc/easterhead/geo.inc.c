#include "src/game/envfx_snow.h"

const GeoLayout easterhead_geo[] = {
	GEO_CULLING_RADIUS(1500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, easterhead_Cube_mesh_layer_1),
		GEO_DISPLAY_LIST(1, easterhead_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

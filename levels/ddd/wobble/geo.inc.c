#include "src/game/envfx_snow.h"

const GeoLayout wobble_geo[] = {
	GEO_CULLING_RADIUS(5000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, wobble_Circle_mesh_layer_1),
		GEO_DISPLAY_LIST(1, wobble_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

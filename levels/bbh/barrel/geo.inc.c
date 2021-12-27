#include "src/game/envfx_snow.h"

const GeoLayout barrel_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, barrel_polygon_02_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, barrel_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

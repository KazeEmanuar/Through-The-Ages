#include "src/game/envfx_snow.h"

const GeoLayout jetski_geo2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, jetski_jetski_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, jetski_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

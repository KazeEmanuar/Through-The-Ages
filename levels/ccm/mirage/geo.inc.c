#include "src/game/envfx_snow.h"

const GeoLayout mirage_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mirage_mirage_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mirage_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

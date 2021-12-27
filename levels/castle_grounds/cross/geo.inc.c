#include "src/game/envfx_snow.h"

const GeoLayout cross_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, cross_Plane_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, cross_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

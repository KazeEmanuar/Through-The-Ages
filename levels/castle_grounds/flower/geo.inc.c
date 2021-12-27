#include "src/game/envfx_snow.h"

const GeoLayout flower_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, flower_Plane_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, flower_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

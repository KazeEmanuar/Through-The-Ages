#include "src/game/envfx_snow.h"

const GeoLayout chandelier_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, chandelier_Circle_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, chandelier_Circle_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

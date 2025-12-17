#include "src/game/envfx_snow.h"

const GeoLayout Catchnet_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, Catchnet_bignet_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

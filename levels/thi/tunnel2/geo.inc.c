#include "src/game/envfx_snow.h"

const GeoLayout tunnel2_geo[] = {
	GEO_CULLING_RADIUS(7000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tunnel2_Plane_002_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

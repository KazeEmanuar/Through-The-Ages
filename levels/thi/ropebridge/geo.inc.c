#include "src/game/envfx_snow.h"

const GeoLayout ropebridge_geo[] = {
	GEO_CULLING_RADIUS(2500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, ropebridge_Plane_031_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

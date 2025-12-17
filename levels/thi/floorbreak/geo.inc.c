#include "src/game/envfx_snow.h"

const GeoLayout floorbreak_geo[] = {
	GEO_CULLING_RADIUS(1200),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, floorbreak_Plane_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

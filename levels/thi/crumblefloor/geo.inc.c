#include "src/game/envfx_snow.h"

const GeoLayout crumblefloor_geo[] = {
	GEO_CULLING_RADIUS(750),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, crumblefloor_Plane_044_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

#include "src/game/envfx_snow.h"

const GeoLayout pushcargobox_geo[] = {
	GEO_CULLING_RADIUS(1500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pushcargobox_Plane_032_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, pushcargobox_Plane_032_mesh_layer_6),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

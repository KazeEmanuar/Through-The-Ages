#include "src/game/envfx_snow.h"

const GeoLayout medusagate_geo[] = {
	GEO_CULLING_RADIUS(7000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(4, medusagate_Plane_mesh_layer_4),
		GEO_DISPLAY_LIST(4, medusagate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
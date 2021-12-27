#include "src/game/envfx_snow.h"

const GeoLayout treasuredoor_geo[] = {
	GEO_CULLING_RADIUS(4000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, treasuredoor_world_006_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, treasuredoor_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

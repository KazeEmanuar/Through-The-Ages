#include "src/game/envfx_snow.h"

const GeoLayout kaioplanet_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, kaioplanet_Visualk_mesh_layer_1),
		GEO_DISPLAY_LIST(4, kaioplanet_Visualk_mesh_layer_4),
		GEO_DISPLAY_LIST(1, kaioplanet_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, kaioplanet_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

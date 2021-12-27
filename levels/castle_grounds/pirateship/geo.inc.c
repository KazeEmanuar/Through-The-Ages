#include "src/game/envfx_snow.h"

const GeoLayout pirateship_geo[] = {
	GEO_CULLING_RADIUS(9000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, pirateship_DrawCall_69_mesh_layer_1),
		GEO_DISPLAY_LIST(4, pirateship_DrawCall_69_mesh_layer_4),
		GEO_DISPLAY_LIST(1, pirateship_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, pirateship_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

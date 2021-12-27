#include "src/game/envfx_snow.h"

const GeoLayout jetski_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(1, 0, 0, 0, 0, 0, 0, jetski_jetski_mesh),
		GEO_DISPLAY_LIST(0, jetski_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, jetski_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, jetski_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, jetski_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, jetski_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, jetski_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, jetski_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, jetski_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

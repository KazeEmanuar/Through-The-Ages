#include "src/game/envfx_snow.h"

const GeoLayout icebeam[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(6, 0, 0, 0, 0, 0, 0, icebeam_Cube_mesh),
		GEO_DISPLAY_LIST(0, icebeam_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, icebeam_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, icebeam_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, icebeam_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, icebeam_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, icebeam_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, icebeam_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, icebeam_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

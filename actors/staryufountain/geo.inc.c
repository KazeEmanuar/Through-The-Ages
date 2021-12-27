#include "src/game/envfx_snow.h"

const GeoLayout staryufountain_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(5, 0, 0, 0, 0, 0, 0, staryufountain_Cube_mesh),
		GEO_DISPLAY_LIST(0, staryufountain_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, staryufountain_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, staryufountain_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, staryufountain_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, staryufountain_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, staryufountain_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, staryufountain_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, staryufountain_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

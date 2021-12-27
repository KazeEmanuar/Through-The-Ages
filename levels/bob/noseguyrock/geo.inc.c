#include "src/game/envfx_snow.h"

const GeoLayout noseguyrock_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(1, 0, 0, 0, 0, 0, 0, noseguyrock_stone_mesh),
		GEO_DISPLAY_LIST(0, noseguyrock_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, noseguyrock_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, noseguyrock_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, noseguyrock_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, noseguyrock_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, noseguyrock_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, noseguyrock_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, noseguyrock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

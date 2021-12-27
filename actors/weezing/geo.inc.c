#include "src/game/envfx_snow.h"

const GeoLayout weezing_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(1, 43, 0, -98, 90, 0, 0),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(1, 0, 0, 0, weezing_Bone_mesh),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(0, weezing_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, weezing_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, weezing_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, weezing_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, weezing_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, weezing_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, weezing_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, weezing_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

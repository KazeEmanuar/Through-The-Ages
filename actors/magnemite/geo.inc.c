#include "src/game/envfx_snow.h"

const GeoLayout magnemite_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(1, 0, -2, 37, 90, -1, -1),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(1, 0, 0, 0, magnemite_head_mesh),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(1, magnemite_expression_skinned),
				GEO_TRANSLATE_ROTATE(1, 0, 0, -6, -14, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(1, 0, 0, 0, magnemite_expression_mesh),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(1, 42, 0, -2, -90, 0, -87),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(1, 0, 0, 0, magnemite_magnet_L_mesh),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(1, -42, 0, -2, -90, 0, 87),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(1, 0, 0, 0, magnemite_magnet_R_mesh),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(1, 12, 19, 24, 19, 0, -17),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(1, 0, 0, 0, magnemite_screw_L_mesh),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(1, -12, 19, 24, 19, 0, 17),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(1, 0, 0, 0, magnemite_screw_R_mesh),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(1, 0, 0, -36, -90, -1, 1),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(1, 0, 0, 0, magnemite_topScrew_mesh),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(0, magnemite_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, magnemite_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, magnemite_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, magnemite_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, magnemite_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, magnemite_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, magnemite_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, magnemite_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
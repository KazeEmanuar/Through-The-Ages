#include "src/game/envfx_snow.h"

const GeoLayout dolphin_geo[] = {
	GEO_CULLING_RADIUS(2500),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(1, 0, 3, 206, 0, -90, 91),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(1, 0, 0, 0, dolphin_head_mesh),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(1, dolphin_body1_skinned),
				GEO_TRANSLATE_ROTATE(1, 0, 146, 0, 0, 90, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(1, 0, 0, 0, dolphin_body1_mesh),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(1, dolphin_body3_skinned),
						GEO_TRANSLATE_ROTATE(1, 0, 123, 0, 0, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(1, 0, 0, 0, dolphin_body3_mesh),
							GEO_OPEN_NODE(),
								GEO_DISPLAY_LIST(1, dolphin_body4_skinned),
								GEO_TRANSLATE_ROTATE(1, 0, 89, 0, -1, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(1, 0, 0, 0, dolphin_body4_mesh),
									GEO_OPEN_NODE(),
										GEO_DISPLAY_LIST(1, dolphin_body7_skinned),
										GEO_TRANSLATE_ROTATE(1, 0, 134, 0, 1, 0, 0),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(1, 0, 0, 0, dolphin_body7_mesh),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
						GEO_TRANSLATE_ROTATE(1, 61, 30, -21, -4, 22, -79),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(1, 0, 0, 0, dolphin_fin1L_mesh),
						GEO_CLOSE_NODE(),
						GEO_TRANSLATE_ROTATE(1, -61, 30, -21, -51, 144, -73),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(1, 0, 0, 0, dolphin_fin1R_mesh),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(1, -28, 90, 0, 0, 0, 170),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(1, 0, 0, 0, dolphin_mouth_mesh),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(0, dolphin_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, dolphin_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, dolphin_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, dolphin_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, dolphin_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, dolphin_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, dolphin_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, dolphin_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
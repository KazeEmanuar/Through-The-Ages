#include "src/game/envfx_snow.h"

const GeoLayout zeus_geo[] = {
	GEO_CULLING_RADIUS(32000),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 1, -8, 9, 0, 0),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_body_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 30, 38, -9, 177, 17, -46),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_arm_L_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 26, 0, -2, 98, -16),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_forearm_L_mesh_layer_1),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 23, 0, -8, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_hand_L_mesh_layer_1),
									GEO_OPEN_NODE(),
										GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 23, 4, -75, 0, 0),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -30, 38, -9, 177, -17, 46),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_arm_R_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 26, 0, -2, -98, 16),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_forearm_R_mesh_layer_1),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 23, 0, -8, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_hand_R_mesh_layer_1),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 48, 0, 1, -180, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_head_mesh_layer_1),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 18, -8, -2, 172, 8, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_tigh_L_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 41, 0, 1, 98, -1),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_chin_L_mesh_layer_1),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 25, 0, 69, 84, -6),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_foot_L_mesh_layer_1),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -18, -8, -2, 172, -8, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_tigh_R_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 41, 0, 1, -98, 1),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_chin_R_mesh_layer_1),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 25, 0, 69, -84, 6),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, zeus_foot_R_mesh_layer_1),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, zeus_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

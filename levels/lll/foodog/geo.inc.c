#include "src/game/envfx_snow.h"

const GeoLayout foodog_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 104, 0, -120, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
				GEO_OPEN_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 97, 0, 73, 0, 0),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
						GEO_OPEN_NODE(),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 42, 0, 10, 0, 0),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_003_mesh),
								GEO_OPEN_NODE(),
									GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_Bone_004_skinned),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 57, 0, 13, 0, 0),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_004_mesh),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 97, 0, 0, 0, -90),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
						GEO_OPEN_NODE(),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 48, 0, -13, -5, -63),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_006_L_mesh),
								GEO_OPEN_NODE(),
									GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_Bone_007_L_skinned),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 73, 0, -143, 65, -22),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_007_L_mesh),
										GEO_OPEN_NODE(),
											GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_Bone_008_L_skinned),
											GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 86, 0, 45, -75, -123),
											GEO_OPEN_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_008_L_mesh),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 97, 0, 0, 0, 90),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
						GEO_OPEN_NODE(),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 48, 0, -13, 5, 63),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_006_R_mesh),
								GEO_OPEN_NODE(),
									GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_Bone_007_R_skinned),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 73, 0, -143, -65, 22),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_007_R_mesh),
										GEO_OPEN_NODE(),
											GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_Bone_008_R_skinned),
											GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 86, 0, 45, 75, 123),
											GEO_OPEN_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_008_R_mesh),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 104, 0, 12, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_005_mesh),
				GEO_OPEN_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 121, 0, 124, 0, 0),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
						GEO_OPEN_NODE(),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 94, 0, 31, 0, 0),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, foodog_Bone_008_mesh),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 121, 0, 29, 0, 0),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_009_mesh),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_Bone_006_skinned),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 44, 0, 79, 0, 0),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_Bone_006_mesh),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 104, 0, 36, 0, -55),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
				GEO_OPEN_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 83, 0, 34, -65, -142),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_b_l_mesh),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_c_l_skinned),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 75, 0, 8, 4, 29),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_c_l_mesh),
								GEO_OPEN_NODE(),
									GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_d_l_skinned),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 61, 0, 22, 19, 73),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_d_l_mesh),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 104, 0, 36, 0, 55),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
				GEO_OPEN_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 83, 0, 34, 65, 142),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_b_r_mesh),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_c_r_skinned),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 75, 0, 8, -4, -29),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_c_r_mesh),
								GEO_OPEN_NODE(),
									GEO_DISPLAY_LIST(LAYER_OPAQUE, foodog_d_r_skinned),
									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 61, 0, 22, -19, -73),
									GEO_OPEN_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, foodog_d_r_mesh),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

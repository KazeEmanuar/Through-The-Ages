#include "src/game/envfx_snow.h"

const GeoLayout dragonbridge_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, -4, 293, 0, 90, -90),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_root_mesh_layer_4),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine1_skinned_mesh_layer_4),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 313, 0, 7, -90, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine1_mesh_layer_4),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine2_skinned_mesh_layer_4),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 169, 0, 3, -180, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine2_mesh_layer_4),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 129, 0, -76, -20, 135),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_Bone_001_mesh_layer_1),
									GEO_OPEN_NODE(),
										GEO_DISPLAY_LIST(LAYER_OPAQUE, dragonbridge_arm_L_skinned_mesh_layer_1),
										GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 236, 0, -21, -159, -67),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_arm_L_mesh_layer_1),
											GEO_OPEN_NODE(),
												GEO_DISPLAY_LIST(LAYER_OPAQUE, dragonbridge_forearm_L_skinned_mesh_layer_1),
												GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 127, 0, -53, -180, 5),
												GEO_OPEN_NODE(),
													GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_forearm_L_mesh_layer_1),
												GEO_CLOSE_NODE(),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 129, 0, -76, 20, -135),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_Bone_002_mesh_layer_1),
									GEO_OPEN_NODE(),
										GEO_DISPLAY_LIST(LAYER_OPAQUE, dragonbridge_arm_R_skinned_mesh_layer_1),
										GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 236, 0, -23, 156, 68),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_arm_R_mesh_layer_1),
											GEO_OPEN_NODE(),
												GEO_DISPLAY_LIST(LAYER_OPAQUE, dragonbridge_forearm_R_skinned_mesh_layer_1),
												GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 129, 0, -59, 180, -6),
												GEO_OPEN_NODE(),
													GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_forearm_R_mesh_layer_1),
												GEO_CLOSE_NODE(),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
								GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine3_skinned_mesh_layer_4),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 129, 0, -1, 180, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine3_mesh_layer_4),
									GEO_OPEN_NODE(),
										GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine4_skinned_mesh_layer_4),
										GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 126, 0, -1, 0, 0),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine4_mesh_layer_4),
											GEO_OPEN_NODE(),
												GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine5_skinned_mesh_layer_4),
												GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 127, 0, -1, 0, 0),
												GEO_OPEN_NODE(),
													GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine5_mesh_layer_4),
													GEO_OPEN_NODE(),
														GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine6_skinned_mesh_layer_4),
														GEO_ANIMATED_PART(LAYER_ALPHA, 0, 128, 0, dragonbridge_spine6_mesh_layer_4),
														GEO_OPEN_NODE(),
															GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine7_skinned_mesh_layer_4),
															GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 131, 0, -2, 0, 0),
															GEO_OPEN_NODE(),
																GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine7_mesh_layer_4),
																GEO_OPEN_NODE(),
																	GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine8_skinned_mesh_layer_4),
																	GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 141, 0, -2, 0, 0),
																	GEO_OPEN_NODE(),
																		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine8_mesh_layer_4),
																		GEO_OPEN_NODE(),
																			GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine9_skinned_mesh_layer_4),
																			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 140, 0, 1, 0, 0),
																			GEO_OPEN_NODE(),
																				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine9_mesh_layer_4),
																				GEO_OPEN_NODE(),
																					GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine10_skinned_mesh_layer_4),
																					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 137, 0, -2, 0, 0),
																					GEO_OPEN_NODE(),
																						GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine10_mesh_layer_4),
																						GEO_OPEN_NODE(),
																							GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine11_skinned_mesh_layer_4),
																							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 136, 0, -2, 0, 0),
																							GEO_OPEN_NODE(),
																								GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine11_mesh_layer_4),
																								GEO_OPEN_NODE(),
																									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 141, 0, -115, -38, -38),
																									GEO_OPEN_NODE(),
																										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
																									GEO_CLOSE_NODE(),
																									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 141, 0, -115, 38, 38),
																									GEO_OPEN_NODE(),
																										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
																									GEO_CLOSE_NODE(),
																									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 211, 67, -42, -10, 0, -180),
																									GEO_OPEN_NODE(),
																										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_leg_L_mesh_layer_1),
																										GEO_OPEN_NODE(),
																											GEO_DISPLAY_LIST(LAYER_OPAQUE, dragonbridge_foreleg_L_skinned_mesh_layer_1),
																											GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 143, 0, 36, 0, 180),
																											GEO_OPEN_NODE(),
																												GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_foreleg_L_mesh_layer_1),
																											GEO_CLOSE_NODE(),
																										GEO_CLOSE_NODE(),
																									GEO_CLOSE_NODE(),
																									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -211, 67, -42, -10, 0, 180),
																									GEO_OPEN_NODE(),
																										GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_leg_R_mesh_layer_1),
																										GEO_OPEN_NODE(),
																											GEO_DISPLAY_LIST(LAYER_OPAQUE, dragonbridge_foreleg_R_skinned_mesh_layer_1),
																											GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 143, 0, 36, 0, 180),
																											GEO_OPEN_NODE(),
																												GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, dragonbridge_foreleg_R_mesh_layer_1),
																											GEO_CLOSE_NODE(),
																										GEO_CLOSE_NODE(),
																									GEO_CLOSE_NODE(),
																									GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine12_skinned_mesh_layer_4),
																									GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 141, 0, -2, 0, 0),
																									GEO_OPEN_NODE(),
																										GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine12_mesh_layer_4),
																										GEO_OPEN_NODE(),
																											GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine13_skinned_mesh_layer_4),
																											GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 146, 0, 1, 0, 0),
																											GEO_OPEN_NODE(),
																												GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine13_mesh_layer_4),
																												GEO_OPEN_NODE(),
																													GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine14_skinned_mesh_layer_4),
																													GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 141, 0, 2, 0, 0),
																													GEO_OPEN_NODE(),
																														GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine14_mesh_layer_4),
																														GEO_OPEN_NODE(),
																															GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_spine15_skinned_mesh_layer_4),
																															GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 172, 0, -1, 0, 0),
																															GEO_OPEN_NODE(),
																																GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, dragonbridge_spine15_mesh_layer_4),
																															GEO_CLOSE_NODE(),
																														GEO_CLOSE_NODE(),
																													GEO_CLOSE_NODE(),
																												GEO_CLOSE_NODE(),
																											GEO_CLOSE_NODE(),
																										GEO_CLOSE_NODE(),
																									GEO_CLOSE_NODE(),
																								GEO_CLOSE_NODE(),
																							GEO_CLOSE_NODE(),
																						GEO_CLOSE_NODE(),
																					GEO_CLOSE_NODE(),
																				GEO_CLOSE_NODE(),
																			GEO_CLOSE_NODE(),
																		GEO_CLOSE_NODE(),
																	GEO_CLOSE_NODE(),
																GEO_CLOSE_NODE(),
															GEO_CLOSE_NODE(),
														GEO_CLOSE_NODE(),
													GEO_CLOSE_NODE(),
												GEO_CLOSE_NODE(),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, dragonbridge_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, dragonbridge_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
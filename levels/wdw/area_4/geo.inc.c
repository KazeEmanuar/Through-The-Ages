#include "src/game/envfx_snow.h"

const GeoLayout wdw_area_4_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wdw_dl_Circle_020_mesh_layer_1),
		GEO_ASM(0, background_translate),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wdw_dl_Circle_021_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 355, 204, -366, wdw_dl_Circle_022_mesh_layer_1),
		GEO_TRANSLATE_NODE(LAYER_OPAQUE, 355, 204, -366),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_TRANSPARENT, 355, 204, -366, wdw_dl_Circle_024_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wdw_dl_Cube_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, wdw_dl_Cube_001_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout wdw_area_4[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(0),
		GEO_OPEN_NODE(),
			GEO_NODE_ORTHO(100.0000),
			GEO_OPEN_NODE(),
				GEO_BACKGROUND_COLOR(0x9257),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 50000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 430, 0, 51954, 430, -1, 51954, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, wdw_area_4_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, wdw_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, wdw_dl_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, wdw_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

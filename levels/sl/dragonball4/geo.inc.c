#include "src/game/envfx_snow.h"

const GeoLayout dragonball_geo4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(5, dragonball4_Icosphere_003_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -8, -4, -22, dragonball4_Plane_006_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 18, 17, -4, dragonball4_Plane_007_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 2, -6, 18, dragonball4_Plane_008_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -24, 19, -1, dragonball4_Plane_009_mesh_layer_5),
		GEO_DISPLAY_LIST(5, dragonball4_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

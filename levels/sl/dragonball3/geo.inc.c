#include "src/game/envfx_snow.h"

const GeoLayout dragonball_geo3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(5, dragonball3_Icosphere_002_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -8, 9, -16, dragonball3_Plane_003_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 18, 4, -4, dragonball3_Plane_004_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 2, -6, 16, dragonball3_Plane_005_mesh_layer_5),
		GEO_DISPLAY_LIST(5, dragonball3_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

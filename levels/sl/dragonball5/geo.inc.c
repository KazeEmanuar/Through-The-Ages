#include "src/game/envfx_snow.h"

const GeoLayout dragonball_geo5[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(5, dragonball5_Icosphere_004_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -16, -22, -20, dragonball5_Plane_010_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 29, -18, -1, dragonball5_Plane_011_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 19, 15, 23, dragonball5_Plane_012_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -27, 19, 0, dragonball5_Plane_013_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 0, 0, 0, dragonball5_Plane_014_mesh_layer_5),
		GEO_DISPLAY_LIST(5, dragonball5_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

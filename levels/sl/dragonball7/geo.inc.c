#include "src/game/envfx_snow.h"

const GeoLayout dragonball_geo7[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(5, dragonball7_Icosphere_006_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -22, -22, -17, dragonball7_Plane_021_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 32, -18, 6, dragonball7_Plane_022_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 19, 15, 23, dragonball7_Plane_023_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -27, 19, 0, dragonball7_Plane_024_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -10, -6, 20, dragonball7_Plane_025_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 13, 9, -21, dragonball7_Plane_026_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 0, 0, 0, dragonball7_Plane_027_mesh_layer_5),
		GEO_DISPLAY_LIST(5, dragonball7_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

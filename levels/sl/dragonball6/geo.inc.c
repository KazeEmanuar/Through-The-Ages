#include "src/game/envfx_snow.h"

const GeoLayout dragonball_geo6[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(5, dragonball6_Icosphere_005_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -16, -22, -20, dragonball6_Plane_015_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 29, -18, -1, dragonball6_Plane_016_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 19, 15, 23, dragonball6_Plane_017_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -27, 19, 0, dragonball6_Plane_018_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -9, -6, 16, dragonball6_Plane_019_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 12, 9, -15, dragonball6_Plane_020_mesh_layer_5),
		GEO_DISPLAY_LIST(5, dragonball6_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

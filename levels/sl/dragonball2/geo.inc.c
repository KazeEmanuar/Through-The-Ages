#include "src/game/envfx_snow.h"

const GeoLayout dragonball_geo2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(5, dragonball2_Icosphere_001_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, -8, 9, -8, dragonball2_Plane_001_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 12, -15, 9, dragonball2_Plane_002_mesh_layer_5),
		GEO_DISPLAY_LIST(5, dragonball2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

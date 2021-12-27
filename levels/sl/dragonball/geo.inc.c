#include "src/game/envfx_snow.h"

const GeoLayout dragonball_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(5, dragonball_Icosphere_mesh_layer_5),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(5, 0, 0, 0, dragonball_Plane_mesh_layer_5),
		GEO_DISPLAY_LIST(5, dragonball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

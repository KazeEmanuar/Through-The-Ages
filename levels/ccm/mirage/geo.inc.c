#include "src/game/envfx_snow.h"

const GeoLayout mirage_geo[] = {
	GEO_CULLING_RADIUS(30000),
	GEO_OPEN_NODE(),
		GEO_ASM(0, geo_prim_from_opacity),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mirage_Mesh_002_rdmobj15_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mirage_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

#include "src/game/envfx_snow.h"

const GeoLayout paintguy_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(LAYER_TRANSPARENT_DECAL, set_prim_to_opacity),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, paintguy_Plane_027_mesh_layer_6),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

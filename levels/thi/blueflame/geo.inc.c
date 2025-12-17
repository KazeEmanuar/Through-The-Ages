#include "src/game/envfx_snow.h"

const GeoLayout blueflame_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		//GEO_ASM(5, geo_flame_shear),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, blueflame_Circle_001_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

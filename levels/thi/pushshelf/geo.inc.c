#include "src/game/envfx_snow.h"

const GeoLayout pushshelf_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(1, geo_set_primOpa),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pushshelf_Room3Layer1_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

#include "src/game/envfx_snow.h"

const GeoLayout DoubleDoor_Geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, DoubleDoor_Room2Layer1_004_mesh_layer_4),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

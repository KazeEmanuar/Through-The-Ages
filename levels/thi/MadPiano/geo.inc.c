#include "src/game/envfx_snow.h"

const GeoLayout MadPiano_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, MadPiano_Bone_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, MadPiano_Bone_mesh_layer_4),
			GEO_ANIMATED_PART(LAYER_ALPHA, -564, 593, 0, MadPiano_Bone_002_mesh_layer_4),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

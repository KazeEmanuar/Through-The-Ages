#include "src/game/envfx_snow.h"

const GeoLayout booguybarrell_geo2[] = {
	GEO_CULLING_RADIUS(1500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, booguybarrell2_Bone_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, booguybarrell2_Bone_001_skinned_mesh_layer_1),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 202, -72, booguybarrell2_Bone_001_mesh_layer_1),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 107, -107, NULL),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 81, 194, NULL),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_TRANSPARENT, 0, -202, -84, booguybarrell2_Bone_005_mesh_layer_5),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

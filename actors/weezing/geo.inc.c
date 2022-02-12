#include "src/game/envfx_snow.h"

const GeoLayout weezing_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 43, 0, -98, 90, 0, 0),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, weezing_Bone_mesh_layer_1),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, weezing_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

#include "src/game/envfx_snow.h"

const GeoLayout smallblargg_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 0, 0, -11, 0, 0),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, smallblargg_Bone_mesh),
			GEO_OPEN_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 96, 0, 74, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, smallblargg_Bone_001_mesh),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 96, 0, 112, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, smallblargg_Bone_002_mesh),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, smallblargg_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, smallblargg_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

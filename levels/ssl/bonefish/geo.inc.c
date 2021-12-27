#include "src/game/envfx_snow.h"

const GeoLayout bonefish_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SCALE(LAYER_FORCE, 16384),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, -16, 0, 0, NULL),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, bonefish_000_offset_001_mesh_layer_4),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 97, 0, 0, bonefish_000_offset_002_mesh_layer_4),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bonefish_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

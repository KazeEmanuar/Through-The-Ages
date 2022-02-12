#include "src/game/envfx_snow.h"

const GeoLayout haunter_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, haunter_head_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 79, -9, 62, 71, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, haunter_hand_L_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -79, -9, 62, 71, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, haunter_hand_R_mesh_layer_1),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, haunter_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

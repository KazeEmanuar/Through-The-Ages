#include "src/game/envfx_snow.h"

const GeoLayout tikigoomba_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x96, 100),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 21, 0, tikigoomba_head_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, tikigoomba_head_mesh_layer_4),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, -3, 0, -179, 0, 0),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, tikigoomba_body_mesh_layer_4),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 10, -1, 1, NULL),
					GEO_OPEN_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 14, 0, -81, 0, -11),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, tikigoomba_foot_L_mesh_layer_1),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -11, -1, 1, 0, 0, 1),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
						GEO_OPEN_NODE(),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 14, 0, -81, 6, 5),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, tikigoomba_foot_R_mesh_layer_1),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, tikigoomba_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, tikigoomba_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

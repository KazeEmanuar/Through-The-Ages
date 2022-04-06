#include "src/game/envfx_snow.h"

const GeoLayout colorpipe_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
			GEO_ASM(0, geo_set_prim),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, colorpipe_skinned_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, colorpipe_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

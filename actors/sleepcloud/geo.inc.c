#include "src/game/envfx_snow.h"

const GeoLayout sleepcloud_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0, set_prim_to_opacity),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sleepcloud_JOBJ_3_DOBJ_0_SINGLE_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, sleepcloud_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

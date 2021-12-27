#include "src/game/envfx_snow.h"

const GeoLayout huffnpuffbaby_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, huffnpuffbaby_littleBody_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, huffnpuffbaby_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

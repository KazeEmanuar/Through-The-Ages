#include "src/game/envfx_snow.h"

const GeoLayout stalkbig_geo[] = {
	GEO_CULLING_RADIUS(4000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, stalkbig_beanstalk_001_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, stalkbig_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

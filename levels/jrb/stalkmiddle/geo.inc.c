#include "src/game/envfx_snow.h"

const GeoLayout stalkmiddle_geo[] = {
	GEO_CULLING_RADIUS(2000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, stalkmiddle_beanstalk_001_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, stalkmiddle_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

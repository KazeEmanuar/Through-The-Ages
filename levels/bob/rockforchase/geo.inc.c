#include "src/game/envfx_snow.h"

const GeoLayout rockforchase_geo[] = {
   GEO_CULLING_RADIUS(1500),
   GEO_OPEN_NODE(),
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rockforchase_Icosphere_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, rockforchase_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

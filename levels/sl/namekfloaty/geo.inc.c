#include "src/game/envfx_snow.h"

const GeoLayout namekfloaty_geo[] = {
	GEO_CULLING_RADIUS(1500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(1, namekfloaty_Sphere_001_mesh_layer_1),
		GEO_DISPLAY_LIST(6, namekfloaty_Sphere_001_mesh_layer_6),
		GEO_DISPLAY_LIST(6, namekfloaty_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, namekfloaty_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

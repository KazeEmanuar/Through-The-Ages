#include "src/game/envfx_snow.h"

const GeoLayout raft_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE_WITH_DL(1, 0, 0, 0, 0, 0, 0, raft_Cube_mesh),
		GEO_DISPLAY_LIST(0, raft_material_revert_render_settings),
		GEO_DISPLAY_LIST(1, raft_material_revert_render_settings),
		GEO_DISPLAY_LIST(2, raft_material_revert_render_settings),
		GEO_DISPLAY_LIST(3, raft_material_revert_render_settings),
		GEO_DISPLAY_LIST(4, raft_material_revert_render_settings),
		GEO_DISPLAY_LIST(5, raft_material_revert_render_settings),
		GEO_DISPLAY_LIST(6, raft_material_revert_render_settings),
		GEO_DISPLAY_LIST(7, raft_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

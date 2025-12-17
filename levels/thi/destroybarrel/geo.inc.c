#include "src/game/envfx_snow.h"

const GeoLayout destroybarrel_Armature_001[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, destroybarrel_325_23_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout destroybarrel_Armature_002[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, destroybarrel_fdeshsdfh_fdgsdag_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout destroybarrel_Armature_003[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, destroybarrel_fgdfg_ddgdasg_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout destroybarrel_Armature_004[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, destroybarrel_dsga_dggg_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout destroybarrel_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(5, geo_switch_anim_state),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, destroybarrel_Bone_001_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, destroybarrel_Armature_001),
			GEO_BRANCH(1, destroybarrel_Armature_002),
			GEO_BRANCH(1, destroybarrel_Armature_003),
			GEO_BRANCH(1, destroybarrel_Armature_004),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};

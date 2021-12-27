void scroll_lightningball_Bone_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 8;
	int width = 64 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(lightningball_Bone_mesh_layer_5_vtx_0);

	deltaX = (int)(10.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;

}
void scroll_lightningball_Bone_001_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 8;
	int width = 64 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(lightningball_Bone_001_mesh_layer_5_vtx_0);

	deltaX = (int)(10.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;

}
void scroll_lightningball_Bone_002_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 8;
	int width = 64 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(lightningball_Bone_002_mesh_layer_5_vtx_0);

	deltaX = (int)(10.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;

}
void scroll_lightningball_Bone_003_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 8;
	int width = 64 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(lightningball_Bone_003_mesh_layer_5_vtx_0);

	deltaX = (int)(10.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;

}
void scroll_ddd_level_geo_lightningball() {
	scroll_lightningball_Bone_mesh_layer_5_vtx_0();
	scroll_lightningball_Bone_001_mesh_layer_5_vtx_0();
	scroll_lightningball_Bone_002_mesh_layer_5_vtx_0();
	scroll_lightningball_Bone_003_mesh_layer_5_vtx_0();
}

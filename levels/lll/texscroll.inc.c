void scroll_lll_dl_Cube_002_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 96;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(lll_dl_Cube_002_mesh_layer_5_vtx_0);

	deltaX = (int)(3.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;

}
void scroll_lll_dl_Cube_002_mesh_layer_5_vtx_1() {
	int i = 0;
	int count = 120;
	int width = 128 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(lll_dl_Cube_002_mesh_layer_5_vtx_1);

	deltaX = (int)(6.0 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;

}
void scroll_lll() {
	scroll_lll_dl_Cube_002_mesh_layer_5_vtx_0();
	scroll_lll_dl_Cube_002_mesh_layer_5_vtx_1();
}

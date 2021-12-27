void scroll_ddd_dl_Plane_004_mesh_layer_6_vtx_0() {
	int i = 0;
	int count = 88;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(ddd_dl_Plane_004_mesh_layer_6_vtx_0);

	deltaY = (int)(-4.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_ddd_dl_Clouds_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 1627;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(ddd_dl_Clouds_mesh_layer_1_vtx_0);

	deltaX = (int)(-0.25 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_ddd() {
	scroll_ddd_dl_Plane_004_mesh_layer_6_vtx_0();
	scroll_ddd_dl_Clouds_mesh_layer_1_vtx_0();
}

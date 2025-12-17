void scroll_thi_dl_Room2_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 60;
	int width = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(thi_dl_Room2_mesh_layer_5_vtx_0);

	deltaX = (int)(0.009999999776482582 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_thi_dl_Room5_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 30;
	int width = 128 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(thi_dl_Room5_mesh_layer_5_vtx_0);

	deltaX = (int)(0.009999999776482582 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_thi() {
	scroll_thi_dl_Room2_mesh_layer_5_vtx_0();
	scroll_thi_dl_Room5_mesh_layer_5_vtx_0();
};

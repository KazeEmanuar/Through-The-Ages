void scroll_wdw_dl_Circle_003_mesh_layer_1_vtx_3() {
	int i = 0;
	int count = 9;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(wdw_dl_Circle_003_mesh_layer_1_vtx_3);

	deltaX = (int)(0.25 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_wdw_dl_Icosphere_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 453;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	static int timeY;
	float amplitudeY = 1.0;
	float frequencyY = 0.10000000149011612;
	float offsetY = 0.0;
	Vtx *vertices = segmented_to_virtual(wdw_dl_Icosphere_mesh_layer_1_vtx_0);

	deltaX = (int)(0.019999999552965164 * 0x20) % width;
	deltaY = (int)(amplitudeY * frequencyY * coss((frequencyY * timeY + offsetY) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;	timeY += 1;
}

void scroll_sts_mat_wdw_dl_f3d_material_030_layer1() {
	Gfx *mat = segmented_to_virtual(mat_wdw_dl_f3d_material_030_layer1);
	shift_s(mat, 21, PACK_TILESIZE(0, 1));
};

void scroll_wdw() {
	scroll_wdw_dl_Circle_003_mesh_layer_1_vtx_3();
	scroll_wdw_dl_Icosphere_mesh_layer_1_vtx_0();
	scroll_sts_mat_wdw_dl_f3d_material_030_layer1();
}

void scroll_hmc_dl_Circle_009_mesh_layer_1_vtx_1() {
	int i = 0;
	int count = 1550;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	static int timeY;
	float amplitudeY = 1.0;
	float frequencyY = 0.05000000074505806;
	float offsetY = 0.0;
	Vtx *vertices = segmented_to_virtual(hmc_dl_Circle_009_mesh_layer_1_vtx_1);

	deltaX = (int)(0.5 * 0x20) % width;
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

void scroll_sts_mat_hmc_dl_f3d_material_014_layer1() {
	Gfx *mat = segmented_to_virtual(mat_hmc_dl_f3d_material_014_layer1);
	shift_s(mat, 20, PACK_TILESIZE(0, 1));
	shift_t(mat, 20, PACK_TILESIZE(0, 1));
	shift_s_down(mat, 35, PACK_TILESIZE(0, 1));
};

void scroll_hmc() {
	scroll_hmc_dl_Circle_009_mesh_layer_1_vtx_1();
	scroll_sts_mat_hmc_dl_f3d_material_014_layer1();
}

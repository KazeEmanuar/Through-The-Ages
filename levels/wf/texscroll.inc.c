void scroll_wf_dl_Plane_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 16;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(wf_dl_Plane_mesh_layer_1_vtx_0);

	deltaX = (int)(0.05000000074505806 * 0x20) % width;
	deltaY = (int)(0.05000000074505806 * 0x20) % height;

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
	currentX += deltaX;	currentY += deltaY;
}

void scroll_sts_mat_wf_dl_f3d_material_016_layer1() {
	Gfx *mat = segmented_to_virtual(mat_wf_dl_f3d_material_016_layer1);
	shift_s(mat, 13, PACK_TILESIZE(0, 1));
};

void scroll_wf() {
	scroll_wf_dl_Plane_mesh_layer_1_vtx_0();
	scroll_sts_mat_wf_dl_f3d_material_016_layer1();
}

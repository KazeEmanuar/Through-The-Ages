void scroll_sts_mat_bob_dl_f3d_material_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bob_dl_f3d_material_layer1);
	shift_s_down(mat, 20, PACK_TILESIZE(0, 1));
	shift_s(mat, 35, PACK_TILESIZE(0, 1));
	shift_t(mat, 35, PACK_TILESIZE(0, 1));
};

void scroll_bob_dl_ZPlane_002_mesh_vtx_0() {
	int i = 0;
	int count = 25;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bob_dl_ZPlane_002_mesh_vtx_0);

	deltaY = (int)(-1.5 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bob_dl_ZPlane_004_mesh_vtx_0() {
	int i = 0;
	int count = 8;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bob_dl_ZPlane_004_mesh_vtx_0);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bob_dl_ZZPlane_003_mesh_vtx_0() {
	int i = 0;
	int count = 10;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bob_dl_ZZPlane_003_mesh_vtx_0);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_bob() {
	scroll_sts_mat_bob_dl_f3d_material_layer1();
	scroll_bob_dl_ZPlane_002_mesh_vtx_0();
	scroll_bob_dl_ZPlane_004_mesh_vtx_0();
	scroll_bob_dl_ZZPlane_003_mesh_vtx_0();
}

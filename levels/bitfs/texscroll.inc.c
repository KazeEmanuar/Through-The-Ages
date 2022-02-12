void scroll_sts_mat_bitfs_dl_f3d_material_007() {
	Gfx *mat = segmented_to_virtual(mat_bitfs_dl_f3d_material_007);
	shift_s(mat, 11, PACK_TILESIZE(0, 1));
};

void scroll_bitfs_dl_Plane_005_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 61;
	int width = 128 * 0x20;
	int height = 64 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(bitfs_dl_Plane_005_mesh_layer_5_vtx_0);

	deltaY = (int)(-0.029999999329447746 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;
}

void scroll_sts_mat_bitfs_dl_f3d_material_001_layer5() {
	Gfx *mat = segmented_to_virtual(mat_bitfs_dl_f3d_material_001_layer5);
	shift_s_down(mat, 13, PACK_TILESIZE(0, 1));
	shift_s(mat, 21, PACK_TILESIZE(0, 1));
	shift_t(mat, 21, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_bitfs_dl_f3d_material_002_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bitfs_dl_f3d_material_002_layer1);
	shift_s(mat, 12, PACK_TILESIZE(0, 1));
	shift_t(mat, 12, PACK_TILESIZE(0, 1));
	shift_s_down(mat, 20, PACK_TILESIZE(0, 1));
	shift_t(mat, 20, PACK_TILESIZE(0, 1));
};

void scroll_bitfs() {
	scroll_sts_mat_bitfs_dl_f3d_material_007();
	scroll_bitfs_dl_Plane_005_mesh_layer_5_vtx_0();
	scroll_sts_mat_bitfs_dl_f3d_material_001_layer5();
	scroll_sts_mat_bitfs_dl_f3d_material_002_layer1();
}

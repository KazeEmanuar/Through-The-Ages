void scroll_sts_mat_sl_dl_f3d_material_010_layer1() {
	Gfx *mat = segmented_to_virtual(mat_sl_dl_f3d_material_010_layer1);
	shift_s(mat, 13, PACK_TILESIZE(0, 1));
	shift_s_down(mat, 21, PACK_TILESIZE(0, 1));
	shift_t_down(mat, 21, PACK_TILESIZE(0, 1));
};

void scroll_sl() {
	scroll_sts_mat_sl_dl_f3d_material_010_layer1();
}

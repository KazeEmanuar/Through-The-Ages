void scroll_gfx_mat_blueflame_f3d_material_041_layer5() {
	Gfx *mat = SegmentedToVirtual(mat_blueflame_f3d_material_041_layer5);


	shift_s(mat, 11, PACK_TILESIZE(0, 5));
	shift_t_down(mat, 11, PACK_TILESIZE(0, 19));
	shift_s_down(mat, 13, PACK_TILESIZE(0, 2));
	shift_t_down(mat, 13, PACK_TILESIZE(0, 10));

};

void scroll_bbh_level_geo_blueflame() {
	scroll_gfx_mat_blueflame_f3d_material_041_layer5();
};

const Collision goldseesaw_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(8),
	COL_VERTEX(48, 0, 623),
	COL_VERTEX(48, 105, 623),
	COL_VERTEX(-50, 104, 623),
	COL_VERTEX(-48, 104, -620),
	COL_VERTEX(-48, 0, -620),
	COL_VERTEX(-49, 0, 623),
	COL_VERTEX(50, 0, -620),
	COL_VERTEX(49, 105, -620),
	COL_TRI_INIT(SURFACE_DEFAULT, 12),
	COL_TRI(0, 1, 2),
	COL_TRI(2, 3, 4),
	COL_TRI(5, 0, 2),
	COL_TRI(2, 4, 5),
	COL_TRI(5, 4, 6),
	COL_TRI(5, 6, 0),
	COL_TRI(6, 4, 3),
	COL_TRI(7, 1, 0),
	COL_TRI(6, 3, 7),
	COL_TRI(7, 0, 6),
	COL_TRI(7, 3, 2),
	COL_TRI(7, 2, 1),
	COL_TRI_STOP(),
	COL_END()
};
const Collision treasuredoor_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(12),
	COL_VERTEX(-200, 346, 86),
	COL_VERTEX(200, 346, 86),
	COL_VERTEX(235, 408, -56),
	COL_VERTEX(-235, 408, -56),
	COL_VERTEX(-399, 0, 86),
	COL_VERTEX(-471, 0, -56),
	COL_VERTEX(-200, -346, 86),
	COL_VERTEX(-235, -408, -56),
	COL_VERTEX(200, -346, 86),
	COL_VERTEX(235, -408, -56),
	COL_VERTEX(399, 0, 86),
	COL_VERTEX(471, 0, -56),
	COL_TRI_INIT(SURFACE_DEFAULT, 16),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI(4, 0, 3),
	COL_TRI(4, 3, 5),
	COL_TRI(6, 4, 5),
	COL_TRI(6, 5, 7),
	COL_TRI(8, 6, 7),
	COL_TRI(8, 7, 9),
	COL_TRI(10, 8, 9),
	COL_TRI(10, 9, 11),
	COL_TRI(1, 10, 11),
	COL_TRI(1, 11, 2),
	COL_TRI(1, 0, 4),
	COL_TRI(4, 6, 8),
	COL_TRI(8, 10, 1),
	COL_TRI(4, 8, 1),
	COL_TRI_STOP(),
	COL_END()
};
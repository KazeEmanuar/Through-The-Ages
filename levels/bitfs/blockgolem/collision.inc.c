const Collision blockgolem_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(8),
	COL_VERTEX(-250, -250, 250),
	COL_VERTEX(-250, -250, -250),
	COL_VERTEX(250, -250, -250),
	COL_VERTEX(250, -250, 250),
	COL_VERTEX(-250, 250, 250),
	COL_VERTEX(250, 250, 250),
	COL_VERTEX(250, 250, -250),
	COL_VERTEX(-250, 250, -250),
	COL_TRI_INIT(SURFACE_DEFAULT, 12),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI(4, 5, 6),
	COL_TRI(4, 6, 7),
	COL_TRI(2, 1, 7),
	COL_TRI(2, 7, 6),
	COL_TRI(0, 3, 5),
	COL_TRI(0, 5, 4),
	COL_TRI(3, 2, 6),
	COL_TRI(3, 6, 5),
	COL_TRI(1, 0, 4),
	COL_TRI(1, 4, 7),
	COL_TRI_STOP(),
	COL_END()
};
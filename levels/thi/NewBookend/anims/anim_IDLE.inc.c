// 4
static const s16 anim_beIDLE_values[] = {
	0x0000, 0x4000, 0xb1c7, 0x4e39, 
};

// 18
static const u16 anim_beIDLE_indices[] = {
	0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0000, 
	0x0001, 0x0001, 0x0001, 0x0003, 0x0001, 0x0000, 
	
};

static const struct Animation NewBookend_anim_IDLE = {
	0x0000, // flags ANIM_FLAG_NOLOOP
	0, // animYTransDivisor
	0, // startFrame
	1, // loopStart
	2, // loopEnd
	ANIMINDEX_NUMPARTS(anim_beIDLE_indices), // unusedBoneCount
	anim_beIDLE_values, // values
	anim_beIDLE_indices, // index
	0 // length
};


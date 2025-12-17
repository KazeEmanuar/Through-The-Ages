// 5
static const s16 anim_STARTPEEK_002_values[] = {
	0x0000, 0xf54e, 0xd3d2, 0x0480, 0x2023, 
};

// 30
static const u16 anim_STARTPEEK_002_indices[] = {
	0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0000, 
	0x0001, 0x0002, 0x0001, 0x0000, 0x0001, 0x0000, 
	0x0001, 0x0003, 0x0001, 0x0000, 0x0001, 0x0000, 
	0x0001, 0x0004, 0x0001, 0x0000, 0x0001, 0x0000, 
	
};

static const struct Animation booguybarrell_anim_STARTPEEK_002 = {
	0x0001, // flags ANIM_FLAG_NOLOOP
	0, // animYTransDivisor
	0, // startFrame
	1, // loopStart
	12, // loopEnd
	ANIMINDEX_NUMPARTS(anim_STARTPEEK_002_indices), // unusedBoneCount
	anim_STARTPEEK_002_values, // values
	anim_STARTPEEK_002_indices, // index
	0 // length
};


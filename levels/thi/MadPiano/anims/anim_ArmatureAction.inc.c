// 2
static const s16 anim_aaa_values[] = {
	0x0000, 0xc000, 
};

// 18
static const u16 anim_aaa_indices[] = {
	0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 
	0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0001, 
	
};

static const struct Animation MadPiano_anim_ArmatureAction = {
	0x0000, // flags ANIM_FLAG_NOLOOP
	0, // animYTransDivisor
	0, // startFrame
	1, // loopStart
	2, // loopEnd
	ANIMINDEX_NUMPARTS(anim_aaa_indices), // unusedBoneCount
	anim_aaa_values, // values
	anim_aaa_indices, // index
	0 // length
};


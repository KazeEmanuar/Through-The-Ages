Lights1 tikispear_cableWood_v4_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 tikispear_ropes_v4_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 tikispear_blackRock_v4_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx tikispear_red_ci8_aligner[] = {gsSPEndDisplayList()};
u8 tikispear_red_ci8[] = {
	0x00, 0x01, 0x02, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x01, 
	0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x02, 0x01, 
	0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x01, 
	0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 
	0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 
	0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 
	0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 
	0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x04, 
	0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 
	0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x04, 0x03, 
	0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
	0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 
	0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 
	0x00, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
	0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
	0x03, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
	0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
	0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 
	0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
	0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x01, 0x01, 
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x00, 0x03, 0x00, 0x01, 0x01, 0x01, 
	0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 
	0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x00, 0x03, 0x00, 0x01, 0x01, 0x01, 0x00, 
	0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
	0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x00, 0x03, 0x03, 0x00, 0x01, 0x01, 0x01, 0x00, 
	0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 
	0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 
	0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 
	0x04, 0x04, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 
	0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 
	0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x04, 
	0x04, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
	0x00, 0x03, 0x00, 0x01, 0x01, 0x00, 0x05, 0x04, 
	0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x00, 0x03, 0x04, 0x00, 0x04, 0x05, 0x03, 0x00, 
	0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 
	0x00, 0x00, 0x03, 0x04, 0x04, 0x03, 0x00, 0x00, 
	0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 
	0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x04, 
	0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0x00, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x04, 
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 
	0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x04, 0x04, 
	0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x00, 0x03, 0x03, 0x00, 0x01, 
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x04, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x04, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
	0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x01, 
	0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x04, 0x03, 
	0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 
	0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x00, 0x00, 0x04, 0x04, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x00, 
	
};

Gfx tikispear_red_ci8_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 tikispear_red_ci8_pal_rgba16[] = {
	0xd0, 0xc7, 0xd1, 0x07, 0xd1, 0x47, 0xd0, 0x87, 
	0xc8, 0x87, 0xc8, 0x47, 
};

Gfx tikispear_headDetails_ci4_aligner[] = {gsSPEndDisplayList()};
u8 tikispear_headDetails_ci4[] = {
	0x01, 0x23, 0x12, 0x45, 0x66, 0x66, 0x66, 0x66, 
	0x66, 0x67, 0x38, 0x24, 0x9a, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x64, 0x28, 0x37, 0x7b, 0x66, 
	0x66, 0x66, 0x66, 0x66, 0x54, 0x21, 0x32, 0x10, 
	0x6c, 0x2b, 0xb2, 0xbd, 0x66, 0x66, 0x66, 0x66, 
	0x66, 0x67, 0x31, 0x2c, 0x9d, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x6c, 0x21, 0x37, 0x7b, 0x66, 
	0x66, 0x66, 0x66, 0x66, 0xdb, 0x2b, 0xb2, 0x36, 
	0x63, 0x8b, 0xb8, 0x21, 0x56, 0x66, 0x66, 0x66, 
	0x66, 0x67, 0x31, 0x2c, 0x95, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x61, 0x21, 0x37, 0x76, 0x66, 
	0x66, 0x66, 0x66, 0x65, 0xc2, 0x8b, 0xb1, 0x36, 
	0x66, 0x32, 0xb1, 0xb2, 0x06, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x31, 0x21, 0x94, 0xa6, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x61, 0x21, 0x37, 0x76, 0x66, 
	0x66, 0x66, 0x66, 0x60, 0x22, 0x11, 0x23, 0x66, 
	0x66, 0x31, 0x73, 0x12, 0xc5, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x0c, 0xbc, 0x99, 0xa6, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x9c, 0xbc, 0x08, 0x86, 0x66, 
	0x66, 0x66, 0x66, 0x5c, 0x21, 0x32, 0x13, 0x66, 
	0x66, 0x6c, 0xb3, 0xcb, 0xb5, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x00, 0xbc, 0x99, 0xa6, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x91, 0xb0, 0x0e, 0x16, 0x66, 
	0x66, 0x66, 0x66, 0x5b, 0xbc, 0x3b, 0xc6, 0x66, 
	0x66, 0x6d, 0xcb, 0xdc, 0xbd, 0x56, 0x66, 0x66, 
	0x66, 0x66, 0xf0, 0xcc, 0x49, 0xa6, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x4c, 0xc0, 0xff, 0x66, 0x66, 
	0x66, 0x66, 0x6d, 0xdb, 0xcd, 0xbc, 0xd6, 0x66, 
	0x66, 0x66, 0x0c, 0x00, 0xcc, 0xd5, 0x0f, 0x33, 
	0x3f, 0xf5, 0x53, 0x03, 0x49, 0xdd, 0xd3, 0xe3, 
	0x33, 0x1f, 0x59, 0x43, 0x03, 0x1a, 0x55, 0x54, 
	0xdc, 0xcc, 0x5d, 0x3c, 0x00, 0xc0, 0x66, 0x66, 
	0x66, 0x66, 0x60, 0x33, 0x03, 0x05, 0x5d, 0xee, 
	0x0a, 0x05, 0x9f, 0x33, 0xd9, 0x5a, 0xda, 0xee, 
	0xff, 0xfa, 0xd5, 0x53, 0xff, 0x70, 0x55, 0xa3, 
	0xfe, 0x30, 0x5d, 0x30, 0x33, 0x06, 0x66, 0x66, 
	0x66, 0x66, 0x6f, 0x3f, 0x13, 0xfd, 0x55, 0xaa, 
	0xdd, 0xd5, 0x9a, 0x3e, 0xd4, 0x5a, 0x5a, 0xe8, 
	0xee, 0xfa, 0x59, 0x0e, 0x33, 0x25, 0x55, 0xaa, 
	0xef, 0xa5, 0x0f, 0x31, 0xf3, 0xf6, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x3e, 0xb1, 0xef, 0x56, 0x66, 
	0x66, 0x66, 0x6e, 0x08, 0x04, 0x5f, 0x66, 0x66, 
	0x66, 0x66, 0x65, 0x08, 0x0e, 0x26, 0x66, 0x66, 
	0x66, 0x65, 0x3e, 0x1b, 0xe3, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x3c, 0xeb, 0xc8, 0xd5, 0x66, 
	0x66, 0x66, 0x66, 0xc8, 0xa4, 0xda, 0x66, 0x66, 
	0x66, 0x66, 0x64, 0xa8, 0xcb, 0x26, 0x66, 0x66, 
	0x66, 0x5d, 0x8c, 0xbe, 0xc3, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x6c, 0xe1, 0xbe, 0x1d, 0x66, 
	0x66, 0x66, 0x66, 0xd1, 0xc4, 0x4d, 0x66, 0x66, 
	0x66, 0x66, 0x64, 0xc1, 0xdb, 0x26, 0x66, 0x66, 
	0x66, 0xde, 0xeb, 0x1e, 0xc6, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x6d, 0xc8, 0xb1, 0x7c, 0x56, 
	0x66, 0x66, 0x66, 0x41, 0x84, 0x4a, 0xe6, 0x66, 
	0x66, 0x66, 0x64, 0x81, 0x4b, 0x26, 0x66, 0x66, 
	0x65, 0xc7, 0x1b, 0x80, 0xd6, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x66, 0xd8, 0xdb, 0x88, 0xd6, 
	0x66, 0x66, 0x66, 0x6e, 0x8d, 0x9d, 0x36, 0x66, 
	0x66, 0x66, 0x9d, 0x8e, 0x52, 0x66, 0x66, 0x66, 
	0x6d, 0x88, 0xb0, 0xed, 0x66, 0x66, 0x66, 0x66, 
	0x66, 0x66, 0x66, 0x66, 0xd0, 0x8c, 0x17, 0x35, 
	0x66, 0x66, 0x66, 0x63, 0x7d, 0x9d, 0xa6, 0x66, 
	0x66, 0x66, 0x9d, 0x73, 0xd2, 0x66, 0x66, 0x66, 
	0x53, 0x71, 0xc8, 0x0d, 0x66, 0x66, 0x66, 0x66, 
	
};

Gfx tikispear_headDetails_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 tikispear_headDetails_ci4_pal_rgba16[] = {
	0x59, 0x41, 0x69, 0x81, 0x8a, 0x03, 0x61, 0x83, 
	0x40, 0xc1, 0x41, 0x01, 0xff, 0xfe, 0x7a, 0x03, 
	0x69, 0xc1, 0x30, 0x41, 0x51, 0x81, 0x79, 0x81, 
	0x61, 0x41, 0x51, 0x01, 0x61, 0x81, 0x59, 0x81, 
	
};

Gfx tikispear_ropes_ci8_aligner[] = {gsSPEndDisplayList()};
u8 tikispear_ropes_ci8[] = {
	0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 
	0x05, 0x06, 0x07, 0x03, 0x00, 0x00, 0x01, 0x02, 
	0x08, 0x00, 0x01, 0x00, 0x09, 0x0a, 0x00, 0x02, 
	0x04, 0x00, 0x0b, 0x01, 0x08, 0x00, 0x01, 0x00, 
	0x0c, 0x07, 0x04, 0x00, 0x0d, 0x0b, 0x00, 0x0e, 
	0x04, 0x00, 0x0f, 0x0a, 0x0c, 0x07, 0x04, 0x00, 
	0x0e, 0x04, 0x05, 0x00, 0x0d, 0x04, 0x00, 0x0e, 
	0x04, 0x00, 0x0f, 0x03, 0x0e, 0x04, 0x05, 0x00, 
	0x00, 0x10, 0x0b, 0x00, 0x0d, 0x03, 0x00, 0x0e, 
	0x04, 0x00, 0x0f, 0x03, 0x00, 0x10, 0x0b, 0x00, 
	0x00, 0x00, 0x05, 0x00, 0x0d, 0x04, 0x07, 0x0e, 
	0x04, 0x00, 0x0f, 0x03, 0x00, 0x00, 0x05, 0x00, 
	0x00, 0x02, 0x04, 0x00, 0x0d, 0x04, 0x11, 0x0d, 
	0x04, 0x00, 0x0f, 0x03, 0x00, 0x02, 0x04, 0x00, 
	0x00, 0x0e, 0x04, 0x00, 0x0d, 0x04, 0x02, 0x03, 
	0x04, 0x00, 0x0f, 0x04, 0x00, 0x0e, 0x04, 0x00, 
	0x00, 0x0e, 0x04, 0x12, 0x0d, 0x04, 0x00, 0x09, 
	0x0a, 0x00, 0x0f, 0x03, 0x00, 0x0e, 0x04, 0x12, 
	0x00, 0x0e, 0x04, 0x06, 0x07, 0x03, 0x00, 0x0d, 
	0x0b, 0x00, 0x0f, 0x08, 0x00, 0x0e, 0x04, 0x06, 
	0x07, 0x0e, 0x04, 0x00, 0x0b, 0x01, 0x00, 0x0d, 
	0x04, 0x00, 0x0f, 0x08, 0x07, 0x0e, 0x04, 0x00, 
	0x11, 0x0d, 0x04, 0x00, 0x0f, 0x0a, 0x00, 0x0d, 
	0x03, 0x08, 0x00, 0x01, 0x11, 0x0d, 0x04, 0x00, 
	0x02, 0x03, 0x04, 0x00, 0x0f, 0x03, 0x00, 0x0d, 
	0x04, 0x0c, 0x07, 0x04, 0x02, 0x03, 0x04, 0x00, 
	0x00, 0x09, 0x0a, 0x00, 0x0f, 0x03, 0x00, 0x0d, 
	0x04, 0x0e, 0x04, 0x05, 0x00, 0x09, 0x0a, 0x00, 
	0x00, 0x0d, 0x0b, 0x00, 0x0f, 0x03, 0x00, 0x0d, 
	0x04, 0x00, 0x10, 0x0b, 0x00, 0x0d, 0x0b, 0x00, 
	0x00, 0x0d, 0x04, 0x00, 0x0f, 0x03, 0x12, 0x0d, 
	0x04, 0x00, 0x00, 0x05, 0x00, 0x0d, 0x04, 0x00, 
	0x00, 0x0d, 0x03, 0x00, 0x00, 0x01, 0x06, 0x07, 
	0x03, 0x00, 0x02, 0x04, 0x00, 0x0d, 0x03, 0x00, 
	0x00, 0x0d, 0x04, 0x08, 0x00, 0x01, 0x00, 0x0b, 
	0x01, 0x00, 0x0e, 0x04, 0x00, 0x0d, 0x04, 0x08, 
	0x00, 0x0d, 0x04, 0x0c, 0x07, 0x04, 0x00, 0x0f, 
	0x0a, 0x00, 0x0e, 0x04, 0x00, 0x0d, 0x04, 0x0c, 
	0x00, 0x0d, 0x04, 0x0e, 0x04, 0x05, 0x00, 0x0f, 
	0x03, 0x00, 0x0e, 0x04, 0x00, 0x0d, 0x04, 0x0e, 
	0x12, 0x0d, 0x04, 0x00, 0x10, 0x0b, 0x00, 0x00, 
	0x01, 0x07, 0x0e, 0x04, 0x12, 0x0d, 0x04, 0x00, 
	0x06, 0x07, 0x03, 0x00, 0x00, 0x05, 0x08, 0x00, 
	0x01, 0x11, 0x0d, 0x04, 0x06, 0x07, 0x03, 0x00, 
	0x00, 0x0b, 0x01, 0x00, 0x02, 0x04, 0x0c, 0x07, 
	0x04, 0x02, 0x03, 0x04, 0x00, 0x0b, 0x01, 0x00, 
	0x00, 0x0f, 0x0a, 0x00, 0x0e, 0x04, 0x0e, 0x04, 
	0x05, 0x00, 0x09, 0x0a, 0x00, 0x0f, 0x0a, 0x00, 
	0x00, 0x0f, 0x03, 0x00, 0x0e, 0x04, 0x00, 0x10, 
	0x0b, 0x00, 0x0d, 0x0b, 0x00, 0x0f, 0x03, 0x00, 
	0x00, 0x0f, 0x03, 0x00, 0x0e, 0x04, 0x00, 0x00, 
	0x05, 0x00, 0x0d, 0x04, 0x00, 0x0f, 0x03, 0x00, 
	0x00, 0x0f, 0x03, 0x07, 0x0e, 0x04, 0x00, 0x02, 
	0x04, 0x00, 0x0d, 0x03, 0x00, 0x0f, 0x03, 0x07, 
	0x00, 0x0f, 0x03, 0x11, 0x0d, 0x04, 0x00, 0x0e, 
	0x04, 0x00, 0x0d, 0x04, 0x00, 0x0f, 0x03, 0x11, 
	0x00, 0x0f, 0x04, 0x02, 0x03, 0x04, 0x00, 0x0e, 
	0x04, 0x00, 0x0d, 0x04, 0x00, 0x0f, 0x04, 0x02, 
	0x00, 0x0f, 0x03, 0x00, 0x09, 0x0a, 0x00, 0x0e, 
	0x04, 0x00, 0x0d, 0x04, 0x00, 0x0f, 0x03, 0x00, 
	0x00, 0x0f, 0x08, 0x00, 0x0d, 0x0b, 0x07, 0x0e, 
	0x04, 0x12, 0x0d, 0x04, 0x00, 0x0f, 0x08, 0x00, 
	0x00, 0x0f, 0x08, 0x00, 0x0d, 0x04, 0x11, 0x0d, 
	0x04, 0x06, 0x07, 0x03, 0x00, 0x0f, 0x08, 0x00, 
	
};

Gfx tikispear_ropes_ci8_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 tikispear_ropes_ci8_pal_rgba16[] = {
	0xb4, 0x49, 0x62, 0x03, 0xb4, 0x09, 0x6a, 0x43, 
	0x6a, 0x03, 0x61, 0xc3, 0x51, 0x81, 0x9b, 0x87, 
	0x72, 0x43, 0x82, 0xc5, 0x49, 0x41, 0x59, 0xc3, 
	0x72, 0x45, 0xac, 0x07, 0xb4, 0x07, 0xab, 0xc7, 
	0xa3, 0xc7, 0x59, 0x83, 0x8b, 0x05, 
};

Gfx tikispear_blackRock_i8_aligner[] = {gsSPEndDisplayList()};
u8 tikispear_blackRock_i8[] = {
	0x14, 0x13, 0x13, 0x13, 0x13, 0x11, 0x12, 0x11, 
	0x08, 0x1b, 0x1a, 0x1a, 0x14, 0x15, 0x0f, 0x14, 
	0x0e, 0x13, 0x1e, 0x1e, 0x1c, 0x15, 0x10, 0x13, 
	0x15, 0x0d, 0x11, 0x18, 0x1e, 0x1c, 0x11, 0x13, 
	0x14, 0x14, 0x15, 0x12, 0x12, 0x12, 0x12, 0x0c, 
	0x0b, 0x1a, 0x15, 0x16, 0x14, 0x15, 0x10, 0x14, 
	0x14, 0x1b, 0x1b, 0x15, 0x0a, 0x10, 0x10, 0x0e, 
	0x18, 0x11, 0x1a, 0x11, 0x0a, 0x1b, 0x10, 0x12, 
	0x13, 0x14, 0x17, 0x0e, 0x12, 0x11, 0x0e, 0x0d, 
	0x1b, 0x16, 0x13, 0x11, 0x13, 0x13, 0x16, 0x13, 
	0x1b, 0x17, 0x1a, 0x14, 0x05, 0x1a, 0x0e, 0x14, 
	0x15, 0x17, 0x1a, 0x12, 0x0d, 0x0e, 0x11, 0x12, 
	0x14, 0x11, 0x0a, 0x11, 0x13, 0x0e, 0x0e, 0x19, 
	0x14, 0x15, 0x0f, 0x12, 0x13, 0x13, 0x14, 0x12, 
	0x12, 0x12, 0x17, 0x1a, 0x17, 0x14, 0x13, 0x15, 
	0x11, 0x13, 0x13, 0x12, 0x12, 0x0e, 0x10, 0x13, 
	0x15, 0x0b, 0x15, 0x16, 0x0f, 0x0e, 0x1a, 0x14, 
	0x15, 0x12, 0x11, 0x0d, 0x12, 0x11, 0x13, 0x14, 
	0x15, 0x19, 0x17, 0x18, 0x14, 0x0c, 0x13, 0x11, 
	0x15, 0x14, 0x14, 0x15, 0x15, 0x10, 0x10, 0x12, 
	0x0c, 0x11, 0x16, 0x11, 0x0b, 0x15, 0x12, 0x16, 
	0x17, 0x15, 0x13, 0x0c, 0x0b, 0x14, 0x12, 0x12, 
	0x17, 0x18, 0x18, 0x18, 0x18, 0x19, 0x19, 0x11, 
	0x14, 0x15, 0x15, 0x17, 0x12, 0x14, 0x14, 0x13, 
	0x0f, 0x0e, 0x0f, 0x0f, 0x0e, 0x16, 0x16, 0x1a, 
	0x1a, 0x18, 0x15, 0x0f, 0x10, 0x0c, 0x13, 0x12, 
	0x18, 0x15, 0x18, 0x19, 0x0c, 0x13, 0x0c, 0x11, 
	0x15, 0x15, 0x16, 0x19, 0x11, 0x12, 0x14, 0x0d, 
	0x14, 0x0b, 0x10, 0x12, 0x15, 0x1c, 0x1a, 0x1b, 
	0x19, 0x19, 0x19, 0x13, 0x11, 0x06, 0x10, 0x12, 
	0x1c, 0x19, 0x0f, 0x09, 0x0d, 0x0f, 0x10, 0x0f, 
	0x17, 0x15, 0x17, 0x15, 0x12, 0x13, 0x0e, 0x0e, 
	0x10, 0x13, 0x19, 0x16, 0x17, 0x18, 0x1b, 0x1a, 
	0x18, 0x19, 0x18, 0x17, 0x0f, 0x1a, 0x06, 0x0b, 
	0x07, 0x0b, 0x15, 0x12, 0x10, 0x1c, 0x18, 0x10, 
	0x15, 0x1a, 0x15, 0x17, 0x16, 0x13, 0x15, 0x12, 
	0x0c, 0x16, 0x1a, 0x18, 0x19, 0x1a, 0x19, 0x19, 
	0x17, 0x17, 0x17, 0x15, 0x0a, 0x13, 0x14, 0x13, 
	0x09, 0x0b, 0x18, 0x17, 0x15, 0x13, 0x12, 0x0b, 
	0x0b, 0x1b, 0x15, 0x15, 0x14, 0x11, 0x0e, 0x0d, 
	0x15, 0x1b, 0x1a, 0x19, 0x19, 0x19, 0x1a, 0x16, 
	0x16, 0x16, 0x16, 0x0d, 0x08, 0x11, 0x12, 0x14, 
	0x14, 0x15, 0x16, 0x16, 0x1d, 0x12, 0x11, 0x11, 
	0x09, 0x04, 0x16, 0x19, 0x13, 0x12, 0x10, 0x12, 
	0x18, 0x19, 0x1a, 0x1b, 0x18, 0x16, 0x17, 0x12, 
	0x12, 0x14, 0x15, 0x0c, 0x14, 0x15, 0x10, 0x15, 
	0x14, 0x13, 0x18, 0x19, 0x0b, 0x0c, 0x14, 0x16, 
	0x16, 0x08, 0x05, 0x10, 0x19, 0x0e, 0x0d, 0x1c, 
	0x18, 0x1b, 0x19, 0x18, 0x17, 0x1a, 0x13, 0x0d, 
	0x10, 0x12, 0x0f, 0x1c, 0x15, 0x14, 0x13, 0x14, 
	0x15, 0x19, 0x10, 0x05, 0x0b, 0x11, 0x14, 0x11, 
	0x15, 0x12, 0x09, 0x0a, 0x0c, 0x0d, 0x16, 0x1c, 
	0x17, 0x17, 0x17, 0x17, 0x13, 0x13, 0x0a, 0x08, 
	0x0c, 0x11, 0x1a, 0x17, 0x12, 0x13, 0x16, 0x12, 
	0x13, 0x0e, 0x06, 0x10, 0x19, 0x18, 0x15, 0x12, 
	0x15, 0x10, 0x16, 0x10, 0x04, 0x11, 0x1a, 0x18, 
	0x11, 0x13, 0x14, 0x12, 0x0d, 0x10, 0x13, 0x15, 
	0x0d, 0x14, 0x16, 0x14, 0x14, 0x10, 0x10, 0x0e, 
	0x08, 0x09, 0x19, 0x13, 0x15, 0x15, 0x15, 0x16, 
	0x18, 0x18, 0x19, 0x1d, 0x1b, 0x16, 0x13, 0x10, 
	0x10, 0x0d, 0x0f, 0x0f, 0x16, 0x17, 0x17, 0x17, 
	0x15, 0x12, 0x12, 0x13, 0x13, 0x11, 0x11, 0x16, 
	0x13, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 
	0x16, 0x14, 0x17, 0x1a, 0x0f, 0x16, 0x14, 0x11, 
	0x16, 0x15, 0x15, 0x17, 0x15, 0x14, 0x17, 0x16, 
	0x13, 0x11, 0x0e, 0x10, 0x11, 0x11, 0x10, 0x12, 
	0x15, 0x17, 0x17, 0x16, 0x0f, 0x17, 0x10, 0x11, 
	0x10, 0x16, 0x13, 0x10, 0x14, 0x15, 0x17, 0x0b, 
	0x17, 0x1a, 0x17, 0x1a, 0x1b, 0x17, 0x1a, 0x1d, 
	0x13, 0x0c, 0x11, 0x0a, 0x10, 0x12, 0x11, 0x10, 
	0x14, 0x18, 0x17, 0x0e, 0x14, 0x19, 0x16, 0x11, 
	0x12, 0x17, 0x13, 0x11, 0x0e, 0x09, 0x12, 0x11, 
	0x14, 0x10, 0x10, 0x1c, 0x16, 0x11, 0x1b, 0x1a, 
	0x10, 0x12, 0x12, 0x14, 0x13, 0x14, 0x15, 0x12, 
	0x10, 0x17, 0x1b, 0x16, 0x17, 0x18, 0x1a, 0x15, 
	0x12, 0x13, 0x14, 0x12, 0x07, 0x16, 0x17, 0x14, 
	0x14, 0x0d, 0x0e, 0x1a, 0x16, 0x14, 0x13, 0x19, 
	0x1c, 0x13, 0x13, 0x11, 0x16, 0x15, 0x16, 0x15, 
	0x10, 0x10, 0x11, 0x12, 0x0f, 0x13, 0x12, 0x0d, 
	0x0c, 0x09, 0x0b, 0x0e, 0x15, 0x12, 0x13, 0x15, 
	0x18, 0x0e, 0x10, 0x18, 0x17, 0x17, 0x14, 0x14, 
	0x15, 0x0f, 0x09, 0x0f, 0x14, 0x12, 0x10, 0x13, 
	0x14, 0x11, 0x11, 0x10, 0x0e, 0x12, 0x15, 0x18, 
	0x15, 0x1a, 0x10, 0x18, 0x0f, 0x10, 0x11, 0x16, 
	0x0d, 0x0c, 0x0d, 0x15, 0x19, 0x15, 0x16, 0x16, 
	0x12, 0x17, 0x0e, 0x14, 0x15, 0x11, 0x0e, 0x0b, 
	0x14, 0x13, 0x11, 0x16, 0x0e, 0x12, 0x16, 0x14, 
	0x13, 0x15, 0x1b, 0x1a, 0x13, 0x12, 0x07, 0x09, 
	0x0d, 0x0e, 0x18, 0x13, 0x14, 0x12, 0x13, 0x11, 
	0x14, 0x12, 0x15, 0x16, 0x14, 0x0e, 0x0e, 0x0f, 
	0x13, 0x15, 0x12, 0x13, 0x0e, 0x0e, 0x12, 0x12, 
	0x15, 0x11, 0x11, 0x12, 0x15, 0x14, 0x13, 0x16, 
	0x17, 0x16, 0x15, 0x12, 0x0f, 0x16, 0x1a, 0x16, 
	0x16, 0x11, 0x14, 0x12, 0x0c, 0x0f, 0x0d, 0x12, 
	0x1c, 0x16, 0x13, 0x10, 0x10, 0x0f, 0x11, 0x13, 
	0x16, 0x15, 0x12, 0x12, 0x13, 0x14, 0x17, 0x15, 
	0x16, 0x15, 0x16, 0x16, 0x16, 0x18, 0x17, 0x18, 
	0x18, 0x15, 0x14, 0x0e, 0x12, 0x16, 0x15, 0x16, 
	0x12, 0x13, 0x16, 0x12, 0x11, 0x11, 0x13, 0x12, 
	0x16, 0x12, 0x12, 0x11, 0x11, 0x17, 0x15, 0x15, 
	0x16, 0x15, 0x15, 0x15, 0x14, 0x15, 0x17, 0x13, 
	0x15, 0x12, 0x0e, 0x0e, 0x17, 0x17, 0x14, 0x16, 
	0x18, 0x19, 0x19, 0x0e, 0x0f, 0x12, 0x13, 0x14, 
	0x12, 0x11, 0x13, 0x11, 0x12, 0x16, 0x16, 0x16, 
	0x15, 0x15, 0x14, 0x14, 0x15, 0x15, 0x18, 0x14, 
	0x14, 0x14, 0x12, 0x16, 0x12, 0x14, 0x12, 0x14, 
	0x17, 0x16, 0x1a, 0x14, 0x0f, 0x11, 0x12, 0x12, 
	0x11, 0x12, 0x14, 0x11, 0x18, 0x15, 0x16, 0x15, 
	0x18, 0x15, 0x16, 0x19, 0x16, 0x13, 0x0e, 0x14, 
	0x14, 0x14, 0x13, 0x12, 0x11, 0x12, 0x12, 0x14, 
	0x1d, 0x1a, 0x0d, 0x0f, 0x12, 0x11, 0x0f, 0x12, 
	0x16, 0x15, 0x13, 0x0d, 0x0e, 0x18, 0x19, 0x16, 
	0x12, 0x11, 0x11, 0x0a, 0x0c, 0x0c, 0x0a, 0x14, 
	0x0f, 0x18, 0x15, 0x10, 0x13, 0x12, 0x12, 0x12, 
	0x12, 0x13, 0x15, 0x08, 0x0f, 0x11, 0x0f, 0x10, 
	0x15, 0x13, 0x11, 0x0f, 0x08, 0x0a, 0x0e, 0x15, 
	0x08, 0x07, 0x0a, 0x0e, 0x0e, 0x14, 0x16, 0x18, 
	0x07, 0x0d, 0x14, 0x10, 0x13, 0x11, 0x12, 0x11, 
	0x12, 0x10, 0x14, 0x13, 0x17, 0x0e, 0x10, 0x0d, 
	0x11, 0x14, 0x0d, 0x0e, 0x16, 0x0c, 0x09, 0x06, 
	0x17, 0x17, 0x16, 0x16, 0x15, 0x13, 0x13, 0x13, 
	0x19, 0x0e, 0x0c, 0x0e, 0x13, 0x15, 0x14, 0x10, 
	0x12, 0x13, 0x11, 0x1b, 0x17, 0x0f, 0x11, 0x14, 
	0x0f, 0x08, 0x10, 0x12, 0x1e, 0x1b, 0x1b, 0x12, 
	0x12, 0x13, 0x13, 0x13, 0x13, 0x13, 0x10, 0x13, 
	0x13, 0x0d, 0x11, 0x0a, 0x0f, 0x13, 0x16, 0x15, 
	0x12, 0x10, 0x15, 0x15, 0x17, 0x14, 0x11, 0x14, 
	0x17, 0x19, 0x11, 0x13, 0x1c, 0x17, 0x1a, 0x14, 
	
};

Vtx tikispear_Torch_mesh_layer_1_vtx_cull[8] = {
	{{{-8, -69, -8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-8, -69, 8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-8, 18, 8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-8, 18, -8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{8, -69, -8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{8, -69, 8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{8, 18, 8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{8, 18, -8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx tikispear_Torch_mesh_layer_1_vtx_0[56] = {
	{{{-1, -9, -1},0, {1066, 2136},{0x84, 0xE3, 0x0, 0xFF}}},
	{{{-1, -9, 1},0, {1066, 1521},{0x84, 0xE3, 0x0, 0xFF}}},
	{{{-4, 1, 4},0, {-6, 1521},{0x84, 0xE3, 0x0, 0xFF}}},
	{{{-4, 1, -4},0, {-6, 2136},{0x84, 0xE3, 0x0, 0xFF}}},
	{{{1, -69, 1},0, {2983, 919},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{1, -9, 1},0, {-1995, 919},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-1, -9, 1},0, {-1994, 1467},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-1, -69, 1},0, {2984, 1467},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-1, -69, 1},0, {2984, 1467},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-1, -9, 1},0, {-1994, 1467},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-1, -9, -1},0, {-1990, 2015},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-1, -69, -1},0, {2987, 2015},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-1, -69, -1},0, {1008, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{1, -69, -1},0, {54, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{1, -69, 1},0, {54, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-1, -69, 1},0, {1008, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{1, -69, -1},0, {2984, 371},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{1, -9, -1},0, {-1994, 371},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{1, -9, 1},0, {-1995, 919},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{1, -69, 1},0, {2983, 919},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-1, -69, -1},0, {2987, -176},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-1, -9, -1},0, {-1990, -176},{0x0, 0x0, 0x81, 0xFF}}},
	{{{1, -9, -1},0, {-1994, 371},{0x0, 0x0, 0x81, 0xFF}}},
	{{{1, -69, -1},0, {2984, 371},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-4, 1, -4},0, {-6, 2136},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{-4, 1, 4},0, {-6, 1521},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{-4, 4, 4},0, {-1067, 1521},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{-4, 4, -4},0, {-1067, 2136},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{1, -9, 1},0, {1066, 864},{0x7C, 0xE3, 0x0, 0xFF}}},
	{{{1, -9, -1},0, {1066, 211},{0x7C, 0xE3, 0x0, 0xFF}}},
	{{{4, 1, -4},0, {-6, 211},{0x7C, 0xE3, 0x0, 0xFF}}},
	{{{4, 1, 4},0, {-6, 864},{0x7C, 0xE3, 0x0, 0xFF}}},
	{{{1, -9, -1},0, {1066, 211},{0x0, 0xE3, 0x84, 0xFF}}},
	{{{-1, -9, -1},0, {1066, -375},{0x0, 0xE3, 0x84, 0xFF}}},
	{{{-4, 1, -4},0, {-6, -375},{0x0, 0xE3, 0x84, 0xFF}}},
	{{{4, 1, -4},0, {-6, 211},{0x0, 0xE3, 0x84, 0xFF}}},
	{{{-1, -9, 1},0, {1066, 1521},{0x0, 0xE3, 0x7C, 0xFF}}},
	{{{1, -9, 1},0, {1066, 864},{0x0, 0xE3, 0x7C, 0xFF}}},
	{{{4, 1, 4},0, {-6, 864},{0x0, 0xE3, 0x7C, 0xFF}}},
	{{{-4, 1, 4},0, {-6, 1521},{0x0, 0xE3, 0x7C, 0xFF}}},
	{{{-4, 1, 4},0, {-6, 1521},{0x0, 0xFA, 0x7F, 0xFF}}},
	{{{4, 1, 4},0, {-6, 864},{0x0, 0xFA, 0x7F, 0xFF}}},
	{{{4, 4, 4},0, {-1067, 864},{0x0, 0xFA, 0x7F, 0xFF}}},
	{{{-4, 4, 4},0, {-1067, 1521},{0x0, 0xFA, 0x7F, 0xFF}}},
	{{{4, 1, -4},0, {-6, 211},{0x0, 0xFA, 0x81, 0xFF}}},
	{{{-4, 1, -4},0, {-6, -375},{0x0, 0xFA, 0x81, 0xFF}}},
	{{{-4, 4, -4},0, {-1067, -375},{0x0, 0xFA, 0x81, 0xFF}}},
	{{{4, 4, -4},0, {-1067, 211},{0x0, 0xFA, 0x81, 0xFF}}},
	{{{4, 1, 4},0, {-6, 864},{0x7F, 0xFA, 0x0, 0xFF}}},
	{{{4, 1, -4},0, {-6, 211},{0x7F, 0xFA, 0x0, 0xFF}}},
	{{{4, 4, -4},0, {-1067, 211},{0x7F, 0xFA, 0x0, 0xFF}}},
	{{{4, 4, 4},0, {-1067, 864},{0x7F, 0xFA, 0x0, 0xFF}}},
	{{{4, 4, -4},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-4, 4, -4},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-4, 4, 4},0, {45, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{4, 4, 4},0, {45, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx tikispear_Torch_mesh_layer_1_tri_0[] = {
	gsSPVertex(tikispear_Torch_mesh_layer_1_vtx_0 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
	gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
	gsSPVertex(tikispear_Torch_mesh_layer_1_vtx_0 + 32, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Vtx tikispear_Torch_mesh_layer_4_vtx_cull[8] = {
	{{{-8, -69, -8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-8, -69, 8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-8, 18, 8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-8, 18, -8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{8, -69, -8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{8, -69, 8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{8, 18, 8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{8, 18, -8},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx tikispear_Torch_mesh_layer_4_vtx_0[16] = {
	{{{-6, 1, 6},0, {280, 481},{0x0, 0xBD, 0x94, 0xFF}}},
	{{{6, 1, 6},0, {1736, 481},{0x0, 0xBD, 0x94, 0xFF}}},
	{{{8, -3, 8},0, {2018, -10},{0x0, 0xBD, 0x94, 0xFF}}},
	{{{-8, -3, 8},0, {-2, -10},{0x0, 0xBD, 0x94, 0xFF}}},
	{{{6, 1, -6},0, {280, 481},{0x0, 0xBD, 0x6C, 0xFF}}},
	{{{-6, 1, -6},0, {1736, 481},{0x0, 0xBD, 0x6C, 0xFF}}},
	{{{-8, -3, -8},0, {2018, -10},{0x0, 0xBD, 0x6C, 0xFF}}},
	{{{8, -3, -8},0, {-2, -10},{0x0, 0xBD, 0x6C, 0xFF}}},
	{{{6, 1, 6},0, {280, 481},{0x94, 0xBD, 0x0, 0xFF}}},
	{{{6, 1, -6},0, {1736, 481},{0x94, 0xBD, 0x0, 0xFF}}},
	{{{8, -3, -8},0, {2018, -10},{0x94, 0xBD, 0x0, 0xFF}}},
	{{{8, -3, 8},0, {-2, -10},{0x94, 0xBD, 0x0, 0xFF}}},
	{{{-6, 1, -6},0, {280, 481},{0x6C, 0xBD, 0x0, 0xFF}}},
	{{{-6, 1, 6},0, {1736, 481},{0x6C, 0xBD, 0x0, 0xFF}}},
	{{{-8, -3, 8},0, {2018, -10},{0x6C, 0xBD, 0x0, 0xFF}}},
	{{{-8, -3, -8},0, {-2, -10},{0x6C, 0xBD, 0x0, 0xFF}}},
};

Gfx tikispear_Torch_mesh_layer_4_tri_0[] = {
	gsSPVertex(tikispear_Torch_mesh_layer_4_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSPEndDisplayList(),
};

Vtx tikispear_Torch_mesh_layer_4_vtx_1[16] = {
	{{{-4, 4, -4},0, {-182, -260},{0x6C, 0xBD, 0x0, 0xFF}}},
	{{{-4, 4, 4},0, {-182, 1252},{0x6C, 0xBD, 0x0, 0xFF}}},
	{{{-6, 1, 6},0, {326, 1681},{0x6C, 0xBD, 0x0, 0xFF}}},
	{{{-6, 1, -6},0, {326, -689},{0x6C, 0xBD, 0x0, 0xFF}}},
	{{{4, 4, 4},0, {-182, -260},{0x94, 0xBD, 0x0, 0xFF}}},
	{{{4, 4, -4},0, {-182, 1252},{0x94, 0xBD, 0x0, 0xFF}}},
	{{{6, 1, -6},0, {326, 1681},{0x94, 0xBD, 0x0, 0xFF}}},
	{{{6, 1, 6},0, {326, -689},{0x94, 0xBD, 0x0, 0xFF}}},
	{{{4, 4, -4},0, {-182, -260},{0x0, 0xBD, 0x6C, 0xFF}}},
	{{{-4, 4, -4},0, {-182, 1252},{0x0, 0xBD, 0x6C, 0xFF}}},
	{{{-6, 1, -6},0, {326, 1681},{0x0, 0xBD, 0x6C, 0xFF}}},
	{{{6, 1, -6},0, {326, -689},{0x0, 0xBD, 0x6C, 0xFF}}},
	{{{-4, 4, 4},0, {-182, -260},{0x0, 0xBD, 0x94, 0xFF}}},
	{{{4, 4, 4},0, {-182, 1252},{0x0, 0xBD, 0x94, 0xFF}}},
	{{{6, 1, 6},0, {326, 1681},{0x0, 0xBD, 0x94, 0xFF}}},
	{{{-6, 1, 6},0, {326, -689},{0x0, 0xBD, 0x94, 0xFF}}},
};

Gfx tikispear_Torch_mesh_layer_4_tri_1[] = {
	gsSPVertex(tikispear_Torch_mesh_layer_4_vtx_1 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSPEndDisplayList(),
};

Vtx tikispear_Torch_mesh_layer_4_vtx_2[12] = {
	{{{0, 18, 0},0, {1370, 1370},{0x7D, 0x15, 0x0, 0xFF}}},
	{{{2, 4, 2},0, {1370, 210},{0x7D, 0x15, 0x0, 0xFF}}},
	{{{2, 4, -2},0, {-378, 210},{0x7D, 0x15, 0x0, 0xFF}}},
	{{{0, 18, 0},0, {-378, 210},{0x83, 0x15, 0x0, 0xFF}}},
	{{{-2, 4, -2},0, {-378, 1370},{0x83, 0x15, 0x0, 0xFF}}},
	{{{-2, 4, 2},0, {1370, 1370},{0x83, 0x15, 0x0, 0xFF}}},
	{{{0, 18, 0},0, {1370, 1370},{0x0, 0x15, 0x7D, 0xFF}}},
	{{{-2, 4, 2},0, {1370, 210},{0x0, 0x15, 0x7D, 0xFF}}},
	{{{2, 4, 2},0, {-378, 210},{0x0, 0x15, 0x7D, 0xFF}}},
	{{{0, 18, 0},0, {-378, 210},{0x0, 0x15, 0x83, 0xFF}}},
	{{{2, 4, -2},0, {-378, 1370},{0x0, 0x15, 0x83, 0xFF}}},
	{{{-2, 4, -2},0, {1370, 1370},{0x0, 0x15, 0x83, 0xFF}}},
};

Gfx tikispear_Torch_mesh_layer_4_tri_2[] = {
	gsSPVertex(tikispear_Torch_mesh_layer_4_vtx_2 + 0, 12, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSPEndDisplayList(),
};


Gfx mat_tikispear_cableWood_v4[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tikispear_red_ci8_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 5),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 32, tikispear_red_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 124, 124),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(tikispear_cableWood_v4_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_tikispear_cableWood_v4[] = {
	gsDPPipeSync(),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx mat_tikispear_headDetails_v4[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tikispear_headDetails_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 15),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 32, tikispear_headDetails_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 126, 60),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 60),
	gsSPEndDisplayList(),
};

Gfx mat_revert_tikispear_headDetails_v4[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx mat_tikispear_ropes_v4[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tikispear_ropes_ci8_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 18),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 16, tikispear_ropes_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 2, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 60, 124),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 124),
	gsSPSetLights1(tikispear_ropes_v4_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_tikispear_ropes_v4[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx mat_tikispear_blackRock_v4[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 32, tikispear_blackRock_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 124, 124),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(tikispear_blackRock_v4_lights),
	gsSPEndDisplayList(),
};

Gfx tikispear_Torch_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(tikispear_Torch_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_tikispear_cableWood_v4),
	gsSPDisplayList(tikispear_Torch_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_tikispear_cableWood_v4),
	gsSPEndDisplayList(),
};

Gfx tikispear_Torch_mesh_layer_4[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(tikispear_Torch_mesh_layer_4_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_tikispear_headDetails_v4),
	gsSPDisplayList(tikispear_Torch_mesh_layer_4_tri_0),
	gsSPDisplayList(mat_revert_tikispear_headDetails_v4),
	gsSPDisplayList(mat_tikispear_ropes_v4),
	gsSPDisplayList(tikispear_Torch_mesh_layer_4_tri_1),
	gsSPDisplayList(mat_revert_tikispear_ropes_v4),
	gsSPDisplayList(mat_tikispear_blackRock_v4),
	gsSPDisplayList(tikispear_Torch_mesh_layer_4_tri_2),
	gsSPEndDisplayList(),
};

Gfx tikispear_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

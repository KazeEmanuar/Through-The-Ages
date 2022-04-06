ALIGNED8 static const u8 coin_CoinTurn__00000_ia8[] = {
#include "actors/coin/CoinTurn__00000.ia8.inc.c"
};

ALIGNED8 static const u8 coin_CoinTurn__00019_ia8[] = {
#include "actors/coin/CoinTurn__00019.ia8.inc.c"
};

ALIGNED8 static const u8 coin_CoinTurn__00038_ia8[] = {
#include "actors/coin/CoinTurn__00038.ia8.inc.c"
};

ALIGNED8 static const u8 coin_CoinTurn__00056_ia8[] = {
#include "actors/coin/CoinTurn__00056.ia8.inc.c"
};

ALIGNED8 static const u8 coin_CoinTurn__00075_ia8[] = {
#include "actors/coin/CoinTurn__00075.ia8.inc.c"
};

ALIGNED8 static const u8 coin_CoinTurn__00094_ia8[] = {
#include "actors/coin/CoinTurn__00094.ia8.inc.c"
};

ALIGNED8 static const u8 coin_CoinTurn__00113_ia8[] = {
#include "actors/coin/CoinTurn__00113.ia8.inc.c"
};

ALIGNED8 static const u8 coin_CoinTurn__00131_ia8[] = {
#include "actors/coin/CoinTurn__00131.ia8.inc.c"
};


Vtx coin_Circle_mesh_vtx_0[3] = {
	{{{-89, -29, 0},0, {-1040, 2715},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{89, -29, 0},0, {3056, 2715},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 125, 0},0, {1008, -1210},{0xFF, 0xFF, 0xFF, 0xFF}}},
};


Gfx coin_Circle_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPSetGeometryMode(G_LIGHTING),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0),
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 252, 252),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPVertex(coin_Circle_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPEndDisplayList(),
};


#define YELLOWCOLOR gsDPSetPrimColor(0, 0, 0xff, 0xcc, 0, 255),
Gfx yellow0[] = {
	YELLOWCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00000_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx yellow1[] = {
	YELLOWCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00019_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx yellow2[] = {
	YELLOWCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00038_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx yellow3[] = {
	YELLOWCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00056_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx yellow4[] = {
	YELLOWCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00075_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx yellow5[] = {
	YELLOWCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00094_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx yellow6[] = {
	YELLOWCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00113_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx yellow7[] = {
	YELLOWCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00131_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

#define REDCOLOR gsDPSetPrimColor(0, 0, 255, 63, 63, 255),
Gfx red0[] = {
	REDCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00000_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx red1[] = {
	REDCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00019_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx red2[] = {
	REDCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00038_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx red3[] = {
	REDCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00056_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx red4[] = {
	REDCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00075_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx red5[] = {
	REDCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00094_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx red6[] = {
	REDCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00113_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx red7[] = {
	REDCOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00131_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

#define BLUECOLOR gsDPSetPrimColor(0, 0, 63, 127, 255, 255),
Gfx blue0[] = {
	BLUECOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00000_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx blue1[] = {
	BLUECOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00019_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx blue2[] = {
	BLUECOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00038_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx blue3[] = {
	BLUECOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00056_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx blue4[] = {
	BLUECOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00075_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx blue5[] = {
	BLUECOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00094_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx blue6[] = {
	BLUECOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00113_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

Gfx blue7[] = {
	BLUECOLOR
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 64, coin_CoinTurn__00131_ia8),
    gsSPBranchList(coin_Circle_mesh),
};

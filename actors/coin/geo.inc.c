// 0x1600013C
const GeoLayout yellow_coin_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 50),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow0),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow1),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow2),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow3),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow4),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow5),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow6),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x160001A0
const GeoLayout yellow_coin_no_shadow_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow0),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow1),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow2),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow3),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow4),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow5),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow6),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yellow7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16000200
const GeoLayout blue_coin_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 80),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue0),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue1),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue2),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue3),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue4),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue5),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue6),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16000264
const GeoLayout blue_coin_no_shadow_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue0),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue1),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue2),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue3),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue4),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue5),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue6),
         GEO_DISPLAY_LIST(LAYER_ALPHA, blue7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x160002C4
const GeoLayout red_coin_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xB4, 80),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red0),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red1),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red2),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red3),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red4),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red5),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red6),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16000328
const GeoLayout red_coin_no_shadow_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red0),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red1),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red2),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red3),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red4),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red5),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red6),
         GEO_DISPLAY_LIST(LAYER_ALPHA, red7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

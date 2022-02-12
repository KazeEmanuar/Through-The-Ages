#include "levels/ccm/header.h"
#include "levels/ccm/texscroll.inc.c"
#include "levels/ccm/bigblarrgg/texscroll.inc.c"
#include "levels/ccm/toadmummy/texscroll.inc.c"
#include "levels/ccm/cleopeach/texscroll.inc.c"
#include "levels/ccm/butler/texscroll.inc.c"
#include "levels/ccm/pharaoh/texscroll.inc.c"
#include "levels/ccm/crystalpillar/texscroll.inc.c"
#include "levels/ccm/smallblargg/texscroll.inc.c"
void scroll_textures_ccm() {
	scroll_ccm();

	scroll_ccm_level_geo_bigblarrgg();

	
	scroll_ccm_level_geo_toadmummy();

	scroll_ccm_level_geo_cleopeach();

	scroll_ccm_level_geo_butler();

	scroll_ccm_level_geo_pharaoh();

	scroll_ccm_level_geo_crystalpillar();

	scroll_ccm_level_geo_smallblargg();

}

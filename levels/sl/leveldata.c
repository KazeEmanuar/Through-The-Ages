#include <ultra64.h>
#include "sm64.h"
#include "surface_terrains.h"
#include "moving_texture_macros.h"
#include "level_misc_macros.h"
#include "macro_preset_names.h"
#include "special_preset_names.h"
#include "textures.h"
#include "dialog_ids.h"

#include "make_const_nonconst.h"
#include "levels/sl/texture.inc.c"
#include "levels/sl/areas/1/1/model.inc.c"
#include "levels/sl/areas/1/2/model.inc.c"
#include "levels/sl/areas/1/3/model.inc.c"
#include "levels/sl/areas/1/4/model.inc.c"
#include "levels/sl/areas/1/5/model.inc.c"
#include "levels/sl/areas/1/6/model.inc.c"
#include "levels/sl/areas/1/7/model.inc.c"
#include "levels/sl/snow_mound/model.inc.c"
#include "levels/sl/unused_cracked_ice/model.inc.c"
#include "levels/sl/unused_ice_shard/model.inc.c" // Used in the unused behavior when ground pounding the cracked ice show in the above model.
#include "levels/sl/areas/2/1/model.inc.c"
#include "levels/sl/areas/2/2/model.inc.c"
#include "levels/sl/areas/2/3/model.inc.c"
#include "levels/sl/areas/2/4/model.inc.c"
#include "levels/sl/areas/1/collision.inc.c"
#include "levels/sl/areas/1/macro.inc.c"
#include "levels/sl/snow_mound/collision.inc.c"
#include "levels/sl/unused_cracked_ice/collision.inc.c"
#include "levels/sl/areas/2/collision.inc.c"
#include "levels/sl/areas/2/macro.inc.c"
#include "levels/sl/areas/1/movtext.inc.c"
#include "levels/sl/leveldata.inc.c"

#include "levels/sl/namekfloaty/model.inc.c"
#include "levels/sl/namekfloaty/collision.inc.c"
#include "levels/sl/namekElder/model.inc.c"
#include "levels/sl/namekElder/anims/data.inc.c"
#include "levels/sl/namekElder/anims/table.inc.c"
#include "levels/sl/namekian/model.inc.c"
#include "levels/sl/walutroopa/model.inc.c"
#include "levels/sl/walutroopa/anims/data.inc.c"
#include "levels/sl/walutroopa/anims/table.inc.c"
#include "levels/sl/kiattack/model.inc.c"
#include "levels/sl/kiattack/anims/data.inc.c"
#include "levels/sl/kiattack/anims/table.inc.c"
#include "levels/sl/bulma/model.inc.c"
#include "levels/sl/bulma/anims/data.inc.c"
#include "levels/sl/bulma/anims/table.inc.c"
#include "levels/sl/dragonradar/model.inc.c"
#include "levels/sl/dragonball/model.inc.c"
#include "levels/sl/dragonball2/model.inc.c"
#include "levels/sl/dragonball3/model.inc.c"
#include "levels/sl/dragonball4/model.inc.c"
#include "levels/sl/dragonball5/model.inc.c"
#include "levels/sl/dragonball6/model.inc.c"
#include "levels/sl/dragonball7/model.inc.c"
#include "levels/sl/waluFreezF1/model.inc.c"
#include "levels/sl/waluFreezF1/anims/data.inc.c"
#include "levels/sl/waluFreezF1/anims/table.inc.c"
#include "levels/sl/kaioplanet/model.inc.c"
#include "levels/sl/deathbeam/model.inc.c"
#include "levels/sl/waluFreezF2/model.inc.c"
#include "levels/sl/waluFreezF2/anims/data.inc.c"
#include "levels/sl/waluFreezF2/anims/table.inc.c"
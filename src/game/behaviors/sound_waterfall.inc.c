// sound_waterfall.inc.c

void bhv_waterfall_sound_loop(void) {
    cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
}

void bhv_bgm_player(void) {
    switch (o->oBehParams2ndByte) {
        case 0:
            play_sound(SOUND_ENV_ELDORADOBGM, gDefaultSoundArgs);
            break;
        case 2:
          //  play_sound(SOUND_ENV_BABYLONBGM, gDefaultSoundArgs);
            break;
    }
}

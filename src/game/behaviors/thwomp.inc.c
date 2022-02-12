// thwomp.c.inc

void grindel_thwomp_act_4(void) {
    if (o->oTimer == 0)
        o->oThwompRandomTimer = random_float() * 10.0f + 20.0f;
    if (o->oTimer > o->oThwompRandomTimer)
        o->oAction = 0;
}

void grindel_thwomp_act_2(void) {
    cur_obj_update_floor_height();
    o->oVelY += -4.0f;
    o->oPosY += o->oVelY;
    if (o->oPosY < o->oFloorHeight + 1.0f) {
        o->oPosY = o->oFloorHeight + 1.0f;
        o->oVelY = 0;
        o->oAction = 3;
    }
}

void grindel_thwomp_act_3(void) {
    if (o->oTimer == 0)
        if (o->oDistanceToMario < 3500.0f) {
            cur_obj_shake_screen(SHAKE_POS_SMALL);
            cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
        }
    if (o->oTimer > 9)
        o->oAction = 4;
}

void grindel_thwomp_act_1(void) {
    if (o->oTimer == 0)
        o->oThwompRandomTimer = random_float() * 30.0f + 10.0f;
    if (o->oTimer > o->oThwompRandomTimer)
        o->oAction = 2;
}

void grindel_thwomp_act_0(void) {
    if (!o->oBehParams2ndByte) {

        cur_obj_resolve_wall_collisions();
        if (cur_obj_lateral_dist_from_mario_to_home() < 4000.f) {
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x400);
            o->oForwardVel = 15.f;
            o->oVelX = sins(o->oMoveAngleYaw) * o->oForwardVel;
            o->oVelZ = coss(o->oMoveAngleYaw) * o->oForwardVel;
        } else {
            o->oVelX = 0.f;
            o->oVelZ = 0.f;
        }
        o->oPosX += o->oVelX;
        o->oPosZ += o->oVelZ;
    }
    if (o->oBehParams2ndByte + 40 < o->oTimer) {
        o->oAction = 1;
        o->oPosY += 5.0f;
    } else
        o->oPosY += 10.0f;
}

void (*sGrindelThwompActions[])(void) = { grindel_thwomp_act_0, grindel_thwomp_act_1,
                                          grindel_thwomp_act_2, grindel_thwomp_act_3,
                                          grindel_thwomp_act_4 };

void bhv_grindel_thwomp_loop(void) {
    if (gCurrLevelNum != LEVEL_LLL) {
        o->oFaceAngleYaw = o->oMoveAngleYaw + 0x4000;
    }
    cur_obj_call_action_function(sGrindelThwompActions);
    if (cur_obj_dist_to_nearest_object_with_behavior(bhvExplosion) < 750.f) {
        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
        o->oNumLootCoins = 2;
        obj_explode_and_spawn_coins(80.0f, 2);
    }
}

// bhvExplosion
void bhv_thwomp_explosive(void) {
    if (cur_obj_dist_to_nearest_object_with_behavior(bhvExplosion) < 750.f) {
        play_puzzle_jingle();
        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
        obj_explode_and_spawn_coins(80.0f, 0);
    }
}
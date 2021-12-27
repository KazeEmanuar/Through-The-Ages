// dolphin.c.inc
#include "sm64.h"
#include "types.h"
//#include "game/game.h"
#include "game/level_update.h"
#include "dialog_ids.h"
#include "game/object_helpers.h"
//#include "game/kaze_library.h"
#include "seq_ids.h"
#include "game/camera.h"
#include "engine/math_util.h"
#include "buffers/buffers.h"
#include "game/segment2.h"
#include "game/ingame_menu.h"
#include "audio/external.h"
#include "engine/surface_collision.h"

#define m gMarioState
#define o gCurrentObject
#pragma intrinsic(sqrtf)

void breakCannon(void) {
    if (o->oTimer > 20) {
        if (o->oDistanceToMario < 150.f) {
            gMarioState->pos[0] = o->oPosX;
            gMarioState->pos[1] = o->oPosY;
            gMarioState->pos[2] = o->oPosZ;
            gMarioState->faceAngle[1] = o->oFaceAngleYaw;
            gMarioState->action = ACT_SHOT_FROM_CANNON;
            o->oTimer = 0;
            gMarioState->vel[1] = 25.f;
            gMarioState->forwardVel = 60.f;
        }
    }
}
// talkanim
// idleanim
// shootanim
// damageanim
extern s16 newcam_yaw;
u8 shootcannons = 0;
void kingpiratecode(void) {
    if (!o->oOpacity) {
        o->oOpacity = 1;
        newcam_yaw = 0;
        o->oGraphYOffset = -0x0165;
        o->oHealth = 0;
    }
    switch (o->oAction) {
        case 0:
            // wait till land
            if (gMarioState->action != ACT_SHOT_FROM_CANNON) {
                o->oAction = 1;
            }
            break;
        case 1:
            // talk
            if (talkToMario(115)) {
                o->oAction++;
                sequence_player_unlower(SEQ_PLAYER_LEVEL, 60);
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
            }
            break;
        case 2:
            // idlr
            if (o->header.gfx.unk38.animID == 0) {
                if ((o->header.gfx.unk38.animFrame == 9) || (o->header.gfx.unk38.animFrame == 49)) {
                    if ((random_u16() % (19 - o->oHealth * 3)) < 7) {
                        // random generate a cannon to shoot from
                        cur_obj_init_animation(1);
                        shootcannons |= ((random_u16() & 1) + 1);
                    }
                }
            } else if (cur_obj_check_if_at_animation_end()) {
                cur_obj_init_animation(0);
            }
            if (o->oHealth > 4) {
                o->oAction = 5;
            }
            break;
        case 4:
            // damage
            break;
        case 5:
            // deathspeech
            cur_obj_init_animation(0);
            if (talkToMario(116)) {
                o->oAction++;
                stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                cur_obj_spawn_star_at_y_offset(gMarioState->pos[0], gMarioState->pos[1] + 200.f,
                                               gMarioState->pos[2], 200.f);
            }
            break;
        case 6:
            // spawnstar
            break;
    }
}

void cannonking(void) {
    if (shootcannons & o->oBehParams2ndByte) {
        shootcannons &= ~o->oBehParams2ndByte;
        spawn_object(o, MODEL_BLACK_BOBOMB, bhvCannonOmb);
        play_sound(SOUND_GENERAL_WALL_EXPLOSION, gDefaultSoundArgs);
        spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
    }
}

void cannonomb(void) {
    f32 x, z;
    if (!o->oAction) {
        if (!o->oTimer) {
            // aim at some point in a 200 coordinate radius around mario
            o->oDrawingDistance = 60000.f;
            x = gMarioState->pos[0] + random_f32_around_zero(300.f);
            z = gMarioState->pos[2] + random_f32_around_zero(300.f);
            o->oVelY = 50.f;
            o->oMoveAngleYaw = atan2s(o->oPosZ - z, o->oPosX - x) + 0x8000;
            o->oForwardVel =
                sqrtf((o->oPosZ - z) * (o->oPosZ - z) + (o->oPosX - x) * (o->oPosX - x)) / (55.f);
        }
        if (o->oTimer > 20) {
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                obj_mark_for_deletion(o);
                spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
            }
        }
        if (o->oDistanceToMario < 100.f) {
            if (gMarioState->action & ACT_FLAG_ATTACKING) {
                o->oMoveAngleYaw += 0x8000;
                o->oVelY = 50.f;
                o->oAction = 1;
            } else {
                obj_mark_for_deletion(o);
                spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
            }
        }
    } else {
        if (o->oTimer == 50) {
            obj_mark_for_deletion(o);
            spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
            if (cur_obj_nearest_object_with_behavior(bhvKingPirate)) {
                cur_obj_nearest_object_with_behavior(bhvKingPirate)->oHealth++;
                play_sound(SOUND_OBJ2_KING_BOBOMB_DAMAGE, gDefaultSoundArgs);
                spawn_triangle_break_particles(20, 138, 2.0f, 0);
                spawn_triangle_break_particles(20, 116, 1.0f, 0);
            }
        }
    }
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);
}

s16 object_stepfish(void) {
    struct Surface *sObjFloor;
    f32 objX = o->oPosX;
    f32 objY = o->oPosY;
    f32 objZ = o->oPosZ;

    f32 floorY;

    f32 objVelX = o->oVelX;
    f32 objVelZ = o->oVelZ;
    s16 collisionFlags = 0;

    // Find any wall collisions, receive the push, and set the flag.
    if (obj_find_wall(objX + objVelX, objY, objZ + objVelZ, objVelX, objVelZ) == 0) {
    }

    floorY = find_floor(objX + objVelX, objY, objZ + objVelZ, &sObjFloor);
    if (o->oPosY < floorY) {
        o->oPosY = floorY;
    }

    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
    o->oPosY += o->oVelY;

    return collisionFlags;
}

extern s8 sOrientObjWithFloor;
void goToPoint() {
    s16 targetAngle, targetPitch;
    f32 targetSpeed;
    targetAngle = atan2s(o->oBobombBuddyPosZCopy - o->oPosZ, o->oBobombBuddyPosXCopy - o->oPosX);
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x0380);
    targetPitch =
        -atan2s(sqrtf((o->oBobombBuddyPosZCopy - o->oPosZ) * (o->oBobombBuddyPosZCopy - o->oPosZ)
                      + (o->oBobombBuddyPosXCopy - o->oPosX) * (o->oBobombBuddyPosXCopy - o->oPosX)),
                o->oBobombBuddyPosYCopy - o->oPosY);
    o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, targetPitch, 0x0380);
    targetSpeed = 4.f * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f)
                  * (coss(targetPitch - o->oFaceAnglePitch) + 1.0f);
    o->oForwardVel = approach_f32(o->oForwardVel, targetSpeed, 1.2f, 2.f);
    o->oVelY = sins(-o->oFaceAnglePitch) * o->oForwardVel;
    o->oVelX = coss(-o->oFaceAnglePitch) * sins(o->oMoveAngleYaw) * o->oForwardVel;
    o->oVelZ = coss(-o->oFaceAnglePitch) * coss(o->oMoveAngleYaw) * o->oForwardVel;
    if (o->oFaceAnglePitch > 0x1000) {
        o->oFaceAnglePitch = 0x1000;
    }
    sOrientObjWithFloor = FALSE;
    object_stepfish();
    sOrientObjWithFloor = TRUE;
}

void evilShark(void) {
    switch (o->oAction) {
        case 0:
            if (gMarioState->action & ACT_FLAG_SWIMMING) {
                if (gMarioState->pos[0] < 0.f) {
                    if (o->oPosX < 0.f) {
                        o->oAction = 1;
                    }
                } else if (o->oPosX > 0.f) {
                    o->oAction = 1;
                }
            }
            break;
        case 1:
            cur_obj_init_animation(0);
            if ((gMarioState->pos[1] == gMarioState->floorHeight)
                && !(gMarioState->action & ACT_FLAG_SWIMMING)) {
                o->oAction++;
            }
            // approach mario then bite
            play_secondary_music(SEQ_EVENT_JAW, 0, 255, 1000);
            vec3f_copy(&o->oBobombBuddyPosXCopy, gMarioState->pos);
            goToPoint();
            break;
        case 2:
            cur_obj_init_animation(0);
            if (gMarioState->action & ACT_FLAG_SWIMMING) {
                if (gMarioState->pos[2] < 0.f) {
                    if (o->oPosZ < 0.f) {
                        o->oAction = 1;
                    }
                } else if (o->oPosZ > 0.f) {
                    o->oAction = 1;
                }
            }
            func_80321080(50);
            vec3f_copy(&o->oBobombBuddyPosXCopy, &o->oHomeX);
            goToPoint();
            o->oPosY -= 0x10;
            break;
    }
    if (o->oDistanceToMario < 250.f) {
        if (!o->oOpacity) {
            o->oOpacity = 1;
            o->oAction = 2;
            m->interactObj = o;
            set_mario_action(m, ACT_EATEN_BY_BUBBA, 0);
            cur_obj_play_sound_2(SOUND_OBJ2_PIRANHA_PLANT_BITE);
        }
    }
}

void pirateskel(void) {
    o->oGraphYOffset = -100.f;
    switch (o->oAction) {
        case 0:
            // wait mario close
            o->oInteractType = INTERACT_IGLOO_BARRIER;
            o->hitboxHeight = 20.f;
            cur_obj_init_animation(0);
            o->header.gfx.unk38.animFrame = 0;
            if (o->oDistanceToMario < 1200.f) {
                o->oAction = 1;
                cur_obj_play_sound_2(SOUND_GENERAL_BOAT_ROCK);
            }
            break;
        case 1:
            // get up
            if (o->header.gfx.unk38.animFrame > 35) {
                o->oAngleVelYaw -= 0x100;
                o->oForwardVel += 3.f;
            }
            if (o->header.gfx.unk38.animFrame >= 40) {
                o->oAction = 2;
            }
            break;
        case 2:
            // wildly swing at mario
            o->oInteractType = INTERACT_DAMAGE;
            o->hitboxHeight = 250.f;
            o->oAngleVelYaw = approach_s16_symmetric(o->oAngleVelYaw, -0x1140, 0x0200);
            o->header.gfx.unk38.animFrame = 40;
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 18.f, 1.f);
            if (!(o->oTimer % 13)) {
                cur_obj_play_sound_2(SOUND_GENERAL_SWISH_AIR_2);
            }
            if ((o->oTimer > 100)) {
                o->oAction = 3;
            }
            break;
        case 3:
            // wildly swing at mario
            o->header.gfx.unk38.animFrame = 40;
            o->oAngleVelYaw = approach_s16_symmetric(o->oAngleVelYaw, 0, 0x0018 * o->oTimer);
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0.f, 1.f);
            if (o->oAngleVelYaw == 0) {
                o->oInteractType = INTERACT_IGLOO_BARRIER;
                o->oAction = 4;
                cur_obj_play_sound_2(SOUND_GENERAL_BOAT_ROCK);
            }
            break;
        case 4:
            // lie back down
            o->oForwardVel = 0.f;
            if (o->oTimer > 10) {

                o->hitboxHeight = 20.f;
            }
            if (o->oTimer > 120) {
                o->oAction = 0;
            }
            break;
    }
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x280);
    o->oFaceAngleYaw += o->oAngleVelYaw;
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-78);
}
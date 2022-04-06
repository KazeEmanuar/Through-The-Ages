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

u16 shoeTimer = 0;
extern const Trajectory ddd_area_1_spline_LuigiTrack[];
#define pointgoal o->oOpacity
#define /*0x0F8*/ yoshi1 OBJECT_FIELD_OBJ(0x1C)
#define /*0x0F4*/ yoshi2 OBJECT_FIELD_OBJ(0x1B)
void luigiChariot(void) {
    f32 dist;
    u16 targetAngle;
    u16 targetPitch;
    f32 x, y, z;
    f32 targetSpeed;
    u32 i;
    struct Object *yosher;
    if (!o->yoshi1) {
        o->yoshi1 = spawn_object(o, 0x37, bhvYoshiChariot);
        o->yoshi1->oHiddenBlueCoinSwitch = o;
        o->yoshi2 = spawn_object(o, 0x37, bhvYoshiChariot);
        o->yoshi2->oHiddenBlueCoinSwitch = o;
        o->oPosY += 27.f;
    }
#define dLeft 75.f
#define dY 0.f
#define dForwward 100.f
    obj_set_pos_relative(o->yoshi1, o, dLeft, dY, dForwward);
    obj_set_pos_relative(o->yoshi2, o, -dLeft, dY, dForwward);
    if (!o->oBehParams) {
        switch (o->oAction) {
            case 0:
                // just wait
                if (o->oSubAction) {
                    if (o->oDistanceToMario < 500.f) {
                        o->oAction = 1;
                    }
                } else {
                    if (o->oDistanceToMario > 550.f) {
                        o->oSubAction = 1;
                    }
                }
                break;
            case 1:
                // just talk, ask for race if on act 2
                if (gCurrActNum < 2) {
                    if (talkToMarioNoRotation(78)) {
                        o->oAction = 0;
                    }
                } else {
                    switch (askMario(81, 0)) {
                        case 0:
                            break;
                        case 1:
                            o->oAction = 2;
                            break;
                        case 2:
                            o->oAction = 0;
                            break;
                    }
                }
                break;
            case 2:
                // do the racing
                o->oBobombBuddyPosXCopy =
                    ((s16 *) segmented_to_virtual(ddd_area_1_spline_LuigiTrack))[1 + pointgoal * 4];
                o->oBobombBuddyPosYCopy =
                    ((s16 *) segmented_to_virtual(ddd_area_1_spline_LuigiTrack))[2 + pointgoal * 4];
                o->oBobombBuddyPosZCopy =
                    ((s16 *) segmented_to_virtual(ddd_area_1_spline_LuigiTrack))[3 + pointgoal * 4];

                dist = sqrtf(
                    (o->oBobombBuddyPosZCopy - o->oPosZ) * (o->oBobombBuddyPosZCopy - o->oPosZ)
                    + (o->oBobombBuddyPosXCopy - o->oPosX) * (o->oBobombBuddyPosXCopy - o->oPosX)
                    + (o->oBobombBuddyPosYCopy - o->oPosY) * (o->oBobombBuddyPosYCopy - o->oPosY));
                if (pointgoal < 16) {
                    targetAngle =
                        atan2s(o->oBobombBuddyPosZCopy - o->oPosZ, o->oBobombBuddyPosXCopy - o->oPosX);
                    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x0240);
                    targetPitch = -atan2s(sqrtf((o->oBobombBuddyPosZCopy - o->oPosZ)
                                                    * (o->oBobombBuddyPosZCopy - o->oPosZ)
                                                + (o->oBobombBuddyPosXCopy - o->oPosX)
                                                      * (o->oBobombBuddyPosXCopy - o->oPosX)),
                                          o->oBobombBuddyPosYCopy - o->oPosY);
                    if (o->oTimer > 50) {
                        o->oFaceAnglePitch =
                            approach_s16_symmetric(o->oFaceAnglePitch, targetPitch, 0x0100);
                    }

                    o->oForwardVel = approach_f32(o->oForwardVel,
                                                  5.5f * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f)
                                                      * (coss(targetPitch - o->oFaceAnglePitch) + 1.0f),
                                                  0.2f, 1.f);
                } else {
                    o->oForwardVel = approach_f32(o->oForwardVel, 0, 0.2f, .5f);
                    if (o->oForwardVel < 1.f) {
                        if (cur_obj_nearest_object_with_behavior(bhvRaceCheck)->oOpacity) {
                            o->oAction = 4;
                        } else {
                            o->oAction = 3;
                        }
                    }
                    approach_s16_symmetric(o->oFaceAnglePitch, 0, 0x0100);
                }
                o->oVelY = sins(-o->oFaceAnglePitch) * o->oForwardVel;
                o->oVelX = coss(-o->oFaceAnglePitch) * sins(o->oMoveAngleYaw) * o->oForwardVel;
                o->oVelZ = coss(-o->oFaceAnglePitch) * coss(o->oMoveAngleYaw) * o->oForwardVel;
                cur_obj_move_using_vel();
                if (dist < 250.f) {
                    pointgoal++;
                }
                break;
            case 3:
                // wait at goal
                if (!o->oSubAction) {
                    if (o->oDistanceToMario < 500.f) {
                        o->oSubAction = 1;
                    }
                } else {
                    o->oForwardVel = 0;
                    o->oFaceAnglePitch = 0;
                    if (talkToMarioNoRotation(82)) {
                        o->oAction = 5;
                    }
                }
                break;
            case 4:
                // talk at goal
                if (!o->oSubAction) {
                    if (o->oDistanceToMario < 500.f) {
                        o->oSubAction = 1;
                    }
                } else {
                    o->oForwardVel = 0;
                    o->oFaceAnglePitch = 0;
                    if (talkToMarioNoRotation(86)) {
                        o->oAction = 5;
                        // give mario rainbow boots
                        shoeTimer = 1;
                    }
                }
                break;
            case 5:
                break;
        }
    } else {
        switch (o->oAction) {
            case 0:
                // off screen
                if (o->oTimer > 120) {
                    o->oAction++;
                    o->oBobombBuddyPosXCopy = -350.f;
                    o->oBobombBuddyPosYCopy = 1000.f;
                    o->oBobombBuddyPosZCopy = 13200.f;
                }
                break;
            case 1:
                // fly to mario
                x = o->oPosX - o->oBobombBuddyPosXCopy;
                y = o->oPosY - o->oBobombBuddyPosYCopy;
                z = o->oPosZ - o->oBobombBuddyPosZCopy;
                if (sqrtf(x * x + y * y + z * z) < 500.f) {
                    o->oAction++;
                }
                break;
            case 2:
                // talk to mario
                o->oBobombBuddyPosXCopy = o->oPosX;
                o->oBobombBuddyPosYCopy = o->oPosY;
                o->oBobombBuddyPosZCopy = o->oPosZ;
                if (talkToMarioNoRotation(104)) {
                    o->oAction = 3;
                }
                break;
            case 3:
                // drop yoshi
                yosher = spawn_object(o, 0x37, bhvYoshiRiding);
                yosher->oVelY = 45.f;
                yosher->oForwardVel = 30.f;
                o->oBobombBuddyPosXCopy = o->oHomeX;
                o->oBobombBuddyPosYCopy = o->oHomeY;
                o->oBobombBuddyPosZCopy = o->oHomeZ;
                o->oAction++;
                break;
            case 4:
                // fly around idly
                x = o->oPosX - o->oBobombBuddyPosXCopy;
                y = o->oPosY - o->oBobombBuddyPosYCopy;
                z = o->oPosZ - o->oBobombBuddyPosZCopy;
                if (!cur_obj_nearest_object_with_behavior(bhvYoshiRiding)) {
                    o->oAction = 5;
                    o->oBobombBuddyPosXCopy = -350.f;
                    o->oBobombBuddyPosYCopy = 1000.f;
                    o->oBobombBuddyPosZCopy = 13200.f;
                }
                break;
            case 5:
                // fly to mario
                x = o->oPosX - o->oBobombBuddyPosXCopy;
                y = o->oPosY - o->oBobombBuddyPosYCopy;
                z = o->oPosZ - o->oBobombBuddyPosZCopy;
                if (sqrtf(x * x + y * y + z * z) < 500.f) {
                    o->oAction = 3;
                }
        }
        if (o->oAction && (o->oAction != 2)) {
            dist = sqrtf((o->oBobombBuddyPosZCopy - o->oPosZ) * (o->oBobombBuddyPosZCopy - o->oPosZ)
                         + (o->oBobombBuddyPosXCopy - o->oPosX) * (o->oBobombBuddyPosXCopy - o->oPosX)
                         + (o->oBobombBuddyPosYCopy - o->oPosY) * (o->oBobombBuddyPosYCopy - o->oPosY));
            dist = (dist) / 3500.f;
            targetAngle =
                atan2s(o->oBobombBuddyPosZCopy - o->oPosZ, o->oBobombBuddyPosXCopy - o->oPosX);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x0080);
            targetPitch = -atan2s(
                sqrtf((o->oBobombBuddyPosZCopy - o->oPosZ) * (o->oBobombBuddyPosZCopy - o->oPosZ)
                      + (o->oBobombBuddyPosXCopy - o->oPosX) * (o->oBobombBuddyPosXCopy - o->oPosX)),
                o->oBobombBuddyPosYCopy - o->oPosY);
            o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, targetPitch, 0x0080);
            targetSpeed = 8.f * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f)
                              * (coss(targetPitch - o->oFaceAnglePitch) + 1.0f) * dist
                          + 10.f;
            if (targetSpeed > 70) {
                targetSpeed = 70.f;
            }
            o->oForwardVel = approach_f32(o->oForwardVel, targetSpeed, 0.2f, 2.f);
            o->oVelY = sins(-o->oFaceAnglePitch) * o->oForwardVel;
            o->oVelX = coss(-o->oFaceAnglePitch) * sins(o->oMoveAngleYaw) * o->oForwardVel;
            o->oVelZ = coss(-o->oFaceAnglePitch) * coss(o->oMoveAngleYaw) * o->oForwardVel;
            cur_obj_move_using_vel();
        }
    }
}

void yoshiChariot(void) {
    if (!o->oOpacity) {
        o->header.gfx.unk38.animFrame = random_u16() % 60;
        o->oOpacity = 1;
    }
    if (gCurrAreaIndex == 3) {
        cur_obj_init_animation(1);
    } else {
        if (o->oHiddenBlueCoinSwitch->oAction == 2) {
            cur_obj_init_animation(1);
        } else {
            cur_obj_init_animation(0);
        }
    }
}
u8 onYoshi = 0;
void yoshiRiding(void) {
    float x, y, z;
    f32 bonusAdd = 0;
    u32 i;
    struct Object *eaten;
    o->oForwardVel *= 0.98f;
    o->oDrawingDistance = 100000.f;
    if (o->oPosY < -3000.f) {
        obj_mark_for_deletion(o);
    }
    switch (o->oAction) {
        case 0:
            // stand idle wait for mario to mount
            if (!onYoshi) {
                cur_obj_init_animation(0);
                if (gMarioState->vel[1] < 0.f) {
                    y = o->oPosY - gMarioState->pos[1];
                    if (lateral_dist_between_objects(o, gMarioState->marioObj) < 150.f) {
                        if ((y < 0.f) && (y > -180.f)) {
                            if (!(gMarioState->action
                                  & (ACT_FLAG_INTANGIBLE | ACT_FLAG_SWIMMING
                                     | ACT_FLAG_SWIMMING_OR_FLYING))) {
                                set_mario_animation(m, MARIO_ANIM_HOLDING_BOWSER);
                                onYoshi = 1;
                                cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_TALK);
                                gMarioState->pos[1] = gMarioState->floorHeight + 100.f;
                                gMarioState->vel[1] = 40.f;
                                gMarioState->action = ACT_FLYING;
                                gMarioState->faceAngle[0] = 0x4000;
                                return;
                            }
                        }
                    }
                }
                cur_obj_update_floor_and_walls();
                cur_obj_move_standard(78);
            } else {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                cur_obj_init_animation(1);
                bonusAdd = sins((0x10000 / 0x1D) * (o->header.gfx.unk38.animFrame + 4) * 2.f) * 2.f;
            }
            break;
    }
    if (onYoshi) {
        // gMarioState->faceAngle[0] = 0;
        // gMarioState->faceAngle[2] = 0;
        o->oIntangibleTimer = -1;
        obj_copy_pos_and_angle(o, gMarioState->marioObj);
        // o->oFaceAnglePitch =gMarioState->faceAngle[2] ;
        // o->oFaceAngleRoll = -(gMarioState->faceAngle[0] -0x1000);
        o->oFaceAnglePitch = 0;
        o->oFaceAngleRoll = 0;
        gMarioState->marioObj->oFlags &= OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE;
#define HORIZOFFSET 50.f
#define VERTOFFSET 55.f
        gMarioState->marioObj->header.gfx.pos[1] = gMarioState->pos[1] + VERTOFFSET + bonusAdd;
        gMarioState->marioObj->header.gfx.pos[0] =
            gMarioState->pos[0] + HORIZOFFSET * sins(gMarioState->faceAngle[1]);
        gMarioState->marioObj->header.gfx.pos[2] =
            gMarioState->pos[2] + HORIZOFFSET * coss(gMarioState->faceAngle[1]);
        // gMarioState->marioObj->header.gfx.angle[0] = -gMarioState->faceAngle[0];
       // gMarioState->marioObj->header.gfx.angle[0] = 0;
       o->oFaceAngleRoll = gMarioState->marioObj->header.gfx.angle[0];
        gMarioState->marioObj->header.gfx.angle[1] = gMarioState->faceAngle[1];
        // gMarioState->marioObj->header.gfx.angle[2] = gMarioState->faceAngle[2];
        gMarioState->marioObj->header.gfx.angle[2] = 0;
        if ((gMarioState->action != ACT_FLYING_TRIPLE_JUMP) && (gMarioState->action != ACT_FLYING)) {
            onYoshi = 0;
            if (gMarioState->action == ACT_SPECIAL_TRIPLE_JUMP){
                mark_obj_for_deletion(o);
            }
        }
    }
#define YOSHIHORIZ 80.f
    o->header.gfx.pos[0] = o->oPosX + sins(o->oMoveAngleYaw) * YOSHIHORIZ;
    o->header.gfx.pos[1] = o->oPosY;
    o->header.gfx.pos[2] = o->oPosZ + coss(o->oMoveAngleYaw) * YOSHIHORIZ;
    o->header.gfx.angle[0] = o->oFaceAngleRoll;
    o->header.gfx.angle[1] = o->oFaceAngleYaw;
    o->header.gfx.angle[2] = o->oFaceAnglePitch;
}

void racecheck(void) {
    if (o->oDistanceToMario < 500.f + ((o->oBehParams & 0xFF000000) >> 20)) {
        if (o->oBehParams2ndByte == 2) {
            if (cur_obj_nearest_object_with_behavior(bhvRaceCheck)->oAction) {
                if (!o->oAction) {
                    cur_obj_play_sound_2(SOUND_GENERAL2_RIGHT_ANSWER);
                }
                o->oOpacity = 1;
                o->oAction = 1;
            }
        } else {
            if (!o->oAction) {
                cur_obj_play_sound_2(SOUND_GENERAL2_RIGHT_ANSWER);
            }
            o->oAction = 1;
        }
    }
}
Gfx SOLID = gsDPSetPrimColor(0, 0, 0, 0, 0, 255);
extern Gfx mat_ddd_dl_RAINBOWTEX[];
#define REMOVEHATTIME 10
void controlHat(void) {
    struct Object *zeus;
    Gfx *rainbow = segmented_to_virtual(mat_ddd_dl_RAINBOWTEX);
    if (!o->oOpacity) {
        o->oOpacity = 1;
        if ((gCurrActNum > 1) && (gCurrActNum < 6)) {
            o->oAction = 1;
        }
        if (gCurrActNum > 2) {
            shoeTimer = 1;
        }
    }
    if (zeus = cur_obj_nearest_object_with_behavior(bhvZeus)) {
        if (zeus->oAction == 2) {
            if (zeus->oTimer > REMOVEHATTIME) {
                o->oAction = 1;
            }
        }
    }
    if (o->oAction) {
        gMarioState->flags &= ~MARIO_CAP_ON_HEAD;
    } else {
        gMarioState->flags |= MARIO_CAP_ON_HEAD;
    }
    if (shoeTimer) {
        rainbow[12] = SOLID;
    }
}

void zeusCode(void) {
    cur_obj_scale(3.f);
    switch (o->oAction) {
        case 0:
            // wait for mario
            if (lateral_dist_between_objects(o, gMarioState->marioObj) < 750.f) {
                o->oAction++;
            }
            break;
        case 1:
            // talk to mario
            if (talkToMarioNoRotation(87)) {
                o->oAction++;
                gMarioState->action = ACT_WAITING_FOR_DIALOG;
            }
            break;
        case 2:
            // electrocutes mario, hat levitates to him, he holds it
            if (o->oTimer == REMOVEHATTIME) {
                spawn_object(gMarioState->marioObj, 0x3A, bhvLightning);
                gMarioState->action = ACT_SHOCKED;
                o->oHiddenBlueCoinSwitch = spawn_object(o, MODEL_MARIOS_CAP, bhvStaticObject);
                o->oHiddenBlueCoinSwitch->oPosY += 375.f;
                o->oHiddenBlueCoinSwitch->oOpacity = 255;
                obj_scale(o->oHiddenBlueCoinSwitch, 3.f);
            }
            if (o->oTimer > REMOVEHATTIME + 10) {
                o->oAction++;
            }
            break;
        case 3:
            // thanks mario, taunts him for not having a hat anymore, spawns star
            if (talkToMarioNoRotation(88)) {
                o->oAction++;
                spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 200.f,
                                   gMarioState->pos[2]);
            }
            break;
        case 4:
            // idles and laughs
            break;
    }
}

void medusacode(void) {
    rotateTowardsMario(0x400);
    switch (o->oAction) {
        case 0:
            if (talkToMario(89)) {
                o->oAction++;
                sequence_player_unlower(SEQ_PLAYER_LEVEL, 60);
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
            }
            break;
        case 1:
            if (o->oTimer > 32) {
                if (gMarioState->pos[0] > 1800.f) {
                    if (gMarioState->pos[1] > -1.f) {
                        if (abs_angle_diff(gMarioState->faceAngle[1], o->oFaceAngleYaw) > 0x5000) {
                            if (cur_obj_nearest_object_with_behavior(bhvStar)) {
                                o->oAction = 2;
                                o->oDamageOrCoinValue = gMarioState->action;
                                gMarioState->action = 0;
                                play_sound(SOUND_MARIO_WAAAOOOW,
                                           m->marioObj->header.gfx.cameraToObject);
                                o->oOpacity = gMarioState->marioObj->header.gfx.unk38.animFrame;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            // mario DIES
            gMarioState->marioObj->header.gfx.unk38.animFrame = o->oOpacity;
            o->header.gfx.unk38.animFrame++;
            gMarioState->health -= 0x10;
            if (gMarioState->health < 0x100) {
                level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                o->oAction = 1;
                gMarioState->action = o->oDamageOrCoinValue;
            }
            if (o->oTimer > 32) {
                o->oAction = 1;
                gMarioState->action = o->oDamageOrCoinValue;
            }
            break;
    }
}

void setBoxSize(void) {
    o->hitboxRadius = o->oBehParams2ndByte * 2;
    o->hitboxHeight = (o->oBehParams & 0xFF) * 2;
}

void checknipperwarp() {
    // SURFACE_NO_CAM_COLLISION
    if (gMarioState->floor && (gMarioState->floor->object == o) && (sSourceWarpNodeId != 0x1b)) {
        o->oOpacity++;
        if (o->oOpacity > 20) {
            m->usedObj = o;
            level_trigger_warp(gMarioState, WARP_OP_WARP_OBJECT);
            gMarioState->action = ACT_DISAPPEARED;
            gMarioObject->header.gfx.sharedChild = 0;
            sSourceWarpNodeId = 0x1B;
        }
    } else {
        o->oOpacity = 0;
    }
}

extern Vtx ddd_dl_Clouds_mesh_layer_1_vtx_0[1627];
u32 waterphas2e = 0;
extern f32 backupPos[3];
void olympship(void) {
    Vtx *a = segmented_to_virtual(ddd_dl_Clouds_mesh_layer_1_vtx_0);
    u8 alpha;
    u16 i;
    u16 brightness;
    if (gCurrAreaIndex>1){
    backupPos[0] = o->oPosX;
    backupPos[1] = o->oPosY+500.f;
    backupPos[2] = o->oPosZ;
    }
#define WAVEHEIGHTMAX (512)
#define SCROLLSIZE 6
    if (o->oBehParams2ndByte) {
        checknipperwarp();
    } else {
        if (o->oBehParams & 0x00000001) {
            waterphas2e += 0x10;
            for (i = 0; i < 1627; i++) {
                alpha = 0;
                a[i].n.ob[1] = -4096
                               + sins(a[i].n.ob[2] * SCROLLSIZE + waterphas2e * 17) * WAVEHEIGHTMAX
                               + sins((a[i].n.ob[0] + a[i].n.ob[2] / 4) * SCROLLSIZE + waterphas2e * 16)
                                     * WAVEHEIGHTMAX;
                brightness = (a[i].n.ob[1] - (-4096 - WAVEHEIGHTMAX * 2)) / 32;
                a[i].v.cn[0] = 0xBf + brightness;
                a[i].v.cn[1] = 0xBf + brightness;
                a[i].v.cn[2] = 0xBf + brightness;
            }
            o->oCollisionDistance = 15000.f;
        }
    }
    load_object_collision_model();
}
#define SCENE CUTSCENE_SSL_PYRAMID_EXPLODE
u8 gateOpen = 0;
void medusagate(void) {
    switch (o->oAction) {
        case 0:
            if (gCurrActNum > 4) {
                gateOpen = 1;
            }
            if (!o->oTimer) {
                if (gateOpen) {
                    obj_mark_for_deletion(o);
                    return;
                }
            }
            o->oAction = gateOpen;
            break;
        case 1:
            if (set_mario_npc_dialog(2) == 2 && cutscene_object(SCENE, o) == 1) {
                o->oAction = 2;
                play_sound(SOUND_GENERAL_WATER_LEVEL_TRIG, gDefaultSoundArgs);
            }
            break;
        case 2:
            if (o->oTimer < 100) {
                o->oPosY += 3.f;
            } else {
                gObjCutsceneDone = TRUE;
                if (cutscene_object(SCENE, o) == -1) {
                    set_mario_npc_dialog(0);
                    o->oAction = 3;
                    mark_obj_for_deletion(o);
                }
            }
            break;
    }
    load_object_collision_model();
}
u8 warioText[6] = { 91, 91, 91, 94, 95, 96 };
void bacchus(void) {
    switch (o->oAction) {
        case 0:
            // wario mario close
            if (o->oDistanceToMario < 400.f) {
                o->oAction++;
            }
            break;
        case 1:
            // talk to mario
            if (talkToMarioNoRotation(warioText[gCurrActNum - 1])) {
                o->oAction++;
                if ((gCurrActNum < 5)) {
                    gateOpen = 1;
                }
            }
            break;
        case 2:
            // wait mario far
            if (o->oDistanceToMario > 700.f) {
                o->oAction = 0;
            }
            break;
    }
}
void thotcode(void) {
}

void zeusCodeBoss(void) {
    struct Object *spawned;
    struct Object *damageyosh;
    f32 targetpos = gMarioState->pos[2] - 6000.f;
    if (targetpos < -10000.f - o->oHealth * 2000.f) {
        targetpos = -10000.f - o->oHealth * 2000.f;
    }
    o->oDrawingDistance = 65000.f;
    if (o->oHealth == 2048) {
        o->oHealth = 0;
        cur_obj_scale(9.f);
    }
    o->header.gfx.scale[0] =
        approach_f32_symmetric(o->header.gfx.scale[0], 9.5f - o->oHealth * 1.5f, 0.1f);
    o->header.gfx.scale[1] = o->header.gfx.scale[0];
    o->header.gfx.scale[2] = o->header.gfx.scale[0];
    switch (o->oAction) {
        case 0:
            // talk to mario
            cur_obj_init_animation(1);
            if (talkToMario(97)) {
                o->oAction++;
                sequence_player_unlower(SEQ_PLAYER_LEVEL, 60);
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
            }
            break;
        case 1:
            // fly into position
            o->oPosZ = approach_f32_asymptotic(o->oPosZ, targetpos, 0.005f);
            if (o->oTimer > 40) {
                o->oAction++;
            }
            break;
        case 2:
            // shoot thunderbolts in a straight line
            o->oPosY = approach_f32_asymptotic(
                o->oPosY, gMarioState->pos[1] + 20.f + sins(o->oTimer * 0x270) * 150.f, 0.02f);
            cur_obj_init_animation(2);
            if (o->header.gfx.unk38.animFrame > 179) {
                o->header.gfx.unk38.animFrame -= 160;
                o->oOpacity = 0;
            }
#define XOFF 70.f
#define YOFF -8.f
#define ZOFF 40.f

            o->oPosX = approach_f32_asymptotic(o->oPosX, gMarioState->pos[0], 0.02f);
            if (!((o->header.gfx.unk38.animFrame < 60) || (o->header.gfx.unk38.animFrame > 140))) {
                if (o->oPosX < gMarioState->pos[0] + ZOFF * o->header.gfx.scale[0]) {
                    o->oVelX += 1.f + o->oHealth * 2.f;
                }
            } else {
                // gMarioState->pos[0] - ZOFF * o->header.gfx.scale[0]
                if (o->oPosX > gMarioState->pos[0] - ZOFF * o->header.gfx.scale[0]) {
                    o->oVelX -= 1.f + o->oHealth * 2.f;
                }
            }
            o->oVelX = approach_f32_asymptotic(o->oVelX, 0, 0.01f);
            o->oPosX += o->oVelX;
            if (o->header.gfx.unk38.animFrame > 60) {
                if (!(o->oOpacity & 1)) {
                    spawned = spawn_object_relative(
                        0, XOFF * o->header.gfx.scale[0], YOFF * o->header.gfx.scale[0],
                        ZOFF * o->header.gfx.scale[0], o, 0x42, bhvZeusLightning);
                    spawned->oBehParams2ndByte = o->oHealth;
                }
                o->oOpacity |= 1;
            }
            if (o->header.gfx.unk38.animFrame > 140) {
                if (!(o->oOpacity & 2)) {
                    spawned = spawn_object_relative(
                        0, -XOFF * o->header.gfx.scale[0], YOFF * o->header.gfx.scale[0],
                        ZOFF * o->header.gfx.scale[0], o, 0x42, bhvZeusLightning);
                    spawned->oBehParams2ndByte = o->oHealth;
                }
                o->oOpacity |= 2;
            }

            o->header.gfx.unk38.animFrame += o->oHealth;
            o->oPosZ = approach_f32_asymptotic(o->oPosZ, targetpos, 0.02f);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x100);
            o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0, 0x100);
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
                    o->oAction++;
                    o->oMoveAngleYaw = o->oAngleToMario;
                    o->oForwardVel = -70.f;
                    o->oHealth++;
                    o->oInteractStatus = 0;
                }
            }

            if (damageyosh = cur_obj_nearest_object_with_behavior(bhvYoshiRiding)) {
                if (damageyosh->oPosZ < (o->oPosZ + 50.f * o->header.gfx.scale[0])) {
                    if (damageyosh->oPosX < (o->oPosX + 50.f * o->header.gfx.scale[0])) {
                        o->oAction = 3;
                        o->oHealth++;
                        o->oAngleVelPitch = (random_u16() % 0x1000) - 0x800;
                        o->oAngleVelYaw = (random_u16() % 0x1000) - 0x800;
                        o->oMoveAngleYaw = o->oAngleToMario;
                        o->oForwardVel = -50.f;
                        onYoshi = 0;
                        gMarioState->action = ACT_SPECIAL_TRIPLE_JUMP;
                        gMarioState->vel[1] = 120.f;
                        gMarioState->forwardVel = -200.f;
                        gMarioState->faceAngle[1] =
                            -atan2s(-13000.f + gMarioState->pos[2], gMarioState->pos[0]);
                        create_sound_spawner(SOUND_OBJ_KING_WHOMP_DEATH);
                        spawn_mist_particles_variable(0, 0, 200.0f);
                        spawn_triangle_break_particles(20, 138, 3.0f, 4);
                        cur_obj_shake_screen(SHAKE_POS_SMALL);
                    }
                }
            }
            break;
        case 3:
            // get hit
            gMarioState->faceAngle[1] = -atan2s(-13000.f + gMarioState->pos[2], gMarioState->pos[0]);
            if (gMarioState->vel[1] < 0) {
                gMarioState->vel[1] = 0.f;
            }
            gMarioState->pos[0] = approach_f32_asymptotic(gMarioState->pos[0], 0, 0.015f);
            gMarioState->pos[0] = approach_f32_symmetric(gMarioState->pos[0], 0, 20.f);
            gMarioState->pos[2] = approach_f32_asymptotic(gMarioState->pos[2], 14000.f, 0.015f);
            gMarioState->pos[2] = approach_f32_symmetric(gMarioState->pos[2], 14000.f, 20.f);
            o->oMoveAngleYaw += o->oAngleVelYaw;
            o->oFaceAnglePitch += o->oAngleVelPitch;
            o->oAngleVelYaw = approach_s16_symmetric(o->oAngleVelYaw, 0, 0x10);
            o->oAngleVelPitch = approach_s16_symmetric(o->oAngleVelPitch, 0, 0x10);
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0.f, 0.5f);
            if (o->oTimer > 155) {
                o->oAction = 2;
                gMarioState->forwardVel = 0.f;
                if (o->oHealth == 3) {
                    stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                    play_music(SEQ_PLAYER_LEVEL, 0, 0);
                    mark_obj_for_deletion(o);
                    spawn_default_star(0, 400, 12250.f);
                    spawn_mist_particles_variable(0, 0, 200.0f);
                    spawn_triangle_break_particles(20, 138, 3.0f, 4);
                    cur_obj_shake_screen(SHAKE_POS_SMALL);
                }
            }
            cur_obj_compute_vel_xz();
            cur_obj_move_using_vel();
            break;
        case 4:
            // talk before giving a star
            if (talkToMario(103)) {
                o->oAction++;
            }
            break;
        case 5:
            // give star
            mark_obj_for_deletion();
            break;
    }
}

void zeusLighting(void) {
    o->header.gfx.unk38.animFrame++;
    cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);
    if (!o->oTimer) {
        o->oAngleVelPitch = (random_u16() & 0x1fff) - 0x1000;
        o->oAngleVelYaw = (random_u16() & 0x1fff) - 0x1000;
    }
    o->oFaceAngleYaw += o->oAngleVelYaw;
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oPosZ += 80.f;
    if (o->oPosZ > 32000.f) {
        mark_obj_for_deletion(o);
    }
}
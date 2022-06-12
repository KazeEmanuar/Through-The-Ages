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
#include "engine/surface_collision.h"
extern void move_obj_with_physics(u8 clampFloor);
extern s16 rotateTowardsMario(int speed);
#define m gMarioState
#define o gCurrentObject

extern const struct Animation *const staryu_anims[];
extern const struct Animation *const haunter_anims[];
extern const struct Animation *const onix_anims[];
extern const struct Animation *const primeape_anims[];
extern const struct Animation *const articuno_anims[];
extern const struct Animation *const magnemite_anims[];
extern const struct Animation *const gyarados_anims[];
extern const struct Animation *const hypno_anims[];
extern const struct Animation *const golem_anims[];
struct Animation *anims[] = {
    staryu_anims,    NULL,           NULL,        haunter_anims,
    onix_anims,      primeape_anims, golem_anims, articuno_anims,
    magnemite_anims, gyarados_anims, hypno_anims,
};
extern u8 talkToMario(int dialogID);
extern struct ObjectNode *gObjectLists;
extern f32 cur_obj_dist_to_home(void);
extern int spawnID;
// uses wallhitboxradius set by behav cmd
#define MODEL_YELLOW_COIN 0x74           // yellow_coin_geo
#define MODEL_YELLOW_COIN_NO_SHADOW 0x75 // yellow_coin_no_shadow_geo
u8 canUseTangela = 1;
void pokemoncode(void) {
    struct Surface *ceiling;
    float x, y, z;
    x = o->oPosX;
    y = o->oPosY;
    z = o->oPosZ;
    o->oAnimations = anims[o->oBehParams2ndByte];
    if (!o->oAction) {
        o->oForwardVel -= 2.0f;
    }
    if (o->oBehParams2ndByte != 9) {
        move_obj_with_physics(1);
    }
    switch (o->oBehParams2ndByte) {
        case 0:
            switch (o->oAction) {
                case 0:
                    if (o->oTimer > 3) {
                        o->oFaceAnglePitch -= 0x400;
                        if (o->oTimer > 18) {
                            o->oAction++;
                        }
                    }
                    break;
                case 1:
                    if (!o->oTimer) {
                        o->oPosY -= 25.f;
                        o->oHiddenBlueCoinSwitch = spawn_object(o, 0xff, bhvFountain);
                        o->oHiddenBlueCoinSwitch->header.gfx.scale[2] = 0.05f;
                        o->oHiddenBlueCoinSwitch->header.gfx.scale[0] = 0.5f;
                        o->oHiddenBlueCoinSwitch->header.gfx.scale[1] = 0.5f;
                        o->oHiddenBlueCoinSwitch->oPosY += 20.f;
                    } else if (o->oTimer < 8) {
                        o->oHiddenBlueCoinSwitch->header.gfx.scale[2] += 0.125f;
                    }
                    cur_obj_init_animation(0);
                    if (o->oTimer > 25) {
                        obj_mark_for_deletion(o);
                        obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                        spawn_mist_particles();
                    }
                    if (lateral_dist_between_objects(gMarioObject, o) < 300.f) {
                        if (gMarioObject->oPosY > o->oPosY) {
                            gMarioState->vel[1] += (1500.f - (o->oPosY - gMarioObject->oPosY)) / 200.f;
                            if (gMarioState->vel[1] > 35.f) {
                                gMarioState->vel[1] = 35.f;
                            }
                        }
                    }
                    break;
            }
            break;
        case 1:
            if (m->action & (ACT_FLAG_WATER_OR_TEXT | ACT_FLAG_METAL_WATER | ACT_FLAG_INTANGIBLE)) {
                obj_mark_for_deletion(o);
                return;
            }
            switch (o->oAction) {
                case 0:
                    if (o->oTimer > 18) {
                        o->oAction++;
                        o->oHomeX = o->oPosX;
                        o->oHomeY = o->oPosY;
                        o->oHomeZ = o->oPosZ;
                    }
                    break;
                case 1:
                    if (lateral_dist_between_objects(gMarioObject, o) < 300.f) {
                        if ((gMarioObject->oPosY > o->oPosY)
                            && (gMarioObject->oPosY < o->oPosY + 500.f)) {
                            o->oAction++;
                        }
                    }
                    // wait for mario
                    break;
                case 2:
                    if (cur_obj_dist_to_home() > 1500.f) {
                        o->oAction++;
                    } else if (o->oPosY - 700.f > o->oHomeY) {
                        o->oAction++;
                    }
                    o->oVelX +=
                        gMarioState->controller->stickMag * sins(gMarioState->intendedYaw) * 0.01f;
                    o->oVelZ +=
                        gMarioState->controller->stickMag * coss(gMarioState->intendedYaw) * 0.01f;
                    if (gMarioState->controller->buttonDown & A_BUTTON) {
                        o->oVelY += 1.0f;
                    }
                    if (gMarioState->controller->buttonDown & B_BUTTON) {
                        o->oVelY -= 1.0f;
                    }
                    o->oVelX *= 0.98f;
                    o->oVelY *= 0.9f;
                    o->oVelZ *= 0.98f;
                    o->oMoveAngleYaw = atan2s(o->oVelZ, o->oVelX);
                    goto mariopos;
                    break;
                case 3:
                    if (o->oTimer < 20) {
                        o->header.gfx.scale[0] -= 0.05;
                        o->header.gfx.scale[1] = o->header.gfx.scale[0];
                        o->header.gfx.scale[2] = o->header.gfx.scale[0];
                        // spwan puff
                        spawn_object(o, MODEL_SMOKE, bhvBobombFuseSmoke);
                    } else {
                        obj_mark_for_deletion(o);
                        spawn_mist_particles();
                    }
                mariopos:
                    cur_obj_move_using_vel();
                    gMarioState->action = ACT_BUTT_SLIDE_AIR;
                    gMarioState->vel[0] = 0;
                    gMarioState->vel[1] = 0;
                    gMarioState->vel[2] = 0;
                    gMarioState->forwardVel = 0;
                    gMarioState->pos[0] = o->oPosX;
                    gMarioState->pos[1] = o->oPosY + 50.f;
                    gMarioState->pos[2] = o->oPosZ;
                    gMarioState->faceAngle[1] = o->oMoveAngleYaw;

                    if (gMarioState->controller->buttonPressed & (Z_TRIG | L_TRIG)) {
                        gMarioState->action = ACT_DIVE;
                        gMarioState->vel[1] = 35.f;
                        gMarioState->forwardVel = 15.f;
                        obj_mark_for_deletion(o);
                        spawn_mist_particles();
                    }
                    break;
            }
            break;
        case 2:
#define tangeloffset 50.f
            if ((o->oTimer == 0) && (o->oAction == 0)) {
                if (!canUseTangela) {
                    obj_mark_for_deletion(o);
                    return;
                }
                canUseTangela = 0;
            }
            gMarioState->pos[0] = o->oPosX;
            gMarioState->pos[1] = o->oPosY;
            gMarioState->pos[2] = o->oPosZ;
            gMarioState->vel[1] = 0;
            gMarioState->forwardVel = 0;
            if (o->oAction == 1) {
#define poggers 1
                if (o->oTimer == poggers) {
                    o->oHiddenBlueCoinSwitch = spawn_object(o, 0xfd, bhvTangelaattack);
                    o->oHiddenBlueCoinSwitch->oPosY += 50.f;
                    o->oHiddenBlueCoinSwitch->oPosX += sins(o->oMoveAngleYaw + 0x4000) * tangeloffset;
                    o->oHiddenBlueCoinSwitch->oPosZ += coss(o->oMoveAngleYaw + 0x4000) * tangeloffset;
                    o->oBooParentBigBoo = spawn_object(o, 0xfd, bhvTangelaattack);
                    o->oBooParentBigBoo->oPosY += 50.f;
                    o->oBooParentBigBoo->oPosX += sins(o->oMoveAngleYaw + 0xC000) * tangeloffset;
                    o->oBooParentBigBoo->oPosZ += coss(o->oMoveAngleYaw + 0xC000) * tangeloffset;
                    o->oBooParentBigBoo->header.gfx.scale[2] = 0.05f;
                    o->oForwardVel = 0.0f;
                }
                if (o->oTimer > poggers) {
#define growth 106.f
                    f32 x, z, y;
                    x = o->oPosX
                        + (sins(o->oMoveAngleYaw) * growth
                           * o->oHiddenBlueCoinSwitch->header.gfx.scale[2]);
                    z = o->oPosZ
                        + (coss(o->oMoveAngleYaw) * growth
                           * o->oHiddenBlueCoinSwitch->header.gfx.scale[2]);
                    y = o->oPosY;
                    if (o->oPosY < find_floor_height(x, o->oPosY + 200.f, z)) {
                        o->oAction++;
                        o->oHomeX = (x - o->oPosX) / (o->oTimer - poggers);
                        o->oHomeZ = (z - o->oPosZ) / (o->oTimer - poggers);
                        o->oBooParentBigBoo->oTimer = 34;
                        o->oHiddenBlueCoinSwitch->oTimer = 34;
                        o->oOpacity = o->oTimer - poggers;
                    }
                    if (f32_find_wall_collision(&x, &y, &z, 20.f, 80.f)) {
                        o->oAction++;
                        o->oHomeX = (x - o->oPosX) / (o->oTimer - poggers);
                        o->oHomeZ = (z - o->oPosZ) / (o->oTimer - poggers);
                        o->oBooParentBigBoo->oTimer = 34;
                        o->oHiddenBlueCoinSwitch->oTimer = 34;
                        o->oOpacity = o->oTimer - poggers;
                    }
                    if ((o->oPosY + 200.f) > find_ceil(x, o->oPosY, z, &ceiling)) {
                        o->oAction++;
                        o->oHomeX = (x - o->oPosX) / (o->oTimer - poggers);
                        o->oHomeZ = (z - o->oPosZ) / (o->oTimer - poggers);
                        o->oBooParentBigBoo->oTimer = 34;
                        o->oHiddenBlueCoinSwitch->oTimer = 34;
                        o->oOpacity = o->oTimer - poggers;
                    }
                }
                if (o->oTimer == 65) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                }
            } else if (!o->oAction) {
                if (!o->oTimer) {
                    // o->oVelY = -25.f;
                }
                o->oForwardVel = 2.0f;
                // o->oVelY -= 4.0f;
                if (o->oTimer > 5) {
                    o->oAction++;
                }
            } else {
                o->oFaceAnglePitch = 0x1000;
                o->oPosX += o->oHomeX;
                o->oPosZ += o->oHomeZ;
                o->oBooParentBigBoo->oPosX += o->oHomeX;
                o->oBooParentBigBoo->oPosZ += o->oHomeZ;
                o->oHiddenBlueCoinSwitch->oPosX += o->oHomeX;
                o->oHiddenBlueCoinSwitch->oPosZ += o->oHomeZ;
                gMarioState->forwardVel = 48.f;
                if (o->oOpacity == o->oTimer) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                }
            }
            break;
        case 3:
            if (o->oAction) {
                gMarioState->flags |= MARIO_VANISH_CAP;
                rotateTowardsMario(0x600);
                cur_obj_init_animation(0);
                if (o->header.gfx.unk38.animFrame == 43) {
                    o->header.gfx.unk38.animFrame = 20;
                }
                if ((o->oTimer > 40) && !(gMarioState->controller->buttonDown & L_TRIG)) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                    gMarioState->flags &= ~MARIO_VANISH_CAP;
                }
            } else {
                if (o->oTimer > 18) {
                    o->oAction++;
                }
            }
            break;
        case 4:
            // floor him, dont have him run of ledges
            o->oVelY -= 4.0f;
            if (!(o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
                if ((o->oPosY - find_floor_height(o->oPosX, o->oPosY + 200.f, o->oPosZ)) < 50.f) {
                    // stick to floor
                    o->oPosY = find_floor_height(o->oPosX, o->oPosY + 200.f, o->oPosZ);
                } else {
                    o->oPosX = x;
                    o->oPosZ = z;
                }
            }
            if (o->oAction) {
                o->oGraphYOffset *= 0.9f;
                o->oPosX = x;
                o->oPosZ = z;
                if (o->header.gfx.unk38.animFrame > 87) {
                    o->header.gfx.unk38.animFrame = 21;
                }
                if ((gMarioState->controller->buttonDown & L_TRIG)) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                    obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                }
            } else {
                cur_obj_init_animation(0);
                cur_obj_scale(((2 + o->oTimer) / 2.0f) * .1);
                o->oGraphYOffset = 25.f * (20 - o->oTimer) * o->header.gfx.scale[0] + 50.f;
                if (o->oTimer > 18) {
                    o->oAction++;
                    o->oGraphYOffset = 0;
                    o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvOnixColl);
                }
            }
            break;
        case 5:
            o->oVelY -= 4.0f;
            o->hitboxRadius = 80.0f;
            o->hitboxHeight = 80.0f;
            o->oInteractType = INTERACT_IGLOO_BARRIER;
            o->oInteractStatus = 0;
            o->oIntangibleTimer = 0;
            if (o->oAction) {
                rotateTowardsMario(0x800);
                if (o->header.gfx.unk38.animFrame > 91) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                }
                if (o->header.gfx.unk38.animFrame == 49) {
                    if (o->oDistanceToMario < 500.f) {
                        m->faceAngle[1] = obj_angle_to_object(gMarioObject, o);
                        cur_obj_play_sound_2(SOUND_OBJ_HEAVEHO_TOSSED);
                        gMarioObject->oInteractStatus |= INT_STATUS_MARIO_UNK2;
                        gMarioStates->forwardVel = 45.0f;
                        gMarioStates->vel[1] = 95.0f;
                        set_mario_action(m, ACT_THROWN_FORWARD, 1);
                    }
                }
            } else {
                o->oGraphYOffset = 50.f;
                cur_obj_init_animation(0);
                o->oForwardVel -= 2.0f;
                if (o->oTimer > 8) {
                    o->oAction++;
                }
            }
            break;
        case 6:
            o->oVelY -= 4.0f;
            o->hitboxRadius = 80.0f;
            o->hitboxHeight = 80.0f;
            o->oInteractType = INTERACT_IGLOO_BARRIER;
            o->oInteractStatus = 0;
            o->oIntangibleTimer = 0;
            if (o->oAction) {
                if (o->oTimer > 70) {
                    cur_obj_scale(0.7 + (f32) (o->oTimer - 70) / 8.0);
                }
                if (o->oTimer > 75) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                    o->oHiddenBlueCoinSwitch = spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
                    o->oHiddenBlueCoinSwitch->oGraphYOffset += 100.0f;
                }
            } else {
                //  o->oGraphYOffset = 50.f;
                cur_obj_init_animation(0);
                cur_obj_scale(0.7);
                if (o->oTimer > 18) {
                    o->oAction++;
                }
            }
            break;

        case 7:
            if (o->oAction) {
                if ((gMarioState->controller->buttonDown & L_TRIG)) {
                    obj_mark_for_deletion(o);
                    if (o->oHiddenBlueCoinSwitch) {
                        obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                    }
                    spawn_mist_particles();
                }
                if (o->oTimer == 52) {
                    o->oHiddenBlueCoinSwitch = spawn_object(o, 0xfe, bhvIcebeam);
                    o->oHiddenBlueCoinSwitch->oPosY += 125.f;
                    o->oHiddenBlueCoinSwitch->header.gfx.scale[1] = 0.05f;
                }
            } else {
                cur_obj_init_animation(0);
                if (!o->oTimer) {
                    o->oVelY = -25.f;
                }
                o->oVelY -= 4.0f;
                if (o->oTimer > 18) {
                    o->oAction++;
                }
            }
            break;
        case 8:
            if (!o->oAction) {
                cur_obj_init_animation(0);
                if (o->oTimer > 18) {
                    o->oAction++;
                }
            } else {
                rotateTowardsMario(0x600);
                o->oPosX += (gMarioState->pos[0] - o->oPosX) * 0.05f;
                o->oPosY += (gMarioState->pos[1] + 200.f - o->oPosY) * 0.05f;
                o->oPosZ += (gMarioState->pos[2] - o->oPosZ) * 0.05f;
                if (gMarioState->controller->buttonPressed & L_TRIG) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                } else {
                    struct Object *obj;
                    struct ObjectNode *listHead;
                    u8 magnetized = 0;
#define maxdist 2000.f
#define mindist 50.f

                    listHead =
                        &gObjectLists[get_object_list_from_behavior(segmented_to_virtual(bhvOneCoin))];
                    obj = (struct Object *) listHead->next;

                    while (obj != (struct Object *) listHead) {
                        if ((obj->header.gfx.sharedChild
                             == gLoadedGraphNodes[MODEL_YELLOW_COIN_NO_SHADOW])
                            || (obj->header.gfx.sharedChild == gLoadedGraphNodes[MODEL_YELLOW_COIN])
                            || (obj->header.gfx.sharedChild == gLoadedGraphNodes[MODEL_RED_COIN])) {
                            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj != o) {
                                f32 objDist = dist_between_objects(o, obj);
                                f32 multiplicator =
                                    (1 - (objDist / maxdist)) * (1 - (objDist / maxdist));
                                if (objDist < maxdist) {

                                    obj->oPosX += ((o->oPosX - obj->oPosX) * multiplicator) / 3.f;
                                    obj->oPosY += ((o->oPosY - obj->oPosY) * multiplicator) / 3.f;
                                    obj->oPosZ += ((o->oPosZ - obj->oPosZ) * multiplicator) / 3.f;
                                    magnetized = 1;
                                }
                                if (objDist < mindist) {
                                    interact_coin(gMarioState, 0, obj);
                                }
                            }
                        }
                        obj = (struct Object *) obj->header.next;
                    }

                    if ((o->header.gfx.unk38.animID == 1)) {
                        if ((o->header.gfx.unk38.animFrame > 22)) {
                            cur_obj_init_animation(magnetized);
                        }
                    } else {
                        cur_obj_init_animation(magnetized);
                    }
                    if (magnetized) {
                        if (o->header.gfx.unk38.animFrame > 17) {
                            o->header.gfx.unk38.animFrame = 5;
                        }
                    }
                }
            }
            break;
        case 9:
            if (o->oAction == 1) {
                if (o->oTimer < 16) {
                    o->oGraphYOffset -= 15.f;
                }
                cur_obj_init_animation(0);
                if (o->oTimer > 59) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                }
            } else if (o->oAction == 2) {
                cur_obj_init_animation(1);
                if (!o->oHiddenBlueCoinSwitch) {
                    o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvGyaradosColl);
                    o->oHiddenBlueCoinSwitch->oFaceAnglePitch = 0;
                    o->oHiddenBlueCoinSwitch->oFaceAngleRoll = 0;
                }
                obj_copy_pos_and_angle(o->oHiddenBlueCoinSwitch, o);
                o->oVelY += ((-2.0f * sins(o->oTimer * 1024) - 4.0f)
                             + (-o->oPosY + find_water_level(o->oPosX, o->oPosZ) + 40.f) / 10.f);
                if (o->oVelY < -78.0f) {
                    o->oVelY = -78.0f;
                }
                o->oVelY *= 0.9f;
                // if mario stands on him, move in the direction mario is facing, converge speed to
                // cosine between angles, slowly rotate to angle.
                if ((gMarioObject->platform == o->oHiddenBlueCoinSwitch)
                    && (gMarioState->pos[1] > o->oPosY + 200.f)) {
                    o->oGoombaTargetYaw = gMarioState->faceAngle[1];
                    o->oTTCCogTargetVel =
                        coss((o->oMoveAngleYaw - gMarioState->faceAngle[1]) & 0xffff) * 30.f;
                    if (o->oTTCCogTargetVel < 0) {
                        o->oTTCCogTargetVel = 0;
                    }
                } else {
                    o->oGoombaTargetYaw = o->oMoveAngleYaw;
                    o->oTTCCogTargetVel = 0.0f;
                }
                o->oPokeyTargetYaw = o->oMoveAngleYaw;
                o->oForwardVel = approach_f32_symmetric(o->oForwardVel, o->oTTCCogTargetVel, 0.5f);

                if (abs_angle_diff(o->oGoombaTargetYaw, o->oMoveAngleYaw) > 0xc00) {
                    o->oMoveAngleYaw =
                        approach_s16_symmetric(o->oMoveAngleYaw, o->oGoombaTargetYaw, 0x100);
                }

                if ((gMarioState->controller->buttonDown & L_TRIG)) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                    obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                }
            } else {
                if (o->oTimer > 18) {
                    o->oAction++;
                    if ((find_floor_height(o->oPosX, o->oPosY + 200.f, o->oPosZ) + 200.f)
                        < find_water_level(o->oPosX, o->oPosZ)) {
                        o->oAction = 2;
                    } else {
                        o->oAction = 1;
                    }
                }
            }
            move_obj_with_physics(0);
            if (o->oAction == 2) {
                if ((find_floor_height(o->oPosX, o->oPosY + 20.f, o->oPosZ) + 200.f)
                    > find_water_level(o->oPosX, o->oPosZ)) {
                    o->oPosX = x;
                    o->oPosZ = z;
                }
            }
            if ((gMarioObject->platform == o->oHiddenBlueCoinSwitch)
                && (gMarioState->pos[1] > o->oPosY + 200.f)) {
                o->oHomeX = o->oPosX + sins(o->oMoveAngleYaw) * 120.f;
                o->oHomeZ = o->oPosZ + coss(o->oMoveAngleYaw) * 120.f;
                gMarioState->pos[0] = approach_f32_symmetric(gMarioState->pos[0], o->oHomeX, 15.0f);
                gMarioState->pos[2] = approach_f32_symmetric(gMarioState->pos[2], o->oHomeZ, 15.0f);
            }
            if (o->oHiddenBlueCoinSwitch) {
                o->oHiddenBlueCoinSwitch->oVelX = o->oPosX - x;
                o->oHiddenBlueCoinSwitch->oVelY = o->oPosY - y;
                o->oHiddenBlueCoinSwitch->oVelZ = o->oPosZ - z;
                o->oHiddenBlueCoinSwitch->oAngleVelYaw = o->oMoveAngleYaw - o->oPokeyTargetYaw;
            }
            break;
        case 10:
            o->oGraphYOffset = -50.f;
            if (o->oAction) {
                if ((o->oSubAction == 1) && (m->action != ACT_SLEEPING)) {
                    obj_mark_for_deletion(o);
                    spawn_mist_particles();
                }
                if (o->header.gfx.unk38.animFrame == 86) {
                    o->header.gfx.unk38.animFrame = 51;
                }
                if (abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw) < 0xc00) {
                    if (mario_ready_to_speak()) {
                        o->oSubAction = 1;
                        m->action = ACT_SLEEPING;
                        m->healCounter += (!(o->oTimer & 0x000f));
                    }
                }
                rotateTowardsMario(0x600);
            } else {
                cur_obj_init_animation(0);
                if (o->oTimer > 18) {
                    o->oAction++;
                }
            }
            break;
    }
}

void fountaincode(void) {
    o->oFaceAngleRoll += 0xcf5;
    if (o->oTimer > 18) {
        o->header.gfx.scale[2] -= 0.125f;
    }
}

void icebeamcode(void) {
    o->oFaceAngleYaw += 0x2cf5;
    if (o->oTimer < 18) {
        o->header.gfx.scale[1] += 0.25f;
    }
}

void tangelaattackcode(void) {
    if (o->oTimer < 18) {
        o->header.gfx.scale[2] += 0.75f;
    }

    if ((o->oTimer > 30) && o->oTimer < 48) {
        o->header.gfx.scale[2] -= 0.75f;
    }
    if (o->oTimer == 49) {
        obj_mark_for_deletion(o);
    }
};

struct Object *findNextTree(int iD) {
    struct ObjectNode *listHead;
    struct Object *obj;
    listHead = &gObjectLists[OBJ_LIST_POLELIKE];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == segmented_to_virtual(bhvTree)) {
            if ((obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) && (obj != o)) {
                if ((obj->oBehParams & 0xff) == iD) {
                    return obj;
                }
            }
        }
        obj = (struct Object *) obj->header.next;
    }
};

void roamingpokemoncode(void) {
    struct Object *target;
    float x, y, z;
    x = o->oPosX;
    y = o->oPosY;
    z = o->oPosZ;
    o->oAnimations = anims[o->oBehParams2ndByte];
    if (o->oBehParams2ndByte != 9) {
        move_obj_with_physics(1);
    }
    if (o->oAction == 69) {
        if (talkToMario(159 + o->oBehParams2ndByte)) {
            obj_mark_for_deletion(o);
            spawnID = o->oBehParams2ndByte;
        }
    } else {
        switch (o->oBehParams2ndByte) {
            case 0:
                break;
            case 1:
                o->oOpacity++;
                o->oPosY += (-2.0f * sins(o->oOpacity * 1024));
                switch (o->oAction) {
                    case 0:
                        if (o->oDistanceToMario < 1000.f) {
                            rotateTowardsMario(0x00c0);
                        }
                        if (o->oDistanceToMario < 100.f) {
                            cur_obj_set_model(0);
                            o->oAction = 69;
                            spawn_mist_particles();
                        }
                        break;
                }
                break;
            case 2:
                o->oGraphYOffset = 30.f;
                switch (o->oAction) {
                    case 0:
                        // wait mario close then jump in tree
                        switch (o->oSubAction) {
                            case 0:
                                if (o->oDistanceToMario < 4000.f) {
                                    rotateTowardsMario(0x0640);
                                }
                                if (o->oDistanceToMario < 1000.f) {
                                    target = findNextTree(o->oArrowLiftUnk100);
                                    o->oMoveAngleYaw = obj_angle_to_object(o, target);
                                    o->oForwardVel = lateral_dist_between_objects(o, target) / 10.f;
                                    o->oVelY = 40.f;
                                    o->oSubAction = 1;
                                    o->oTimer = 0;
                                }
                                break;
                            case 1:
                                o->oVelY -= 4.0f;
                                if (o->oTimer == 9) {
                                    o->oAction = 1;
                                }
                                break;
                        }
                        break;
                    case 1:
                        // vine whip to next tree if mario gets too close
                        switch (o->oSubAction) {
                            case 0:
                                o->oForwardVel = 0;
                                o->oVelY = 0;
                                if (o->oDistanceToMario < 1000.f) {
                                    o->oArrowLiftUnk100++;
                                    target = findNextTree(o->oArrowLiftUnk100);
                                    o->oMoveAngleYaw = obj_angle_to_object(o, target);
                                    o->oSubAction = 1;
                                    o->oTimer = 0;
                                }
                                break;
                            case 1:
#define poggers 1
                                if (o->oTimer == poggers) {
                                    o->oHiddenBlueCoinSwitch = spawn_object(o, 0xfd, bhvTangelaattack);
                                    o->oHiddenBlueCoinSwitch->oPosY += 50.f;
                                    o->oHiddenBlueCoinSwitch->oPosX +=
                                        sins(o->oMoveAngleYaw + 0x4000) * tangeloffset;
                                    o->oHiddenBlueCoinSwitch->oPosZ +=
                                        coss(o->oMoveAngleYaw + 0x4000) * tangeloffset;
                                    o->oBooParentBigBoo = spawn_object(o, 0xfd, bhvTangelaattack);
                                    o->oBooParentBigBoo->oPosY += 50.f;
                                    o->oBooParentBigBoo->oPosX +=
                                        sins(o->oMoveAngleYaw + 0xC000) * tangeloffset;
                                    o->oBooParentBigBoo->oPosZ +=
                                        coss(o->oMoveAngleYaw + 0xC000) * tangeloffset;
                                    o->oBooParentBigBoo->header.gfx.scale[2] = 0.05f;
                                    o->oForwardVel = 0.0f;
                                }
                                if (o->oTimer > 16) {
#define growth 80.f
                                    target = findNextTree(o->oArrowLiftUnk100);
                                    o->oForwardVel = lateral_dist_between_objects(o, target) / 12.f;
                                    o->oBooParentBigBoo->oTimer = 34;
                                    o->oHiddenBlueCoinSwitch->oTimer = 34;
                                    o->oOpacity = o->oTimer - poggers;
                                    o->oHiddenBlueCoinSwitch->oPosX +=
                                        o->oForwardVel * sins(o->oMoveAngleYaw);
                                    o->oHiddenBlueCoinSwitch->oPosZ +=
                                        o->oForwardVel * coss(o->oMoveAngleYaw);
                                    o->oBooParentBigBoo->oPosX +=
                                        o->oForwardVel * sins(o->oMoveAngleYaw);
                                    o->oBooParentBigBoo->oPosZ +=
                                        o->oForwardVel * coss(o->oMoveAngleYaw);
                                }
                                if (o->oTimer == 31) {
                                    obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                                    obj_mark_for_deletion(o->oBooParentBigBoo);
                                    o->oSubAction = 2;
                                    o->oTimer = 0;
                                }
                                break;
                            case 2:
                                if (o->oTimer == 14) {
                                    o->oSubAction = 0;
                                    if (o->oArrowLiftUnk100 == 3) {
                                        o->oAction = 2;
                                        o->oForwardVel = 20.f;
                                        o->oVelY = 20.f;
                                    }
                                }
                                break;
                        }
                        break;
                    case 2:
                        // jump out of tree
                        o->oVelY -= 4.f;
                        if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
                            o->oAction++;
                            o->oForwardVel = 0.f;
                        }
                        break;
                    case 3:
                        // get caught
                        rotateTowardsMario(0x0640);
                        if (o->oDistanceToMario < 100.f) {
                            cur_obj_set_model(0);
                            o->oAction = 69;
                            spawn_mist_particles();
                        }
                        break;
                }
                break;
            case 3:
                break;
            case 4:
                switch (o->oAction) {
                    case 0:
                        cur_obj_init_animation(0);
                        cur_obj_scale(((2 + o->oTimer) / 2.0f) * .1);
                        o->oGraphYOffset = 25.f * (20 - o->oTimer) * o->header.gfx.scale[0] + 50.f;
                        if (o->oTimer > 18) {
                            o->oAction++;
                            o->oGraphYOffset = 0;
                            o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvOnixColl);
                        }
                        break;
                    case 1:
                        o->oGraphYOffset *= 0.9f;
                        o->oPosX = x;
                        o->oPosZ = z;
                        if (o->header.gfx.unk38.animFrame > 87) {
                            o->header.gfx.unk38.animFrame = 21;
                        }
                        // if (cur_obj_is_mario_ground_pounding_platform()){

                        if ((gMarioObject->platform == o->oHiddenBlueCoinSwitch)
                            && (gMarioStates[0].action == ACT_GROUND_POUND_LAND)) {
                            cur_obj_set_model(0);
                            o->oAction = 69;
                            spawn_mist_particles();
                            obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                        }
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                }
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
        }
    }
}
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
// make shroom use colors 83 83 83 or ff ff ff depending on random
Gfx shroomColors[] = {
    gsDPSetPrimColor(0, 0, 130, 130, 255, 255), gsSPEndDisplayList(),
    gsDPSetPrimColor(0, 0, 130, 255, 255, 255), gsSPEndDisplayList(),
    gsDPSetPrimColor(0, 0, 255, 130, 255, 255), gsSPEndDisplayList(),
    gsDPSetPrimColor(0, 0, 255, 255, 130, 255), gsSPEndDisplayList(),
    gsDPSetPrimColor(0, 0, 255, 130, 130, 255), gsSPEndDisplayList(),
    gsDPSetPrimColor(0, 0, 130, 255, 130, 255), gsSPEndDisplayList(),
};

Gfx *geo_set_prim(s32 callContext, struct GraphNode *b, Mat4 *mtx) {
    Gfx *gfx = NULL;
    struct Object *obj = (struct Object *) gCurGraphNodeObject;
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) b;
    if (callContext == GEO_CONTEXT_RENDER) {
        gfx = &shroomColors[obj->oBehParams2ndByte * 2];
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (1 << 8);
    }
    return gfx;
}

Gfx *set_prim_to_opacity(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    Gfx *dlStart;
    Gfx *DL;
    struct Object *obj;
    struct GraphNodeSwitchCase *switchCase;
    struct GraphNodeGenerated *currentGraphNode = (struct GraphNodeGenerated *) node;
    dlStart = alloc_display_list(sizeof(Gfx) * 3);
    DL = dlStart;
    if (callContext == GEO_CONTEXT_RENDER) {
        obj = (struct Object *) gCurGraphNodeObject; // TODO: change global type to Object pointer

        gDPSetPrimColor(DL++, 0, 0, obj->oOpacity, obj->oOpacity, obj->oOpacity, obj->oOpacity);
        gSPEndDisplayList(DL);
            currentGraphNode->fnNode.node.flags =
                (currentGraphNode->fnNode.node.flags & 0xFF) | (LAYER_TRANSPARENT << 8);
        return dlStart;
    }

    return NULL;
}



void bounceshroom(void) {
    if (cur_obj_is_mario_on_platform()) {
        m->action = ACT_TRIPLE_JUMP;
        m->vel[1] = 80.f + (o->oBehParams & 0xFF);
        o->oForwardVel = .08f;
        cur_obj_play_sound_1(SOUND_OBJ_SNOWMAN_BOUNCE);
        m->marioObj->header.gfx.unk38.animFrame = 0;
        o->oTimer = 0;
    }
    cur_obj_scale(o->header.gfx.scale[0] + o->oForwardVel);
    o->oForwardVel = approach_f32_symmetric(o->oForwardVel, (1.f - o->header.gfx.scale[0]), 0.01f);
    o->oForwardVel *= 0.96f;
    if ((m->action == ACT_TRIPLE_JUMP) && (o->oTimer < 45)) {
        m->faceAngle[1] = approach_s16_symmetric(m->faceAngle[1], m->intendedYaw, 0x200);
        m->peakHeight = -100000.f;
    } else {
        load_object_collision_model();
    }
}
struct Object *cur_obj_find_nearest_object_with_bParam4andBehav(const BehaviorScript *behavior,
                                                                u32 Bparam4) {
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct Object *closestObj = NULL;
    struct Object *obj;
    struct ObjectNode *listHead;
    f32 minDist = 600000.f;

    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr) {
            if ((obj->oBehParams & 0xff) == Bparam4) {
                if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj != o) {
                    f32 objDist = dist_between_objects(o, obj);
                    if (objDist < minDist) {
                        closestObj = obj;
                        minDist = objDist;
                    }
                }
            }
        }
        obj = (struct Object *) obj->header.next;
    }

    return closestObj;
}
u32 checkMonkFloor() {
    struct Surface *floor;
#define monkedist o->oForwardVel * 10.f
    f32 floorHeight = find_floor(o->oPosX + sins(o->oMoveAngleYaw) * monkedist, o->oPosY + 50.f,
                                 o->oPosZ + coss(o->oMoveAngleYaw) * monkedist, &floor);
    if (absf(floorHeight - o->oPosY) > 100.f) {
        return 1;
    } else {
        return 0;
    }
}
u8 bunnyThere = 0;
#define waypoint o->oOpacity
void latebunny(void) {
    s16 targetAngle;
    struct Object *shroom;
    if (o->oBehParams & 0xFF) {
        return;
    }
    switch (o->oAction) {
        case 0:
            bunnyThere = 0;
            // wait to talk to mario
            o->oForwardVel = 0.f;
            o->oGraphYOffset = -50.f;
            o->oInteractStatus = 0;
            o->oIntangibleTimer = 0;
            if ((gMarioState->pos[1] > (o->oPosY - 200.f))
                && (gMarioState->pos[1] == gMarioState->floorHeight)) {
                o->oAction++;
                o->oOpacity = 1;
            }
            break;
        case 1:
            cur_obj_init_animation(0);
            o->oForwardVel = 0.f;
            if (talkToMario(139)) {
                o->oAction++;
                o->oHiddenBlueCoinSwitch =
                    cur_obj_find_nearest_object_with_bParam4andBehav(bhvLateBunny, waypoint);
            }
            break;
        case 2:
            // move towards next bunnyspot
            cur_obj_init_animation(1);
            targetAngle = obj_angle_to_object(o, o->oHiddenBlueCoinSwitch);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x600);
            if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
                o->oSubAction = 0;
            }
            shroom = cur_obj_nearest_object_with_behavior(bhvBounceShroom);
            if (o->oSubAction == 0) {
                if (checkMonkFloor()) {
                    o->oVelY = 40.f;
                    o->oSubAction = 1;
                    cur_obj_play_sound_1(SOUND_OBJ_MIPS_RABBIT);
                    // animate
                }
            } else if ((lateral_dist_between_objects(shroom, o) < 770.f)
                       && (absf(shroom->oPosY - o->oPosY) < 500.f)) {
                o->oVelY = 50.f;
                o->oSubAction = 1;
                cur_obj_play_sound_1(SOUND_OBJ_SNOWMAN_BOUNCE);
            }
            if (o->oSubAction) {
                cur_obj_extend_animation_if_at_end();
            }
            o->oForwardVel = approach_f32_symmetric(
                o->oForwardVel, 30.f * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f), 2.f);
            // if theres a floor in front, jump
            // if a mushroom is close, jump
            if (waypoint < 4) {
                if (dist_between_objects(o->oHiddenBlueCoinSwitch, o) < 200.f) {
                    waypoint++;
                    if (o->oHiddenBlueCoinSwitch->oBehParams & 0xFF000000) {
                        o->oAction = 3;
                    } else {
                        o->oHiddenBlueCoinSwitch =
                            cur_obj_find_nearest_object_with_bParam4andBehav(bhvLateBunny, waypoint);
                    }
                }
            } else {
                if (dist_between_objects(o->oHiddenBlueCoinSwitch, o) < 200.f) {
                    bunnyThere = 1;
                    obj_mark_for_deletion(o);
                }
            }
            break;
        case 3:
            cur_obj_init_animation(0);
            o->oForwardVel = 0.f;
            if (!o->oSubAction) {
                if (o->oDistanceToMario < 500.f) {
                    o->oSubAction = 1;
                }
            } else {
                if (talkToMario(140 + waypoint / 3)) {
                    o->oAction = 2;
                    o->oHiddenBlueCoinSwitch =
                        cur_obj_find_nearest_object_with_bParam4andBehav(bhvLateBunny, waypoint);
                }
            }
            break;
        case 4:

            break;
    }
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);
}

void dinnerbunny(void) {
    o->oGraphYOffset = -50.f;
    o->oIntangibleTimer = 0;
    o->oInteractStatus = 0;
    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 200.f) {
                o->oAction = 1;
            }
            break;
        case 1:
            if (talkToMarioNoRotation(o->oBehParams2ndByte)) {
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->oDistanceToMario > 300.f) {
                o->oAction = 0;
            }
            break;
    }
}
void madhatcode(void) {
    o->oGraphYOffset = -75.f;
    o->oIntangibleTimer = 0;
    o->oInteractStatus = 0;
    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 200.f) {
                o->oAction = 1;
            }
            break;
        case 1:
            if (talkToMarioNoRotation(o->oBehParams2ndByte)) {
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->oDistanceToMario > 300.f) {
                o->oAction = 0;
            }
            break;
    }
}

void toad_statue(void) {
    o->header.gfx.unk38.animFrame = 0;
    if (!o->oTimer) {
        o->oFaceAngleYaw -= 0xF40;
    }
    if (o->oDistanceToMario < 500.f) {
        o->oOpacity = 126 - o->oDistanceToMario / 4.f;
        cur_obj_set_model(0xDD);
    } else {
        o->oOpacity = 0;
        cur_obj_set_model(0);
    }
    if (o->oBehParams & 0x01) {
        o->oIntangibleTimer = 0;
        o->hitboxRadius = 200.f;
        o->hitboxHeight = 400.f;
        o->oInteractType = 8;
        o->oInteractStatus = 0;
    }
}

extern const Trajectory wdw_area_2_spline_WingoPath[];
#define pointgoal o->oOpacity
void wingocode(void) {
    f32 dist;
    u16 targetAngle;
    u16 targetPitch;
    f32 x, y, z;
    f32 targetSpeed;
    u32 i;
    o->oGraphYOffset = -125.f;
    o->oIntangibleTimer = 0;
    o->oInteractStatus = 0;
    if (!(o->oBehParams & 0xff)) {
        cur_obj_init_animation(0);
        switch (o->oAction) {
            case 0:
                if (o->oDistanceToMario < 950.f) {
                    o->oAction = 1;
                }
                break;
            case 1:
                if (cur_obj_update_dialog_with_cutscene(3, 2, CUTSCENE_DIALOG, o->oBehParams2ndByte)) {
                    o->oAction = 2;
                }
                break;
            case 2:
                if (o->oDistanceToMario > 1050.f) {
                    o->oAction = 0;
                }
                break;
        }
    } else {
        switch (o->oAction) {
            case 0:
                // wait mario close
                cur_obj_init_animation(0);
                if (o->oDistanceToMario < 550.f) {
                    o->oAction = 1;
                }
                break;
            case 1:
                // talk to mario, silverware in hand
                if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, o->oBehParams2ndByte)) {
                    o->oAction = 2;
                }
                break;
            case 2:
                // fly away
                // stop midair if mario is too far away
                cur_obj_init_animation(1);
                if (lateral_dist_between_objects(o, gMarioState->marioObj) < 2000.f) {
                    o->oBobombBuddyPosXCopy =
                        ((s16 *) segmented_to_virtual(wdw_area_2_spline_WingoPath))[1 + pointgoal * 4];
                    o->oBobombBuddyPosYCopy =
                        ((s16 *) segmented_to_virtual(wdw_area_2_spline_WingoPath))[2 + pointgoal * 4];
                    o->oBobombBuddyPosZCopy =
                        ((s16 *) segmented_to_virtual(wdw_area_2_spline_WingoPath))[3 + pointgoal * 4];

                    dist = sqrtf(
                        (o->oBobombBuddyPosZCopy - o->oPosZ) * (o->oBobombBuddyPosZCopy - o->oPosZ)
                        + (o->oBobombBuddyPosXCopy - o->oPosX) * (o->oBobombBuddyPosXCopy - o->oPosX)
                        + (o->oBobombBuddyPosYCopy - o->oPosY) * (o->oBobombBuddyPosYCopy - o->oPosY));
                    if (pointgoal < 12) {
                        targetAngle = atan2s(o->oBobombBuddyPosZCopy - o->oPosZ,
                                             o->oBobombBuddyPosXCopy - o->oPosX);
                        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x600);
                        targetPitch = -atan2s(sqrtf((o->oBobombBuddyPosZCopy - o->oPosZ)
                                                        * (o->oBobombBuddyPosZCopy - o->oPosZ)
                                                    + (o->oBobombBuddyPosXCopy - o->oPosX)
                                                          * (o->oBobombBuddyPosXCopy - o->oPosX)),
                                              o->oBobombBuddyPosYCopy - o->oPosY);
                        if (o->oTimer > 50) {
                            o->oFaceAnglePitch =
                                approach_s16_symmetric(o->oFaceAnglePitch, targetPitch, 0x0100);
                        }

                        o->oForwardVel =
                            approach_f32(o->oForwardVel,
                                         10.f * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f)
                                             * (coss(targetPitch - o->oFaceAnglePitch) + 1.0f),
                                         2.f, 2.f);
                        if (dist < 250.f) {
                            pointgoal++;
                        }
                    } else {
                        o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0, 0x0100);
                        o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0, 2.f);
                        cur_obj_update_floor_height();
                        o->oVelY = approach_f32_symmetric(o->oVelY, -20.f, 2.f);
                        o->oPosY += o->oVelY;
                        if (o->oPosY < o->oFloorHeight) {
                            o->oPosY = o->oFloorHeight;
                            o->oVelY = 0;
                            o->oAction = 3;
                        }
                        return;
                    }
                } else {
                    o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0, 2.f);
                }
                o->oVelY = sins(-o->oFaceAnglePitch) * o->oForwardVel;
                o->oVelX = coss(-o->oFaceAnglePitch) * sins(o->oMoveAngleYaw) * o->oForwardVel;
                o->oVelZ = coss(-o->oFaceAnglePitch) * coss(o->oMoveAngleYaw) * o->oForwardVel;
                cur_obj_move_using_vel();
                break;
            case 3:
                // sit and wait
                if (o->oDistanceToMario < 550.f) {
                    o->oAction = 4;
                }
                break;
            case 4:
                if (cur_obj_check_if_near_animation_end()) {
                    cur_obj_init_animation(0);
                }
                if (cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG,
                                                        o->oBehParams2ndByte + 1)) {
                    o->oAction = 5;
                    spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 200.f,
                                       gMarioState->pos[2]);
                }
                break;
            case 5:
                // tells mario he wont giver silverware back, he needs it to build a nest, but the star
                // doesnt seem to important
                break;
        }
        o->oWallHitboxRadius = 200.f;
        cur_obj_resolve_wall_collisions();
    }
}
#define STOMPOFFSET 2.f
void alicethwomp(void) {
    o->oAnimState = (o->oBehParams2ndByte & 0x03) + ((o->oBehParams & 0xF1000000) >> 22);
    switch ((o->oBehParams2ndByte
             & 0x03)) { // actually changed to King, queen, J and ace types that have movements
        case 0:
            // diamonds, fall when you get close
            switch (o->oAction) {
                case 0:
                    // wait at homeY+1000
                    o->oPosY = approach_f32_symmetric(o->oPosY, o->oHomeY + 1000.f, 8.f);
                    o->oPosX = approach_f32_symmetric(o->oPosX, o->oHomeX, 0.5f);
                    o->oPosZ = approach_f32_symmetric(o->oPosZ, o->oHomeZ, 0.5f);
                    if (o->oTimer > (1000 / 8)) {
                        if (lateral_dist_between_objects(o, gMarioObject) < 800.f) {
                            if (gMarioState->pos[1] + 200.f > o->oHomeY) {
                                o->oAction = 1;
                            }
                        }
                    }
                    break;
                case 1:
                    // move down, do sound
                    o->oPosX = approach_f32_symmetric(o->oPosX, gMarioState->pos[0], 4.f);
                    o->oPosZ = approach_f32_symmetric(o->oPosZ, gMarioState->pos[2], 4.f);
                    o->oVelY -= 4.f;
                    cur_obj_update_floor_height();
                    if (o->oPosY < o->oFloorHeight + STOMPOFFSET) {
                        o->oPosY = o->oFloorHeight + STOMPOFFSET;
                        cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                        o->oVelY = 0;
                        o->oAction = 2;
                    }
                    break;
                case 2:
                    if (o->oTimer > 21) {
                        o->oAction = 0;
                    }
                    // wait downwards
                    break;
            }
            break;
        case 1:
            // hearts, jump up then at you
            switch (o->oAction) {
                case 0:
                    // wait at homeY
                    o->oMoveAngleYaw =
                        approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x0400);
                    if (o->oTimer > 51) {
                        if (lateral_dist_between_objects(gMarioObject, o) < 500.f) {
                            if (absf(o->oPosY - gMarioState->pos[1]) < 500.f) {
                                o->oAction = 2;
                                cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
                            }
                        }
                    }
                    break;
                case 1:
                    // move down, do sound
                    o->oForwardVel = 16.f;
                    o->oMoveAngleYaw =
                        approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x0400);
                    o->oVelY -= 4.f;
                    cur_obj_update_floor_height();
                    if (o->oPosY < o->oFloorHeight + STOMPOFFSET) {
                        o->oPosY = o->oFloorHeight + STOMPOFFSET;
                        cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                        o->oVelY = 0;
                        o->oAction = 0;
                        o->oForwardVel = 0;
                    }
                    break;
                case 2:
                    // jump up and down to mario
                    o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 16.f, 2.f);
                    o->oMoveAngleYaw =
                        approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x800);
                    o->oPosY += 8.f;
                    if (o->oTimer > 21) {
                        o->oAction = 1;
                    }
                    break;
            }
            break;
        case 2:
            // clubs, patrol and jump at mario
            switch (o->oAction) {
                case 0:
                    // turn around and jump
                    if (o->oTimer >= 31 + (random_u16() & 0x3F)) {
                        o->oAction = 1;
                        o->oVelY = 50.f;
                        o->oForwardVel = 30.f;
                        o->oMoveAngleYaw -= 0x8000;
                    }
                    break;
                case 1:
                    // in jump
                    o->oVelY -= 4.f;
                    cur_obj_update_floor_height();
                    if (o->oPosY < o->oFloorHeight + STOMPOFFSET) {
                        o->oPosY = o->oFloorHeight + STOMPOFFSET;
                        cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                        o->oVelY = 0;
                        o->oAction = 0;
                        o->oForwardVel = 0;
                    }
                    break;
            }
            break;
        case 3:
            // spades, push mario
            switch (o->oAction) {
                case 0:
                    // turn around and jump
                    if (o->oTimer >= 31 + (random_u16() & 0x3F)) {
                        o->oAction = 1;
                        o->oVelY = 10.f;
                        o->oForwardVel = 30.f;
                        o->oMoveAngleYaw -= 0x8000;
                    }
                    break;
                case 1:
                    // in jump
                    o->oVelY = approach_f32_symmetric(o->oVelY, 0.f - (o->oTimer > 40), 1.f);
                    cur_obj_update_floor_height();
                    if (o->oPosY < o->oFloorHeight + STOMPOFFSET) {
                        o->oPosY = o->oFloorHeight + STOMPOFFSET;
                        cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                        o->oVelY = 0;
                        o->oAction = 0;
                        o->oForwardVel = 0;
                    }
                    break;
            }
            break;
    }
    cur_obj_resolve_wall_collisions();
    cur_obj_compute_vel_xz();
    cur_obj_move_using_vel();
}

struct Object *find_Queen(u32 bParam) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvAliceThwomp);
    struct Object *obj;
    struct ObjectNode *listHead;
    f32 minDist = 0x20000;

    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
                if ((obj->oBehParams2ndByte) == bParam) {
                    if ((absf(o->oPosX - obj->oPosX) > 722.f)
                        || (absf(o->oPosZ - obj->oPosZ) > 722.f)) {
                        return obj;
                    }
                }
            }
        }
        obj = (struct Object *) obj->header.next;
    }
    return 0;
}
extern struct Object *spawn_star(struct Object *sp30, f32 sp34, f32 sp38, f32 sp3C);
void thwomptoad(void) {
    struct Object *sp1C;
    // if all thwomps are nearby, despawn and give star to its position
    if ((o->oHealth >= 77) && (o->oHealth <= 127)) {
        o->oHealth++;
        if (o->oHealth == 100) {
            sp1C = spawn_star(o, o->oPosX, o->oPosY + 200.f, o->oPosZ);
            sp1C->oBehParams = 0x01000000;
            obj_mark_for_deletion(o);
        }
    } else {
        if (!find_Queen(1)) {
            o->oHealth = 77;
            cur_obj_set_model(0);
            spawn_mist_particles();
        }
    }
}

extern s16 gCCMEnteredSlide;
#define DISTANCE 1250.f
#define HEIGHT 4075.f
void wiggleralice(void) {
    struct Object *currPart1, *currPart2;
    s16 partCount;
    s16 curAngle;
    f32 moveScale = 1.f;
    f32 curY = o->oPosY;
    f32 curX = o->oPosX;
    f32 curZ = o->oPosZ;
    f32 x, y, z;
    f32 x2, y2, z2;
    /*spawn_object_rel_with_rot(scoreButton, MODEL_MAIN_MENU_MARIO_SAVE_BUTTON, bhvMenuButton,
                                          711, 311, -100, 0, -0x8000, 0);*/
    o->oDrawingDistance = 500000.f;
    if (!o->oBehParams2ndByte) {
        if (gCurrAreaIndex != 5) {
            cur_obj_scale(0.6f);
        } else if (gCurrAreaIndex == 1) {
            cur_obj_scale(4.8f);
        } else {
            cur_obj_scale(0.15f);
        }
        o->oBehParams2ndByte = 1;
        currPart1 = o;
        for (partCount = 0; partCount < 4; partCount++) {
            curAngle = (random_u16() & 0x1FFF) - 0x1000;
            currPart2 =
                spawn_object_relative(0, -DISTANCE * currPart1->header.gfx.scale[0] * sins(curAngle), 0,
                                      -DISTANCE * currPart1->header.gfx.scale[0] * coss(curAngle),
                                      currPart1, 0x3D, bhvWigglerAlice);
            currPart2->oBehParams2ndByte = 2;
            currPart2->oHiddenBlueCoinSwitch = currPart1;
            currPart2->header.gfx.scale[0] = currPart2->oHiddenBlueCoinSwitch->header.gfx.scale[0];
            currPart2->header.gfx.scale[1] = currPart2->oHiddenBlueCoinSwitch->header.gfx.scale[1];
            currPart2->header.gfx.scale[2] = currPart2->oHiddenBlueCoinSwitch->header.gfx.scale[2];
            currPart2->oMarioPolePos = random_f32_around_zero(80.f) + 80.f;
            currPart1 = currPart2;
        }
        o->oGraphYOffset = o->header.gfx.scale[0] * HEIGHT;
    }
    if (o->oBehParams2ndByte == 2) {
        // rotate towards next segment. move closer if outside of some set in stone range.
        o->oMoveAngleYaw = obj_angle_to_object(o, o->oHiddenBlueCoinSwitch);
        moveScale =
            (DISTANCE * o->header.gfx.scale[0] - dist_between_objects(o, o->oHiddenBlueCoinSwitch))
            / (DISTANCE * o->header.gfx.scale[0]);
        o->oPosX = o->oPosX + (o->oPosX - o->oHiddenBlueCoinSwitch->oPosX) * moveScale;
        o->oPosZ = o->oPosZ + (o->oPosZ - o->oHiddenBlueCoinSwitch->oPosZ) * moveScale;
        o->oPosY = o->oHiddenBlueCoinSwitch->oPosY + 1000.f * o->header.gfx.scale[0];
        cur_obj_update_floor_and_walls();
        o->oPosY = approach_f32_asymptotic(curY, o->oFloorHeight, .1f);
        o->oAction = (o->oHiddenBlueCoinSwitch->oAction > 1) << 1;
        if (o->oAction) {
            cur_obj_init_animation(1);
            o->hitboxRadius = DISTANCE * o->header.gfx.scale[0] + 50.f;
            o->hitboxHeight = DISTANCE * o->header.gfx.scale[0] * 1.2f;
        } else {
            cur_obj_init_animation(0);
            o->oMarioPolePos +=
                (sqrtf((o->oPosX - curX) * (o->oPosX - curX) + (o->oPosZ - curZ) * (o->oPosZ - curZ)))
                / (18.f * o->header.gfx.scale[0]);
            if (o->oMarioPolePos < 0.f) {
                o->oMarioPolePos += 160.f;
            } else if (o->oMarioPolePos > 160.f) {
                o->oMarioPolePos -= 160.f;
            }
            o->header.gfx.unk38.animFrame = o->oMarioPolePos;
            o->hitboxRadius = DISTANCE * o->header.gfx.scale[0] + 50.f;
            o->hitboxHeight = HEIGHT * o->header.gfx.scale[0] * 1.2f;
        }
        o->oInteractType = INTERACT_IGLOO_BARRIER;
        o->oInteractStatus = 0;
        o->oIntangibleTimer = 0;
    } else {
        switch (o->oAction) {
            case 0:
                o->oForwardVel = 20.f * o->header.gfx.scale[0];
                o->oMoveAngleYaw += 0x0020;
                if (gCurrAreaIndex == 1) {
                    o->oMoveAngleYaw -= 0x0050;
                }
                if (gCurrAreaIndex == 5) {
                    if (gMarioState->pos[1] > 450.f) {
                        o->oAction = 1;
                        o->oForwardVel = 0;
                    }
                } else if (gCCMEnteredSlide == 2) {
                    o->oAction = 2;
                }
                break;
            case 1:
                if (talkToMarioNoRotation(2)) {
                    o->oAction = 2;
                    gCCMEnteredSlide = 2;
                }
                break;
            case 2:
                o->hitboxRadius = DISTANCE * .7f * o->header.gfx.scale[0] + 50.f;
                o->hitboxHeight = DISTANCE * o->header.gfx.scale[0] * 1.2f;
                o->oInteractType = INTERACT_IGLOO_BARRIER;
                o->oInteractStatus = 0;
                o->oIntangibleTimer = 0;
                o->oGraphYOffset =
                    o->header.gfx.scale[0] * HEIGHT * (50 - (min(50, o->oTimer) * .8f)) / 50.f;
                o->oForwardVel = 0;
                cur_obj_set_model(0x3E);
                if (gCurrAreaIndex != 5) {
                    // warp if get close to mouth
                    /*  if (!o->oHiddenBlueCoinSwitch) {
                          o->oHiddenBlueCoinSwitch = spawn_object_relative(
                              0, DISTANCE *.6f* o->header.gfx.scale[0] * sins(curAngle), 200.f,
                              DISTANCE  *.6f* o->header.gfx.scale[0] * coss(curAngle), o, MODEL_GOOMBA,
                              bhvWarp);
                              o->oHiddenBlueCoinSwitch->oBehParams2ndByte = 0x30010000;
                      }*/
                    x2 = o->oPosX + DISTANCE * .6f * o->header.gfx.scale[0] * sins(o->oMoveAngleYaw);
                    y2 = o->oPosY + 350.f;
                    z2 = o->oPosZ + DISTANCE * .6f * o->header.gfx.scale[0] * coss(o->oMoveAngleYaw);
                    x = gMarioState->pos[0] - x2;
                    y = gMarioState->pos[1] - y2;
                    z = gMarioState->pos[2] - z2;
                    if (sqrtf(x * x + y * y + z * z) < 500.f) {
                        level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                        play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x14, 0, 0, 0);
                        sSourceWarpNodeId = 0x1;
                    }
                }
                break;
        }
        o->oPosY += 100.f * o->header.gfx.scale[0];
        cur_obj_update_floor_and_walls();
        o->oPosY = approach_f32_asymptotic(curY, o->oFloorHeight, .1f);
        cur_obj_move_standard(78);
    }
}

void beestar(void) {
        if (!cur_obj_nearest_object_with_behavior(bhvStingby)) {
            spawn_default_star(o->oPosX, o->oPosY, o->oPosZ);
            mark_obj_for_deletion(o);
        }
}

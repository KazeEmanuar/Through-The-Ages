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

#define CLIP_Y (75.0f)
void initClip(Vec3f prev_pos, struct Object *this) {
    vec3f_copy(prev_pos, &this->oPosX);
}
extern void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos);
u32 clipObject(Vec3f prev_pos, struct Object *this) {
    Vec3f unit_dir, dir;
    f32 clip_mag;
    Vec3f hit_pos;
    f32 clip;
    struct Surface *hit_surface = NULL;
#define CLIP_LENGTH 24.f
    unit_dir[0] = this->oPosX - prev_pos[0];
    unit_dir[1] = this->oPosY - prev_pos[1];
    unit_dir[2] = this->oPosZ - prev_pos[2];
    clip_mag = vec3f_length(unit_dir);
    vec3f_normalize(unit_dir);

    if (clip_mag > 0.0f) {
        // Perform raycast
        dir[0] = unit_dir[0] * (clip_mag + CLIP_LENGTH);
        dir[1] = unit_dir[1] * (clip_mag + CLIP_LENGTH);
        dir[2] = unit_dir[2] * (clip_mag + CLIP_LENGTH);

        /*print_text_fmt_int(32, 192, "X %d", (s32) dir[0]);
        print_text_fmt_int(32, 178, "Y %d", (s32) dir[1]);
        print_text_fmt_int(32, 164, "Z %d", (s32) dir[2]);*/
        prev_pos[1] += CLIP_Y;
        find_surface_on_ray(prev_pos, dir, &hit_surface, hit_pos);
        // Clip if collision was found
        if (hit_surface != NULL) {
            if ((hit_surface)->normal.y < -WALLMAXNORMAL) {
                this->oPosX = hit_pos[0] - unit_dir[0] * CLIP_LENGTH;
                if ((hit_surface)->normal.y
                    < -0.2f) // Dirty hack to prevent Mario from getting stuck on super steep ceilings
                    this->oPosY = hit_pos[1] - unit_dir[1] * CLIP_LENGTH - CLIP_Y;
                this->oPosZ = hit_pos[2] - unit_dir[2] * CLIP_LENGTH;
            } else {
                hit_pos[0] = this->oPosX - (hit_surface)->vertex1[0];
                hit_pos[1] = this->oPosY - (hit_surface)->vertex1[1] + CLIP_Y;
                hit_pos[2] = this->oPosZ - (hit_surface)->vertex1[2];
                clip = (hit_pos[0] * (hit_surface)->normal.x + hit_pos[1] * (hit_surface)->normal.y
                        + hit_pos[2] * (hit_surface)->normal.z)
                       - CLIP_LENGTH;
                this->oPosX -= (hit_surface)->normal.x * clip;
                this->oPosY -= (hit_surface)->normal.y * clip;
                this->oPosZ -= (hit_surface)->normal.z * clip;
            }
        }
    }

    vec3f_copy(prev_pos, &this->oPosX);
    return hit_surface;
}

void namekfloaty(void) {

    o->oVelY += sins(o->oTimer * 0x100) * 0.1f;
    if (cur_obj_is_mario_on_platform()) {
        o->oVelY -= .5f;
    }
    if (cur_obj_is_mario_ground_pounding_platform()) {
        o->oVelY -= 1.5f;
    }
    o->oVelY += (o->oHomeY - o->oPosY) * 0.01f;
    cur_obj_move_using_vel();
    load_object_collision_model();
}

extern u8 mario_texture_mustache[];
extern u8 mario_texture_hair_sideburn[];
extern u8 mario_texture_eyes_front[];
extern u8 mario_texture_eyes_half_closed[];
extern u8 mario_texture_eyes_closed[];
extern u8 mario_texture_eyes_dead[];
extern Lights1 mario_brown2_lights_group;
extern u8 mario_texture_mustacheb[];
extern u8 mario_texture_hair_sideburnb[];
extern u8 mario_texture_eyes_frontb[];
extern u8 mario_texture_eyes_half_closedb[];
extern u8 mario_texture_eyes_closedb[];
extern u8 mario_texture_eyes_deadb[];
extern Lights1 mario_brown2_lights_groupb;

// have the above ones twice in RAM so you can reset them.
// make marios brows yellow and angry
extern Lights1 mario_brown2Saiyan_lights_groupb;
extern u8 mario_texture_mustachec[];
extern u8 mario_texture_hair_sideburnc[];
extern u8 mario_texture_eyes_frontc[];
extern u8 mario_texture_eyes_half_closedc[];
extern u8 mario_texture_eyes_closedc[];
// extern u8 mario_texture_eyes_deadc[];
void resetSuperSaiyan() {
    *((Lights1 *) segmented_to_virtual(&mario_brown2_lights_group)) =
        *((Lights1 *) segmented_to_virtual(&mario_brown2_lights_groupb));
    memcpy(segmented_to_virtual(mario_texture_hair_sideburn),
           segmented_to_virtual(mario_texture_hair_sideburnb), 0x800);
    memcpy(segmented_to_virtual(mario_texture_mustache), segmented_to_virtual(mario_texture_mustacheb),
           0x800);
    memcpy(segmented_to_virtual(mario_texture_eyes_front),
           segmented_to_virtual(mario_texture_eyes_frontb), 0x800);
    memcpy(segmented_to_virtual(mario_texture_eyes_closed),
           segmented_to_virtual(mario_texture_eyes_closedb), 0x800);
    memcpy(segmented_to_virtual(mario_texture_eyes_half_closed),
           segmented_to_virtual(mario_texture_eyes_half_closedb), 0x800);
}
void makeSuperSaiyan() {
    *((Lights1 *) segmented_to_virtual(&mario_brown2_lights_group)) =
        *((Lights1 *) segmented_to_virtual(&mario_brown2Saiyan_lights_groupb));
    memcpy(segmented_to_virtual(mario_texture_hair_sideburn),
           segmented_to_virtual(mario_texture_hair_sideburnc), 0x800);
    memcpy(segmented_to_virtual(mario_texture_mustache), segmented_to_virtual(mario_texture_mustachec),
           0x800);
    memcpy(segmented_to_virtual(mario_texture_eyes_front),
           segmented_to_virtual(mario_texture_eyes_frontc), 0x800);
    memcpy(segmented_to_virtual(mario_texture_eyes_closed),
           segmented_to_virtual(mario_texture_eyes_closedc), 0x800);
    memcpy(segmented_to_virtual(mario_texture_eyes_half_closed),
           segmented_to_virtual(mario_texture_eyes_half_closedc), 0x800);
    spawn_object(o, MODEL_BLUE_FLAME, bhvAnimatedTexture);
}

void namekelder(void) {
    switch (o->oAction) {
        case 0:
            // wario mario close
            if (o->oDistanceToMario < 250.f) {
                o->oAction++;
            }
            break;
        case 1:
            // talk to mario
            if (talkToMario(o->oBehParams2ndByte)) {
                if (o->oBehParams & 0xFF) {
                    o->oAction = 3;
                } else {
                    o->oAction++;
                }
            }
            break;
        case 2:
            // wait mario far
            if (o->oDistanceToMario > 500.f) {
                o->oAction = 0;
            }
            break;
        case 3:
            gMarioState->action = ACT_WAITING_FOR_DIALOG;
            cur_obj_scale(o->header.gfx.scale[0] - 0.05f);
            if (o->header.gfx.scale[0] <= 0.05f) {
                makeSuperSaiyan();
                mark_obj_for_deletion(o);
                spawn_mist_particles();
                gMarioState->action = ACT_IDLE;
            }
            break;
    }
}

void bamekian(void) {
    rotateTowardsMario(0x400);
    if (mario_ready_to_speak() && (o->oInteractStatus == INT_STATUS_INTERACTED)) {
        o->oAction++;
    }
    if (o->oAction) {
        if (talkToMario(o->oBehParams2ndByte)) {
            o->oAction = 0;
        }
    }
}
u32 isInVision() {
    f32 pitchToMario;
    f32 x, y, z;
    x = gMarioState->pos[0] - o->oPosX;
    z = gMarioState->pos[2] - o->oPosZ;
    y = gMarioState->pos[1] - o->oPosY;
    pitchToMario = -atan2s(sqrtf(x * x + z * z), y);
    if (o->oDistanceToMario < 1500.f) {
        if (abs_angle_diff(o->oMoveAngleYaw, o->oAngleToMario) < 0x3400) {
            if (abs_angle_diff(o->oFaceAnglePitch, pitchToMario) < 0x1C00) {
                return 1;
            }
        }
    }
    return 0;
}
#define DASHSOUND SOUND_OBJ2_MRI_SPINNING
#define SHOTSOUND SOUND_OBJ_MRI_SHOOT
void waluigitroopa(void) {
    f32 dist;
    u16 targetAngle;
    struct Surface *floor;
    f32 floorheight;
    u16 randomAngle;
    f32 randomDist;
    f32 x, y, z;
    struct Object *attack;
    o->oDrawingDistance = 40000.f;
    switch (o->oAction) {
        case 0:
            if (o->oForwardVel < 0.2f) {
                cur_obj_init_animation(0);
                initClip(&o->oAngleVelPitch, o);
            } else {
                cur_obj_init_animation(1);
                o->header.gfx.unk38.animFrame += o->oForwardVel / 2.f;
            }
            o->oFaceAngleYaw = o->oMoveAngleYaw;
            // walk to random locations around home during action 0. if seeing mario, attack
            if (o->oOpacity) {
                o->oOpacity--;
            } else {
                o->oOpacity = random_u16() % 150 + 70;
                randomAngle = random_u16();
                randomDist = random_f32_around_zero(700.f);
                o->oBobombBuddyPosXCopy = sins(randomAngle) * randomDist + o->oHomeX;
                o->oBobombBuddyPosZCopy = coss(randomAngle) * randomDist + o->oHomeZ;
            }
            dist = sqrtf((o->oBobombBuddyPosZCopy - o->oPosZ) * (o->oBobombBuddyPosZCopy - o->oPosZ)
                         + (o->oBobombBuddyPosXCopy - o->oPosX) * (o->oBobombBuddyPosXCopy - o->oPosX));
            dist = (dist) / 1500.f;
            targetAngle =
                atan2s(o->oBobombBuddyPosZCopy - o->oPosZ, o->oBobombBuddyPosXCopy - o->oPosX);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x600);
#define TROOPASPEED 8.f
            o->oForwardVel = approach_f32_symmetric(
                o->oForwardVel, TROOPASPEED * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f) * dist,
                2.f);
            if (isInVision()) {
#define JUMPDIST (2000.f + gMarioState->forwardVel * 22.f)
                randomAngle = gMarioState->faceAngle[1] + (random_u16() % 0x4000) - 0x2000;
                o->oAction = 1;
                o->oVelY = 40.f;
                o->oBobombBuddyPosXCopy = sins(randomAngle) * JUMPDIST + gMarioState->pos[0];
                o->oBobombBuddyPosZCopy = coss(randomAngle) * JUMPDIST + gMarioState->pos[2];
                o->oBobombBuddyRole = 0;
                play_sound(DASHSOUND, gDefaultSoundArgs);
            }
            break;
        case 1:
            cur_obj_init_animation(2);
            o->oFaceAngleYaw = o->oAngleToMario;
            o->oVelY = approach_f32_symmetric(o->oVelY, 0, 2.f);
            o->oPosY = approach_f32_symmetric(o->oPosY, gMarioState->pos[1] + 325.f, 5.f);
            o->oForwardVel = 90.f + gMarioState->forwardVel + o->oTimer * 2;
            o->oMoveAngleYaw =
                atan2s(o->oBobombBuddyPosZCopy - o->oPosZ, o->oBobombBuddyPosXCopy - o->oPosX);
            x = o->oBobombBuddyPosXCopy - o->oPosX;
            z = o->oBobombBuddyPosZCopy - o->oPosZ;
            if ((sqrtf(x * x + z * z) < 200.f) || o->oTimer > 100) {
                o->oAction = 2;
                o->oForwardVel = 0;
                o->oVelY = 0;
            }
            if (o->oDistanceToMario > 3000.f) {
                o->oBobombBuddyPosXCopy =
                    sins(gMarioState->faceAngle[1]) * JUMPDIST + gMarioState->pos[0];
                o->oBobombBuddyPosZCopy =
                    coss(gMarioState->faceAngle[1]) * JUMPDIST + gMarioState->pos[2];
            }
            // attack pattern is flying close to mario and shooting beams at mario. make sure he stays
            // in sight
            break;
        case 2:
            o->oMoveAngleYaw = o->oAngleToMario;
            o->oFaceAngleYaw = o->oMoveAngleYaw;
            if (o->oTimer > 25) {
                o->oForwardVel = -3.f;
                cur_obj_init_animation(3);
            } else {
                cur_obj_init_animation(2);
            }
#define XOFF 50.f
#define YOFF 120.f
#define ZOFF 25.f

            if (o->header.gfx.unk38.animFrame == 46) {
                attack = spawn_object_relative(0, XOFF, YOFF, ZOFF, o, 0x39, bhvKiAttack);
                obj_scale(attack, 0.f);
                play_sound(SHOTSOUND, gDefaultSoundArgs);
                // attack->oGraphYOffset += 100.0f;
            }
            if (o->header.gfx.unk38.animFrame == 14) {
                attack = spawn_object_relative(0, -XOFF, YOFF, ZOFF, o, 0x39, bhvKiAttack);
                obj_scale(attack, 0.f);
                play_sound(SHOTSOUND, gDefaultSoundArgs);
                // attack->oGraphYOffset += 100.0f;
            }
            if (o->oTimer > 210) {
                o->oAction = 3;
                    o->oBobombBuddyRole++;
            }
            if (o->oTimer > 30) {
                if (o->oDistanceToMario > 3800.f) {
                    o->oAction = 3;
                    o->oBobombBuddyRole++;
                }
            }
            /*if (gMarioState->controller->buttonPressed & L_TRIG) {
                attack = spawn_object_relative(0, XOFF, YOFF, ZOFF, o, 0x39, bhvKiAttack);
                obj_scale(attack, 0.f);
            }*/
            // he flies backwards slowly while shooting beams
            // bolts are slightly chasing mario, chase speed is increased by distance to mario
            break;
        case 3:
            randomAngle = gMarioState->faceAngle[1] + (random_u16() % 0x4000) - 0x2000;
            o->oBobombBuddyPosXCopy = sins(randomAngle) * JUMPDIST + gMarioState->pos[0];
            o->oBobombBuddyPosZCopy = coss(randomAngle) * JUMPDIST + gMarioState->pos[2];
            o->oAction = 1;
            play_sound(DASHSOUND, gDefaultSoundArgs);
            if (o->oBobombBuddyRole > 3) {
                o->oAction = 0;
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
                vec3f_copy(&o->oAngleVelPitch, &o->oPosX);
                o->oForwardVel = 0;
                return;
            }
            // once he flew back a certain distance, he will reposition
            // if mario is too far away, he readjusts to be in front of mario(slightly angled away)
            break;
        case 4:
            cur_obj_init_animation(4);
            if (o->oTimer > 15) {
                spawn_mist_particles_variable(0, 0, 46.f);
                spawn_triangle_break_particles(30, 138, 3.0f, 4);
                mark_obj_for_deletion(o);
                spawn_object(o, MODEL_BLUE_COIN, bhvMrIBlueCoin);
            }
            // if you hit him during flight, he dies and drops a blue coin
            break;
        case 5:
            // disappear and drop blue coin
            break;
    }
    cur_obj_compute_vel_xz();
    cur_obj_move_using_vel();
    o->oIntangibleTimer = 0;
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            o->oAction = 4;
            o->oForwardVel = -40.f - gMarioState->forwardVel;
            o->oMoveAngleYaw = gMarioState->faceAngle[1] - 0x8000;
            o->oFaceAngleYaw = o->oMoveAngleYaw;
            cur_obj_play_sound_1(SOUND_OBJ_KOOPA_FLYGUY_DEATH);
        }
    }
    o->oInteractStatus = 0;

    floorheight = find_floor(o->oPosX, o->oPosY + 100.f, o->oPosZ, &floor);
    if (o->oPosY < floorheight) {
        o->oPosY = floorheight;
        o->oVelY = 0;
    }
    clipObject(&o->oAngleVelPitch, o);
    // resolve_and_return_wall_collisions(&o->oPosX, 0.f, 80.f);
}

void kiAttack(void) {
    f32 latDist;
    struct Object *explosion;
    o->header.gfx.unk38.animFrame++;
    cur_obj_play_sound_1(SOUND_AIR_AMP_BUZZ);
    o->hitboxRadius = o->header.gfx.scale[0] * 100.f;
    o->hitboxHeight = o->header.gfx.scale[0] * 180.f;
    o->hitboxDownOffset = o->header.gfx.scale[0] * 90.f;
    if (o->header.gfx.scale[0] < 0.45f) {
        obj_scale(o, o->header.gfx.scale[0] + 0.04f);
    }
    if (!o->oTimer) {
        initClip(&o->oBobombBuddyPosXCopy, o);
        o->oAngleVelPitch = (random_u16() & 0x1fff) - 0x1000;
        o->oAngleVelYaw = (random_u16() & 0x1fff) - 0x1000;
    }
    o->oFaceAngleYaw += o->oAngleVelYaw;
    o->oFaceAnglePitch += o->oAngleVelPitch;
#define INITSPEED 70.f
    if (o->oTimer == 15) {
        o->oForwardVel = INITSPEED;
        latDist = lateral_dist_between_objects(gMarioState->marioObj, o);
        o->oVelY = (gMarioState->pos[1] - o->oPosY) / (latDist / o->oForwardVel);
    }
    if ((m->interactObj == o) || clipObject(&o->oBobombBuddyPosXCopy, o)) {
        explosion = spawn_object(o, MODEL_EXPLOSION, bhvExplosion2);
        if ((m->interactObj == o)) {
            play_sound(SOUND_MARIO_OOOF2, gDefaultSoundArgs);
            m->hurtCounter += 8;
            if (m->health - m->hurtCounter * 0x40 < 0x100) {
                m->action = ACT_BACKWARD_AIR_KB;
            }
        }
        obj_mark_for_deletion(o);
        m->interactObj = 0;
    }
    if (o->oTimer > 200) {
        obj_mark_for_deletion(o);
    }
    /*print_text_fmt_int(100, 192, "X %d", (s32)o->oPosX);
    print_text_fmt_int(100, 178, "Y %d", (s32)o->oPosY);
    print_text_fmt_int(100, 164, "Z %d", (s32)o->oPosZ);*/
    cur_obj_compute_vel_xz();
    cur_obj_move_using_vel();
}
u32 noTroopas() {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvWaluigiTroopa);
    struct Object *obj;
    struct ObjectNode *listHead;
    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
                if (obj->oBehParams & 0xFF) {
                    return 0;
                }
            }
        }
        obj = (struct Object *) obj->header.next;
    }
    return 1;
}

void troopaattack(void) {
#define MUSICSTART 66
    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 4000.f) {
                if (o->oOpacity > MUSICSTART) {
                    o->oAction++;
                    sequence_player_unlower(SEQ_PLAYER_LEVEL, 60);
                    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
                } else {
                    o->oOpacity++;
                }
            }
            break;
        case 1:
            if (o->oDistanceToMario > 8000.f) {
                stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                o->oAction = 0;
            }
            break;
    }
    if (noTroopas()) {
        stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
        spawn_default_star(o->oHomeX, o->oHomeY + 300.f, o->oHomeZ);
        mark_obj_for_deletion(o);
    }
}
u8 radarActive = 0;
void bulma(void) {
    switch (o->oAction) {
        case 0:
            // wario mario close
            cur_obj_init_animation(0);
            rotateTowardsMario(0x600);
            if (gCurrActNum > 1) {
                if (o->oDistanceToMario < 320.f) {
                    o->oAction++;
                }
            }
            break;
        case 1:
            // talk to mario
            cur_obj_init_animation(1);
            if (o->header.gfx.unk38.animFrame > 88) {
                o->header.gfx.unk38.animFrame -= 57;
            }
            if (gCurrActNum < 3) {

                if (talkToMario(125)) {
                    o->oAction++;
                    spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 300.f,
                                       gMarioState->pos[2]);
                    radarActive = 1;
                }
            } else {
                if (talkToMario(127)) {
                    o->oAction = 3;
                }
            }
            break;
        case 2:
            // wait mario far
            rotateTowardsMario(0x600);
            break;
        case 3:
            // wait mario far
            if (o->oDistanceToMario > 500.f) {
                o->oAction = 0;
            }
            break;
    }
}
extern Gfx dragonradar_Circle_mesh[];
void render_radar() {
    Mtx *mtx;
    if ((gCurrActNum < 3) && !radarActive) {
        return;
    }
    if ((gCurrLevelNum != LEVEL_SL) || (gCurrAreaIndex != 1)) {
        return;
    }
    mtx = alloc_display_list(sizeof(Mtx));
    guTranslate(mtx, 38.f, 57.f, 0);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx++), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(gDisplayListHead++, &dragonradar_Circle_mesh);

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}
#define BALLRANGE 12000.f
#define BALLMIDX 38
#define BALLMIDY 57
#define BALLSCALE (30.f / BALLRANGE)
extern s16 newcam_yaw;
#define CAMYAW (newcam_yaw)
extern void print_text_fmt_int(s32 x, s32 y, const char *str, s32 n);
void render_ball() {
    f32 x, z;
    f32 RX, RZ;
    if ((gCurrActNum < 3) && !radarActive) {
        return;
    }
    if ((gCurrLevelNum != LEVEL_SL) || (gCurrAreaIndex != 1)) {
        return;
    }
    x = o->oPosX - gMarioState->pos[0];
    z = o->oPosZ - gMarioState->pos[2];
    RZ = sins(CAMYAW) * x + coss(CAMYAW) * z;
    RX = sins(CAMYAW + 0X4000) * x + coss(CAMYAW + 0X4000) * z;
    if (sqrtf(x * x + z * z) < BALLRANGE) {
        print_text_fmt_int((RX * BALLSCALE) + BALLMIDX - 7, (-RZ * BALLSCALE) + BALLMIDY - 7, "M", 0);
    }
}
u8 ballcount = 0;
extern void bhv_hidden_star_trigger_loop(void);
void dragonballcode() {
    render_ball();
    if (gCurrActNum == 3) {
        if (!o->oBehParams2ndByte) {
            if (obj_check_if_collided_with_object(o, gMarioObject)) {
                ballcount++;
                if (ballcount != 5) {
                    spawn_orange_number(ballcount, 0, 0, 0);
                }

                play_sound(SOUND_MENU_COLLECT_SECRET + (((u8) ballcount - 1) << 16), gDefaultSoundArgs);
                mark_obj_for_deletion(o);
            }
        }
    }
}
// ALSO SPAWN BALL IN THE MIDDLE
void dbzStar(void) {
    if (!o->oTimer) {
        ballcount = 0;
    }
    if (ballcount == 5) {
        spawn_default_star(o->oPosX, o->oPosY, o->oPosZ);
        mark_obj_for_deletion(o);
    }
}

u8 ballHeld = 0;
void dragonballpickup(void) {
    if (!o->oOpacity) {
        o->oOpacity = 1;
        // initClip(&o->oBobombBuddyPosXCopy, o);
    }
    switch (o->oHeldState) {
        case HELD_FREE:
            ballHeld = 0;
            // Apply standard physics
            // clipObject(&o->oBobombBuddyPosXCopy, o);
            object_step();
            break;

        case HELD_HELD:
            ballHeld = 1;
            // Disable rendering to hide the object while it's held
            cur_obj_disable_rendering();
            if (!o->oBobombBuddyRole) {
                o->oBobombBuddyRole = 1;
                level_set_transition(-1, NULL);
                create_dialog_box(130);
            }
            //    initClip(&o->oBobombBuddyPosXCopy, o);
            break;

        case HELD_THROWN:
            ballHeld = 0;
            cur_obj_enable_rendering();

            o->oHeldState = HELD_FREE;

            o->oForwardVel = 40.0;
            o->oVelY = 20.0;
            //    clipObject(&o->oBobombBuddyPosXCopy, o);
            break;

        case HELD_DROPPED:
            ballHeld = 0;
            // Re-enable rendering
            cur_obj_enable_rendering();

            cur_obj_get_dropped();

            o->oHeldState = HELD_FREE;

            o->oForwardVel = 0;
            o->oVelY = 0;
            //     clipObject(&o->oBobombBuddyPosXCopy, o);
            break;
    }
    o->oFaceAnglePitch += o->oForwardVel * 100 - o->oVelY * 100;
    o->oFaceAngleYaw = o->oMoveAngleYaw;
}

void dbzStar2(void) {
    if (!o->oTimer) {
        if (lateral_dist_between_objects(gMarioState->marioObj, o) < 2000.f) {
            if (ballHeld) {
                spawn_default_star(o->oPosX, o->oPosY + 300.f, o->oPosZ);
                mark_obj_for_deletion(o);
            }
        } else {
            ballHeld = 0;
        }
    }
}

void spawnDeathBeam(u8 time) {
    s16 targetPitch;
    struct Object *a;
    a = spawn_object_relative(0, -50.f, 40.f, 50.f, o, 0x44, bhvDeathBeam);
    a->oMoveAngleYaw = obj_angle_to_object(a, gMarioObject);
    a->oFaceAnglePitch =
        -atan2s(sqrtf((gMarioObject->oPosZ - a->oPosZ) * (gMarioObject->oPosZ - a->oPosZ)
                      + (gMarioObject->oPosX - a->oPosX) * (gMarioObject->oPosX - a->oPosX)),
                gMarioObject->oPosY - a->oPosY + 50.f);
    a->oBehParams = time;
    // cur_obj_play_sound_1(SOUND_OBJ_UNK23);
}

void walufreeza(void) {
    switch (o->oAction) {
        case 0:
            cur_obj_init_animation(0);
            if (talkToMario(131)) {
                o->oAction += 1;
                // spawn death beam
                spawnDeathBeam(50);
            }
            break;
        case 1:
            cur_obj_init_animation(1);
            if (o->oTimer < 12) {
                gMarioState->action = ACT_WAITING_FOR_DIALOG;
            } else {
                gMarioState->action = ACT_SHOCKED;
            }
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction++;
            }
            break;
        case 2:
            gMarioState->action = ACT_SHOCKED;
            cur_obj_init_animation(0);
            if (o->oTimer > 60) {
                level_trigger_warp(gMarioState, WARP_OP_DEATH);
                sSourceWarpNodeId = 0xF4;
            }
            break;
    }
}
// line intersection algorithm

f32 dist_sq(float px, float py, float pz, float lx1, float ly1, float lz1) {
    f32 x, y, z;
    x = px - lx1;
    y = py - ly1;
    z = pz - lz1;
    return (x * x + y * y + z * z);
}

f32 constrain(float f) {
    if (f < 0) {
        return 0;
    }
    if (f > 1) {
        return 1;
    }
    return f;
}
float dist_to_segment(float px, float py, float pz, float lx1, float ly1, float lz1, float lx2,
                      float ly2, float lz2) {
    float line_dist = dist_sq(lx1, ly1, lz1, lx2, ly2, lz2);
    float t;
    if (line_dist == 0) {
        return dist_sq(px, py, pz, lx1, ly1, lz1);
    }
    t = ((px - lx1) * (lx2 - lx1) + (py - ly1) * (ly2 - ly1) + (pz - lz1) * (lz2 - lz1)) / line_dist;
    t = constrain(t);
    return sqrtf(
        dist_sq(px, py, pz, lx1 + t * (lx2 - lx1), ly1 + t * (ly2 - ly1), lz1 + t * (lz2 - lz1)));
}

void deathbeam(void) {
    s16 timeleft;
    f32 x, y, z;
    f32 sp;
    // o->oIntangibleTimer = 0;
    o->oDrawingDistance = 100000.f;
    if (!(o->oTimer & 5)) {
        cur_obj_play_sound_2(SOUND_OBJ_ENEMY_DEFEAT_SHRINK);
    }
    switch (o->oAction) {
        case 0:
            // move and grow
            o->oForwardVel = 0.f;
            o->header.gfx.scale[2] += 3.f;
            timeleft = (o->oBehParams & 0xFFFF);
            if ((timeleft + 10) < o->oTimer) {
                o->oAction++;
            }
            break;
        case 1:
            // move
            o->oOpacity = 1;
            o->oForwardVel = 180.f;
            if (o->oTimer > (o->oBehParams & 0xFFFF)) {
                mark_obj_for_deletion(o);
            }
            break;
    }
    if (!o->oOpacity) {
        sp = 60.f * o->header.gfx.scale[2];
        y = sins(-o->oFaceAnglePitch) * sp;
        x = coss(-o->oFaceAnglePitch) * sins(o->oMoveAngleYaw) * sp;
        z = coss(-o->oFaceAnglePitch) * coss(o->oMoveAngleYaw) * sp;
        if (dist_to_segment(gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2], o->oHomeX,
                            o->oHomeY, o->oHomeZ, o->oPosX + x, o->oPosY + y, o->oPosZ + z)
            < 50.f) {
            gMarioState->action = ACT_SHOCKED;
            gMarioState->hurtCounter += 4;
            o->oOpacity = 1;
        }
    }
    o->oVelY = sins(-o->oFaceAnglePitch) * o->oForwardVel;
    o->oVelX = coss(-o->oFaceAnglePitch) * sins(o->oMoveAngleYaw) * o->oForwardVel;
    o->oVelZ = coss(-o->oFaceAnglePitch) * coss(o->oMoveAngleYaw) * o->oForwardVel;
    cur_obj_move_using_vel();
}

#include "math.h"
#define marioVecX o->oBobombBuddyPosXCopy
#define marioVecY o->oBobombBuddyPosYCopy
#define marioVecZ o->oBobombBuddyPosZCopy
#define INITYPOS o->oBowserDistToCentre
#define PLANETWIDTH (2352.f)
#define UMFANG (2.f * PLANETWIDTH * M_PI)
#include "engine/math_util.h"
// mario moves in xyz space along the normal from 0 to marioVec by rotate the normal 90 degrees on X and
// Z axis

// first test:
// rotate planet from (0,0,0) to -marioVec
// set mario pos to (0, marioy, 0)
// this should work close to (0,0,0)

#define moveVecX (mariovecCopy[0])
#define moveVecY (mariovecCopy[1])
#define moveVecZ (mariovecCopy[2])
void kaioplanet(void) {
    Vec3f mariovecCopy;
    f32 yposLoss;
    gMarioState->pos[0] = 0;
    gMarioState->controller->buttonDown |= (L_CBUTTONS | R_CBUTTONS);
    gCurrentArea->camera->nextYaw = 0x4000;
    newcam_yaw = 0x4000;
    yposLoss =
        -2.f * M_PI
        * sqrtf(gMarioState->pos[0] * gMarioState->pos[0] + gMarioState->pos[2] * gMarioState->pos[2])
        / PLANETWIDTH;
    if (!o->oOpacity) {
        o->oOpacity = 1;
        o->oBBallSpawnerSpawnOdds = gMarioState->pos[1];
        INITYPOS = gMarioState->pos[1];
        marioVecY = INITYPOS;
    }
    vec3f_copy(mariovecCopy, &marioVecX);
    vec3f_normalize(mariovecCopy);
    /*marioVecX += (-gMarioState->pos[0] * moveVecY + gMarioState->pos[0] * moveVecZ * sqrtf(1 -
    moveVecY)
                  - gMarioState->pos[2] * moveVecZ * moveVecY);

    marioVecZ += (-gMarioState->pos[2] * moveVecY + gMarioState->pos[2] * moveVecX * sqrtf(1 - moveVecY)
                  + gMarioState->pos[0] * moveVecX * moveVecY);

    marioVecX += (gMarioState->pos[1] - INITYPOS + yposLoss) * moveVecX;
    marioVecZ += (gMarioState->pos[1] - INITYPOS + yposLoss) * moveVecZ;
    marioVecY +=
        (-gMarioState->pos[0] * moveVecX + (gMarioState->pos[1] - INITYPOS + yposLoss) * moveVecY
         - gMarioState->pos[2] * moveVecZ);*/

    marioVecX -= (gMarioState->pos[0] * moveVecY + (gMarioState->pos[1] - INITYPOS) * moveVecX
                  + gMarioState->pos[0] * moveVecZ);

    marioVecY -= (-gMarioState->pos[0] * moveVecX + (gMarioState->pos[1] - INITYPOS) * moveVecY
                  - gMarioState->pos[2] * moveVecZ);

    marioVecZ -= (gMarioState->pos[2] * moveVecX + (gMarioState->pos[1] - INITYPOS) * moveVecZ
                  + gMarioState->pos[2] * moveVecY);

    vec3f_copy(mariovecCopy, &marioVecX);
    vec3f_normalize(mariovecCopy);
    /*print_text_fmt_int(8, 100, "mX %d", gMarioState->pos[0]);
    print_text_fmt_int(8, 86, "mz %d", gMarioState->pos[2]);*/

    gMarioState->pos[0] = 0;
    INITYPOS = gMarioState->pos[1];
    gMarioState->pos[2] = 0;
    // debug print marioveccopy to see if it loops around properly on both axis!!!
    /* print_text_fmt_int(8, 192, "X %d", mariovecCopy[0] * 100.f);
     print_text_fmt_int(8, 178, "Y %d", mariovecCopy[1] * 100.f);
     print_text_fmt_int(8, 164, "Z %d", mariovecCopy[2] * 100.f);

     print_text_fmt_int(8, 42, "PX %d", marioVecX);
     print_text_fmt_int(8, 28, "PY %d", marioVecY);
     print_text_fmt_int(8, 14, "PZ %d", marioVecZ);*/

    /*  vec3f_mult(mariovecCopy, o->oBBallSpawnerSpawnOdds);
      vec3f_copy(&marioVecX, mariovecCopy);*/

    o->oFaceAnglePitch = coss(o->oMoveAngleYaw - atan2s(mariovecCopy[2], mariovecCopy[0]))
                         * atan2s(mariovecCopy[1], sqrtf(mariovecCopy[0] * mariovecCopy[0]
                                                         + mariovecCopy[2] * mariovecCopy[2]));
    o->oFaceAngleRoll = sins(o->oMoveAngleYaw - atan2s(mariovecCopy[2], mariovecCopy[0]))
                        * atan2s(mariovecCopy[1], sqrtf(mariovecCopy[0] * mariovecCopy[0]
                                                        + mariovecCopy[2] * mariovecCopy[2]));
}
#include "levels/sl/header.h"
extern s16 newcam_yaw_target;
extern u8 newcam_centering;
extern u16 marioKI;
void smashfreeza(void) {
    gMarioState->controller->buttonDown |= (L_CBUTTONS | R_CBUTTONS);
    gCurrentArea->camera->nextYaw = 0x4000;
    newcam_yaw = 0x4000;
    newcam_distance_target = 2507;
    if (o->oAction) {
        gMarioState->health++;
        marioKI = 150;
    }
    switch (o->oAction) {
        case 0:
            cur_obj_init_animation(0);
            if ((o->oTimer > 70) && (gMarioState->action != ACT_WAITING_FOR_DIALOG)) {
                if (talkToMario(134)) {
                    o->oAction += 1;
                    o->oHealth = 8;
                    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
                }
            }
            break;
        case 1:
            // float up and down, space some randomish distance away from mario that keeps changing
            cur_obj_init_animation(0);
            o->oPosY = approach_f32_asymptotic(
                o->oPosY, gMarioState->pos[1] + 150.f + sins(o->oTimer * 0x400) * 50.f, 0.08f);
            if (o->oPosZ < gMarioState->pos[2]) {
                o->oPosZ = approach_f32_asymptotic(o->oPosZ,
                                                   gMarioState->pos[2] - 1500.f + o->oHealth * 125.f
                                                       + sins(o->oTimer * 0x500) * 20.f,
                                                   0.03f);
            } else {
                o->oPosZ = approach_f32_asymptotic(o->oPosZ,
                                                   gMarioState->pos[2] + 1500.f - o->oHealth * 125.f
                                                       + sins(o->oTimer * 0x500) * 20.f,
                                                   0.03f);
            }
            o->oPosX = approach_f32_asymptotic(o->oPosX, gMarioState->pos[0], 0.05f);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x800);
            if (o->oTimer > (random_u16() % (0x800 + o->oHealth * 0x100))) {
                o->oAction = 2;
            }
            break;
        case 2:
            // deathbeam
            cur_obj_init_animation(1);
            if (o->oTimer == 4) {
                spawnDeathBeam(5);
            }
            if (o->oTimer > 30) {
                o->oAction = 1;
            }
            break;
        case 3:
            // knockback
            if (!o->oTimer) {
                o->oForwardVel = -60.f;
                o->oAngleVelRoll = 0x700 + (random_u16() % 0x700);
                o->oAngleVelPitch = 0x1100 + (random_u16() % 0x1100);
                o->oHealth--;
            }
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0, 2.f);
            if (o->oForwardVel == 0.f) {
                o->oInteractStatus = 0;
                if (o->oHealth < 5) {
                    o->oAction = 4;
                } else {
                    o->oAction = 1;
                }
            }
            break;
        case 4:
            // transform
            switch (o->oSubAction) {
                case 0:
                    // talk
                    if (talkToMario(135)) {
                        o->oSubAction = 2;
                        cur_obj_set_model(0x45);
                        o->oAnimations = waluFreezF2_anims;
                        cur_obj_init_animation(0);
                        spawn_mist_particles();
                        spawn_triangle_break_particles(20, 138, 0.7f, 3);
                        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                        o->oDamageOrCoinValue = 3;
                    }
                    break;
                case 2:
                    // talkagain
                    if (talkToMario(136)) {
                        o->oAction = 5;
                        o->oHealth = 8;
                    }
                    break;
                default:
                    o->oSubAction = 0;
                    break;
            }
            break;
        case 5:
            // idle float
            cur_obj_init_animation(0);
            o->oPosY = approach_f32_asymptotic(
                o->oPosY, gMarioState->pos[1] + 75.f + sins(o->oTimer * 0x400) * 50.f, 0.02f);
            if (o->oPosZ < gMarioState->pos[2]) {
                o->oPosZ = approach_f32_asymptotic(
                    o->oPosZ, gMarioState->pos[2] - 1000.f + sins(o->oTimer * 0x500) * 500.f, 0.03f);
            } else {
                o->oPosZ = approach_f32_asymptotic(
                    o->oPosZ, gMarioState->pos[2] + 1000.f + sins(o->oTimer * 0x500) * 500.f, 0.03f);
            }
            o->oPosX = approach_f32_asymptotic(o->oPosX, gMarioState->pos[0], 0.05f);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x800);
            o->oSubAction++;
            if (o->oSubAction > 7) {
                if ((random_u16() % (70 - o->oSubAction + o->oHealth * 10)) == 0) {
                    spawn_mist_particles();
                    cur_obj_play_sound_2(SOUND_GENERAL_VANISH_SFX);
                    o->oPosZ = gMarioState->pos[2] - (o->oPosZ - gMarioState->pos[2]);
                    o->oMoveAngleYaw += 0x8000;
                    o->oSubAction = 0;
                    switch (random_u16() % 3) {
                        case 0:
                            o->oAction = 7;
                            break;
                        case 1:
                            o->oAction = 8;
                            break;
                        case 2:
                            o->oAction = 10;
                            break;
                    }
                }
                if ((random_u16() % (70 - o->oSubAction + o->oHealth * 10)) == 0) {
                    spawn_mist_particles();
                    cur_obj_play_sound_2(SOUND_GENERAL_VANISH_SFX);
                    o->oPosY = gMarioState->pos[1] + 500.f;
                    o->oSubAction = 0;
                }
            }
            // randomly warp behind mario
            if (o->oTimer > (random_u16() % (0x800 + o->oHealth * 0x100))) {
                switch (random_u16() % 3) {
                    case 0:
                        o->oAction = 7;
                        break;
                    case 1:
                        o->oAction = 8;
                        break;
                    case 2:
                        o->oAction = 10;
                        break;
                }
            }
            break;
        case 6:
            // punch (NOT IMPLEMENTED)
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 5;
            }
            break;
        case 7:
            // tailwhip (spaces back)
            o->oPosY = approach_f32_asymptotic(
                o->oPosY, gMarioState->pos[1] + 75.f + sins(o->oTimer * 0x400) * 50.f, 0.08f);
            if (o->oTimer < 20) {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x800);
            }
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, -10.f, 2.f);
            if (o->oTimer == 34) {
                o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvHitbox);
                o->oHiddenBlueCoinSwitch->hitboxRadius = 70;
                o->oHiddenBlueCoinSwitch->hitboxDownOffset = 75;
                o->oHiddenBlueCoinSwitch->oDamageOrCoinValue = 4;
                o->oHiddenBlueCoinSwitch->hitboxHeight = 150;
            }
            if (o->oHiddenBlueCoinSwitch) {
                obj_set_parent_relative_pos(o->oHiddenBlueCoinSwitch, 0, 0, 70.f);
                obj_build_relative_transform(o->oHiddenBlueCoinSwitch);
                o->oHiddenBlueCoinSwitch->oInteractType = 8;
            }
            if (o->oTimer == 38) {

                obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                o->oHiddenBlueCoinSwitch = 0;
            }
            if (o->oTimer > 22) {

                o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 40.f, 8.f);
            }
            if (o->oTimer > 32) {

                o->oForwardVel = approach_f32_symmetric(o->oForwardVel, -10.f, 16.f);
            }
            cur_obj_init_animation(1);
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 5;
            }
            break;
        case 8:
            // flying kick
            o->oPosY = approach_f32_asymptotic(
                o->oPosY, gMarioState->pos[1] + 75.f + sins(o->oTimer * 0x400) * 50.f, 0.08f);
            if (o->oTimer < 20) {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x800);
            }
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, -10.f, 2.f);
            if (o->oTimer > 20) {

                o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 40.f, 8.f);
            }
            if (o->oTimer == 25) {
                o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvHitbox);
                o->oHiddenBlueCoinSwitch->hitboxRadius = 50;
                o->oHiddenBlueCoinSwitch->hitboxDownOffset = 75;
                o->oHiddenBlueCoinSwitch->oDamageOrCoinValue = 4;
                o->oHiddenBlueCoinSwitch->hitboxHeight = 150;
            }
            if (o->oHiddenBlueCoinSwitch) {
                obj_set_parent_relative_pos(o->oHiddenBlueCoinSwitch, 0, 0, 50.f);
                obj_build_relative_transform(o->oHiddenBlueCoinSwitch);
                o->oHiddenBlueCoinSwitch->oInteractType = 8;
            }
            if (o->oTimer == 43) {
                obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                o->oHiddenBlueCoinSwitch = 0;
            }
            if (o->oTimer > 37) {

                o->oForwardVel = approach_f32_symmetric(o->oForwardVel, -10.f, 16.f);
            }
            cur_obj_init_animation(2);
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 5;
            }
            break;
        case 9:
            // knockback2
            if (o->oHiddenBlueCoinSwitch) {
                obj_mark_for_deletion(o->oHiddenBlueCoinSwitch);
                o->oHiddenBlueCoinSwitch = 0;
            }
            if (!o->oTimer) {
                o->oForwardVel = -60.f;
                o->oAngleVelRoll = 0x700 + (random_u16() % 0x700);
                o->oAngleVelPitch = 0x1100 + (random_u16() % 0x1100);
                o->oHealth--;
            }
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0, 2.f);
            if (o->oForwardVel == 0.f) {
                o->oInteractStatus = 0;
                if (o->oHealth < 1) {
                    o->oAction = 11;
                } else {
                    o->oAction = 5;
                }
            }
            break;
        case 10:
            // deathbeam
            if (o->oTimer == 4) {
                spawnDeathBeam(5);
            }
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, -10.f, 2.f);
            cur_obj_init_animation(3);
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 5;
            }
            break;
        case 11:
            cur_obj_init_animation(0);
            switch (o->oSubAction) {
                case 0:
                    if (talkToMario(137)) {
                        o->oSubAction = 1;
                        spawn_mist_particles();
                        spawn_triangle_break_particles(20, 138, 0.7f, 3);
                        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                    }
                    break;
                case 1:
                    stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                    spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 300.f,
                                       gMarioState->pos[2]);
                    obj_mark_for_deletion(o);
                    break;
            }
            break;
    }
    o->oAngleVelRoll = approach_s16_symmetric(o->oAngleVelRoll, 0, 0x80);
    o->oAngleVelPitch = approach_s16_symmetric(o->oAngleVelPitch, 0, 0x80);
    o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0, 0x400);
    o->oFaceAngleRoll = approach_s16_symmetric(o->oFaceAngleRoll, 0, 0x400);
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oFaceAngleRoll += o->oAngleVelRoll;
    gMarioState->pos[0] = 22647.f;
    if (gMarioState->pos[2] < 11265.f) {
        gMarioState->pos[2] = 11265.f;
    }
    if (gMarioState->pos[2] > 17931.f) {
        gMarioState->pos[2] = 17931.f;
    }
    if ((o->oAction != 3) && (o->oAction != 9)) {
        if (o->oInteractStatus & INT_STATUS_INTERACTED) /* bit 15 */
        {
            if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) /* bit 14 */
            {
                o->oMoveAngleYaw = o->oAngleToMario;
                o->oIntangibleTimer = -1;
                if (o->oAction < 4) {
                    o->oAction = 3;
                } else {
                    o->oAction = 9;
                }
            }
            o->oInteractStatus = 0;
        }
        o->oIntangibleTimer = 0;
        o->oInteractStatus = 0;
    }
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-78);
}
extern u16 waterphase;
extern Vtx sl_dl_CloudPlane_mesh_layer_1_vtx_0[400];
void snakepathanims(void) {
    Vtx *a = segmented_to_virtual(sl_dl_CloudPlane_mesh_layer_1_vtx_0);
    s32 i;
    s32 brightness;
    s32 alpha;
    waterphase += 0x12;
    if (!a[0].n.flag) {
        for (i = 0; i < 400; i++) {
            a[i].n.flag = a[i].n.ob[1] + 1;
        }
    }
#define SCROLLSIZE 5
#define WAVEHEIGHTMAX (256)
    for (i = 0; i < 400; i++) {
        a[i].n.ob[1] =
            a[i].n.flag + sins(a[i].n.ob[2] * SCROLLSIZE + waterphase * 17) * WAVEHEIGHTMAX
            + sins((a[i].n.ob[0] + a[i].n.ob[2] / 4) * SCROLLSIZE + waterphase * 21) * WAVEHEIGHTMAX;
        brightness = (a[i].n.ob[1] - a[0].n.flag) / (WAVEHEIGHTMAX / 32);
        a[i].v.cn[0] = 0x7F + brightness * 1.5f;
        a[i].v.cn[1] = 0x5F + brightness;
        a[i].v.cn[2] = 0x40 + brightness * .75f;
    }
}
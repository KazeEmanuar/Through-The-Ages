/// This is the bit that defines where the angles happen. They're basically environment boxes that
/// dictate camera behaviour. Permaswap is a boolean that simply determines wether or not when the
/// camera changes at this point it stays changed. 0 means it resets when you leave, and 1 means it
/// stays changed. The camera position fields accept "32767" as an ignore flag. The script supports
/// anything that does not take an argument. It's reccomended to keep the scripts in
/// puppycam_scripts.inc.c for the sake of cleanliness. If you do not wish to use a script in the angle,
/// then just leave the field as 0.
struct newcam_hardpos {
    u8 newcam_hard_levelID;
    u8 newcam_hard_areaID;
    s16 newcam_hard_X1;
    s16 newcam_hard_Y1;
    s16 newcam_hard_Z1;
    s16 newcam_hard_X2;
    s16 newcam_hard_Y2;
    s16 newcam_hard_Z2;
    s16 newcam_hard_camX;
    s16 newcam_hard_camY;
    s16 newcam_hard_camZ;
};
struct newcam_hitbox {
    u8 newcam_hard_levelID;
    u8 newcam_hard_areaID;
    s16 newcam_hard_X1;
    s16 newcam_hard_Y1;
    s16 newcam_hard_Z1;
    s16 newcam_hard_X2;
    s16 newcam_hard_Y2;
    s16 newcam_hard_Z2;
    s16 newcam_pitchset;
};
struct camException {
    u8 levelID;
    u8 area;
};
struct camExceptionObject {
    u8 levelID;
    u8 area;
    BehaviorScript *bhv;
};

struct newcam_hardpos newcam_fixedcam[] = {

    { /*Level ID*/ 55, /*Area ID*/ 5,
      // Standard params.
      /*X begin*/ -8192, /*Y begin*/ -8192, /*Z begin*/ -8192, // Where the activation box begins
      /*X end*/ 8192, /*Y end*/ 8192, /*Z end*/ 8192,          // Where the activation box ends.
      /*Cam X*/ -567, /*Cam Y*/ -40,
      /*Cam Z*/ -361 }, // The position the camera looks at for NC_MODE_FIXED_NOMOVE

    { /*Level ID*/ 55, /*Area ID*/ 2,
      // Standard params.
      /*X begin*/ 500, /*Y begin*/ -32000, /*Z begin*/ -32192, // Where the activation box begins
      /*X end*/ 32000, /*Y end*/ 32000, /*Z end*/ -7000,       // Where the activation box ends.
      /*Cam X*/ 1500, /*Cam Y*/ 800,
      /*Cam Z*/ -5500 }, // The position the camera looks at for NC_MODE_FIXED_NOMOVE

};

struct newcam_hitbox newcam_hitboxeset[] = {
    { /*Level ID*/ 55, /*Area ID*/ 1,
      /*X begin*/ -6065, /*Y begin*/ -6956, /*Z begin*/ -1852, // Where the activation box begins
      /*X end*/ -4966, /*Y end*/ -3628, /*Z end*/ -753, 0x3000 },

};
struct camException highHorizon[] = {
    { 55, 3 },

};
struct camException superHighHorizon[] = {
    { 55, 3 },

};
struct camException noRotations[] = {
    { 55, 4 },
};
struct camExceptionObject focusObject[] = {
    { 55, 6, bhvStaticObject },
};

int noRotationslength = sizeof(noRotations) / 2;
int focusLength = sizeof(focusObject) / 8;
int highHorizonlength = sizeof(highHorizon) / 2;
int superHighHorizonlength = sizeof(superHighHorizon) / 2;

#define lengthdir_x(length, dir) ((s16) (length * sins(dir)))
#define lengthdir_y(length, dir) ((s16) (length * coss(dir)))

void adjustTimers(int time) {
    timerbeforerotation = time;
    timerbeforeminmovement = time;
}

u32 rotate() {
    int i;
    for (i = 0; i < noRotationslength; i++) {
        if ((gCurrLevelNum == noRotations[i].levelID) && (gCurrAreaIndex == noRotations[i].area)) {
            return 0;
        }
    }
    return 1;
}
struct Object *find_obj(const BehaviorScript *behavior) {
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct Object *obj;
    struct ObjectNode *listHead;

    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
                return obj;
            }
        }
        obj = (struct Object *) obj->header.next;
    }
    return NULL;
}
struct Object *focus() {
    int i;
    for (i = 0; i < focusLength; i++) {
        if ((gCurrLevelNum == focusObject[i].levelID) && (gCurrAreaIndex == focusObject[i].area)) {
            return find_obj(focusObject[i].bhv);
        }
    }
    return 0;
}

u32 horizon() {
    int i;
    for (i = 0; i < highHorizonlength; i++) {
        if ((gCurrLevelNum == highHorizon[i].levelID) && (gCurrAreaIndex == highHorizon[i].area)) {
            return 1;
        }
    }
    return 0;
}
u32 superHorizon() {
    int i;
    for (i = 0; i < superHighHorizonlength; i++) {
        if ((gCurrLevelNum == superHighHorizon[i].levelID)
            && (gCurrAreaIndex == superHighHorizon[i].area)) {
            return 1;
        }
    }
    return 0;
}
static f32 ivrt(u32 axis) {
    return ((axis == 0) * 2 - 1);
}
// Nested if's baybeeeee
static void newcam_find_fixed(void) {
    u8 i = 0;

    for (i = 0; i < sizeof(newcam_fixedcam) / sizeof(struct newcam_hardpos); i++) {
        if (newcam_fixedcam[i].newcam_hard_levelID == gCurrLevelNum
            && newcam_fixedcam[i].newcam_hard_areaID == gCurrAreaIndex) {
            if (newcam_pos_target[0] > newcam_fixedcam[i].newcam_hard_X1)
                if (newcam_pos_target[0] < newcam_fixedcam[i].newcam_hard_X2)
                    if (newcam_pos_target[1] > newcam_fixedcam[i].newcam_hard_Y1)
                        if (newcam_pos_target[1] < newcam_fixedcam[i].newcam_hard_Y2)
                            if (newcam_pos_target[2] > newcam_fixedcam[i].newcam_hard_Z1)
                                if (newcam_pos_target[2] < newcam_fixedcam[i].newcam_hard_Z2) {
                                    if (newcam_fixedcam[i].newcam_hard_camX != 32767)
                                        newcam_pos[0] = newcam_fixedcam[i].newcam_hard_camX;
                                    if (newcam_fixedcam[i].newcam_hard_camY != 32767)
                                        newcam_pos[1] = newcam_fixedcam[i].newcam_hard_camY;
                                    if (newcam_fixedcam[i].newcam_hard_camZ != 32767)
                                        newcam_pos[2] = newcam_fixedcam[i].newcam_hard_camZ;

                                    newcam_yaw = atan2s(newcam_pos[2] - newcam_pos_target[2],
                                                        newcam_pos[0] - newcam_pos_target[0]);
                                }
        }
    }
}
u32 newcam_hitboxes() {
    int i;
    for (i = 0; i < sizeof(newcam_hitboxeset) / sizeof(struct newcam_hitbox); i++) {
        if (newcam_hitboxeset[i].newcam_hard_levelID == gCurrLevelNum
            && newcam_hitboxeset[i].newcam_hard_areaID == gCurrAreaIndex) {
            if (newcam_pos_target[0] > newcam_hitboxeset[i].newcam_hard_X1)
                if (newcam_pos_target[0] < newcam_hitboxeset[i].newcam_hard_X2)
                    if (newcam_pos_target[1] > newcam_hitboxeset[i].newcam_hard_Y1)
                        if (newcam_pos_target[1] < newcam_hitboxeset[i].newcam_hard_Y2)
                            if (newcam_pos_target[2] > newcam_hitboxeset[i].newcam_hard_Z1)
                                if (newcam_pos_target[2] < newcam_hitboxeset[i].newcam_hard_Z2) {
                                    newcam_pitch = newcam_hitboxeset[i].newcam_pitchset;
                                    return 1;
                                }
        }
    }
    return 0;
}
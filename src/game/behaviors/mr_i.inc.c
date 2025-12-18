// mr_i.c.inc

// this is actually the MrI particle loop function. piranha
// plant code later on reuses this function.
void bhv_piranha_particle_loop(void) {
    if (o->oTimer == 0) {
        o->oVelY = 20.0f + 20.0f * random_float();
        o->oForwardVel = 20.0f + 20.0f * random_float();
        o->oMoveAngleYaw = random_u16();
    }
    cur_obj_move_using_fvel_and_gravity();
}

void mr_i_piranha_particle_act_0(void) {
    cur_obj_scale(3.0f);
    o->oForwardVel = 20.0f;
    cur_obj_update_floor_and_walls();
    if (0x8000 & o->oInteractStatus)
        o->oAction = 1;
    else if ((o->oTimer >= 101) || (0x200 & o->oMoveFlags) || o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM) {
        obj_mark_for_deletion(o);
        spawn_mist_particles();
    }
}

void mr_i_piranha_particle_act_1(void) {
    s32 i;
    obj_mark_for_deletion(o);
    for (i = 0; i < 10; i++)
        spawn_object(o, MODEL_PURPLE_MARBLE, bhvPurpleParticle);
}

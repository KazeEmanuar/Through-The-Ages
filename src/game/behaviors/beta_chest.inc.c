/**
 * Behavior for bhvBetaChestBottom and bhvBetaChestLid.
 * These are apparently the beta versions of chests.
 * They do not spawn stars or appear in groups; they only
 * open and spawn an air bubble. In other words, they're
 * practically the same as underwater chests in-game, except
 * without any star-giving or puzzle functionality.
 */

/**
 * Init function for bhvBetaChestBottom.
 */
u8 chestCount = 0;
void bhv_beta_chest_bottom_init(void) {
    // Set the object's model
    cur_obj_set_model(MODEL_TREASURE_CHEST_BASE);

    // Spawn the chest lid 97 units in the +Y direction and 77 units in the -Z direction.
    spawn_object_relative(0, 0, 97, -77, o, MODEL_TREASURE_CHEST_LID, bhvBetaChestLid);
    chestCount=0;
}

/**
 * Update function for bhvBetaChestBottom.
 * This gives the chest a "virtual hitbox" that pushes Mario away
 * with radius 200 units and height 200 units.
 */
void bhv_beta_chest_bottom_loop(void) {
    cur_obj_push_mario_away_from_cylinder(200.0f, 200.0f);
}

/**
 * Update function for bhvBetaChestLid.
 * The chest lid handles all the logic of the chest,
 * namely opening the chest and spawning an air bubble.
 */
void bhv_beta_chest_lid_loop(void) {
    switch (o->oAction) {
        case BETA_CHEST_ACT_IDLE_CLOSED:
            if (dist_between_objects(o->parentObj, gMarioObject) < 300.0f) {
                o->oAction++; // Set to BETA_CHEST_ACT_OPENING
            }

            break;
        case BETA_CHEST_ACT_OPENING:
            if (o->oTimer == 0) {
                // Spawn the bubble 80 units in the -Y direction and 120 units in the +Z direction.
                spawn_object_relative(0, 0, -80, 120, o, MODEL_BUBBLE, bhvWaterAirBubble);
                play_sound(SOUND_GENERAL_CLAM_SHELL1, o->header.gfx.cameraToObject);
                spawn_orange_number(++chestCount, 0, 0, 0);
            }

            // Rotate the lid 0x400 (1024) angle units per frame backwards.
            // When the lid becomes vertical, stop rotating.
            o->oFaceAnglePitch -= 0x400;
            if (o->oFaceAnglePitch < -0x4000) {
                o->oAction++; // Set to BETA_CHEST_ACT_IDLE_OPEN
                if (chestCount==5){
                    cur_obj_spawn_star_at_y_offset(gMarioState->pos[0], gMarioState->pos[1]+200.f, gMarioState->pos[2], 200.f );
                }
            }

            // Fall-through
        case BETA_CHEST_ACT_IDLE_OPEN:
            break;
    }
}

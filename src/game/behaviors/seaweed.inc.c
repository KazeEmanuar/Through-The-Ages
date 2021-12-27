// seaweed.c.inc

void bhv_seaweed_init(void) {
    o->header.gfx.unk38.animFrame = random_float() * 80.0f;
    o->oDrawingDistance = 650000.f;
}

#define OFFSET 0x8000
void bhv_seaweed_bundle_init(void) {
    struct Object *seaweed;
    u16 rotOffset = random_u16();
    o->oPosY -=200.f;
    seaweed = spawn_object(o, MODEL_SEAWEED, bhvSeaweed);
    seaweed->oFaceAngleYaw = 14523+rotOffset;
    seaweed->oFaceAnglePitch = 5500 + OFFSET;
    seaweed->oFaceAngleRoll = 9600;
    seaweed->header.gfx.scale[0] = 1.0;
    seaweed->header.gfx.scale[1] = 1.0;
    seaweed->header.gfx.scale[2] = 1.0;
    //! gfx.animFrame uninitialized

    /*seaweed = spawn_object(o, MODEL_SEAWEED, bhvSeaweed);
    seaweed->oFaceAngleYaw = 41800;
    seaweed->oFaceAnglePitch = 6102+ OFFSET;
    seaweed->oFaceAngleRoll = 0;
    seaweed->header.gfx.scale[0] = 0.8;
    seaweed->header.gfx.scale[1] = 0.9;
    seaweed->header.gfx.scale[2] = 0.8;
    seaweed->header.gfx.unk38.animFrame = random_float() * 80.0f;*/

    seaweed = spawn_object(o, MODEL_SEAWEED, bhvSeaweed);
    seaweed->oFaceAngleYaw = 40500+rotOffset;
    seaweed->oFaceAnglePitch = 8700+ OFFSET;
    seaweed->oFaceAngleRoll = 4100;
    seaweed->header.gfx.scale[0] = 0.8;
    seaweed->header.gfx.scale[1] = 0.8;
    seaweed->header.gfx.scale[2] = 0.8;
    seaweed->header.gfx.unk38.animFrame = random_float() * 80.0f;

    seaweed = spawn_object(o, MODEL_SEAWEED, bhvSeaweed);
    seaweed->oFaceAngleYaw = 57236+rotOffset;
    seaweed->oFaceAnglePitch = 9500+ OFFSET;
    seaweed->oFaceAngleRoll = 0;
    seaweed->header.gfx.scale[0] = 1.2;
    seaweed->header.gfx.scale[1] = 1.2;
    seaweed->header.gfx.scale[2] = 1.2;
    seaweed->header.gfx.unk38.animFrame = random_float() * 80.0f;
}

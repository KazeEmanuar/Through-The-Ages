// bowser_key_cutscene.inc.c

Gfx *geo_scale_bowser_key(s32 run, struct GraphNode *node, UNUSED f32 mtx[4][4]) {
    struct Object *sp4;
    if (run == TRUE) {
        sp4 = (struct Object *) gCurGraphNodeObject;
        ((struct GraphNodeScale *) node->next)->scale = sp4->oBowserKeyScale;
    }
    return 0;
}

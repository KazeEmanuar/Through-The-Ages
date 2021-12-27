#ifndef SEGMENTS_H
#define SEGMENTS_H

/*
 * Memory addresses for segments. Ideally, this header file would not be
 * needed, and the addresses would be defined in sm64.ld and linker-inserted
 * into C code. However, there are some cases where that would not match, where
 * addresses are loaded using lui/ori rather than lui/addiu.
 * To avoid duplication, this file is included from sm64.ld. We make sure not
 * to cast the addresses to pointers in this file, since that would be invalid
 * linker script syntax.
*/

#define USE_EXT_RAM

/*
 * Workaround for running out of pool space due to
 * importing large custom content.
 */

#define SEG_BUFFERS      0x8005C000 // 0x0085000 in size
#define SEG_MAIN         0x801E1000 // 0x1328000 in size
#define SEG_ENGINE       0x80313800 // 0x0017000 in size
#define SEG_FRAMEBUFFERS 0x8035A800 // 0x0070800 in size
#define SEG_POOL_START   0x803CB000 // 0x0165000 in size
#define SEG_POOL_END     0x80800000
#define SEG_POOL_END_4MB 0x80400000 // For the error message screen enhancement.
#define SEG_GODDARD      SEG_POOL_START + 0x313000
#endif

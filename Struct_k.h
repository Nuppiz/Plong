#ifndef STRUCT_K_H
#define STRUCT_K_H

#include "Incl_std.h"
#include "Def_kb.h"

typedef struct
{
    uint8_t keycode;
    uint8_t type;
    uint32_t time;
} KeyEvent_t;

typedef struct
{
    KeyEvent_t queue[KB_QUEUE_LENGTH];
    uint8_t keystates[KB_ARRAY_LENGTH];
    uint8_t queue_head;
    uint8_t queue_tail;
} Keyboard_t;

#endif /* STRUCT_K_H */

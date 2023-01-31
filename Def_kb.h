#ifndef DEF_KB_H
#define DEF_KB_H

#include "Keylist.h"

/* Keyboard driver defines */

#define KB_ARRAY_LENGTH     256
#define KB_QUEUE_LENGTH     256

#define KEYHANDLER_INT      9
#define KEY_HIT_FLAG        1
#define KEY_PRESSED_FLAG    2
#define KEY_RELEASED_FLAG   0x80 // 128, MSB
#define KEY_SPECIAL_CODE    0xE0 // 224
#define KEY_IS_PRESSED(k)   (Keyboard.keystates[k] & KEY_PRESSED_FLAG)
#define KEY_WAS_HIT(k)      (Keyboard.keystates[k] & KEY_HIT_FLAG)
#define KEY_WAS_RELEASED(k) (Keyboard.keystates[k] & KEY_RELEASED_FLAG)
#define KEY_WAS_TOGGLED(k)  (Keyboard.keystates[k] & (KEY_HIT_FLAG|KEY_RELEASED_FLAG))

#endif /* DEF_KB_H */

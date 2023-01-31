#ifndef DEF_GEN_H
#define DEF_GEN_H
/* Common defines used throughout the code */

/* Boolean defines */
#define TRUE                1
#define FALSE               0

/* Color defines */
#define COLOR_BLACK         0
#define COLOR_COURT_RED     12
#define COLOR_WHITE         15
#define COLOR_BLUE          32
#define COLOR_RED           40
#define COLOR_YELLOW        44
#define TRANSPARENT_COLOR   36

/* Paddle and ball defines used for both physics and drawing */
#define PADDLE_HEIGHT       400
#define PADDLE_WIDTH        80
#define PADDLE_HEIGHT_HALF  200
#define PADDLE_WIDTH_HALF   40
#define BALL_DIAMETER       80
#define BALL_RADIUS         40
#define FIELD_LINE_WIDTH    6
#define NUM_PADDLES         2

#define COURT_WIDTH         3200
#define COURT_HEIGHT        2000
#define COURT_MULTIPLIER    10

/* Bitwise defines */
#define BIT_0               1
#define BIT_1               2
#define BIT_2               4
#define BIT_3               8
#define BIT_4               16
#define BIT_5               32
#define BIT_6               64
#define BIT_7               128
#define BIT_8               256
#define BIT_9               512
#define BIT_10              1024
#define BIT_11              2048
#define BIT_12              4096
#define BIT_13              8192
#define BIT_14              16384
#define BIT_15              32768

#define CONTROL_UP          BIT_0
#define CONTROL_DOWN        BIT_1
#define CONTROL_LEFT        BIT_2
#define CONTROL_RIGHT       BIT_3

#define setBit(bitfield, bit)   (bitfield) |= (bit)
#define clearBit(bitfield, bit) (bitfield) &= ~(bit)
#define isBitSet(bitfield, bit) ((bitfield) & (bit))

#endif /* DEF_GEN_H */

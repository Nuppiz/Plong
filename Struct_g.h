#ifndef STRUCT_G_H
#define STRUCT_G_H

#include "Incl_std.h"
#include "Struct_c.h"

/* In-game structs */

typedef struct
{
    uint8_t type; // AI or player
    Vec2_int current_pos;
    Vec2_int prev_pos;
    Vec2_int vel;
    uint8_t color;
    uint8_t movement_bits;
    uint8_t side;
    uint8_t score;
} Paddle_t;

typedef struct
{
    Vec2_int current_pos;
    Vec2_int prev_pos;
    Vec2_int vel;
    uint8_t color;
} Ball_t;

typedef struct
{
    Paddle_t Paddles[2];
    Ball_t Ball;
    uint8_t game_mode;
    uint8_t player_side; // for single player only
    uint8_t current_server; // whose turn it is to serve
    uint8_t ball_served;
    uint8_t game_status;
    uint8_t winner;
} Gamedata_t;

#endif /* STRUCT_G_H */

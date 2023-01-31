#ifndef GAME_H
#define GAME_H

#include "Incl_std.h"

void addScore(uint8_t scoring_side);
void gameInit(uint8_t game_mode, uint8_t player_side);
void ballInit(uint8_t server);
void ballReset(uint8_t server);

#endif /* GAME_H */

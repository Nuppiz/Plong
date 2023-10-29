#include "Incl_std.h"
#include "Def_draw.h"
#include "Def_gen.h"
#include "Def_game.h"
#include "Def_vid.h"
#include "Struct_g.h"
#include "Draw.h"
#include "Menu.h"
#include "Sounds.h"

extern Gamedata_t Game;

void ballInit(uint8_t server)
{
    Game.Ball.vel.x = 0;
    Game.Ball.vel.y = 0;
    Game.Ball.color = COLOR_YELLOW;
    if (server == LEFT)
    {
        Game.Ball.current_pos.x = Game.Paddles[0].current_pos.x + BALL_DIAMETER;
        Game.Ball.current_pos.y = Game.Paddles[0].current_pos.y;
        Game.current_server = LEFT;
    }
    else if (server == RIGHT)
    {
        Game.Ball.current_pos.x = Game.Paddles[1].current_pos.x - BALL_DIAMETER;
        Game.Ball.current_pos.y = Game.Paddles[1].current_pos.y;
        Game.current_server = RIGHT;
    }
}

void gameInit(uint8_t game_mode, uint8_t player_side)
{
    Game.Paddles[0].current_pos.x = PADDLE_WIDTH_HALF;
    Game.Paddles[0].current_pos.y = COURT_HEIGHT / 2;
    Game.Paddles[0].vel.x = 0;
    Game.Paddles[0].vel.y = 0;
    Game.Paddles[0].color = COLOR_BLUE;
    Game.Paddles[0].movement_bits = 0;
    Game.Paddles[0].side = LEFT;
    Game.Paddles[0].score = 0;

    Game.Paddles[1].current_pos.x = COURT_WIDTH - PADDLE_WIDTH_HALF;
    Game.Paddles[1].current_pos.y = COURT_HEIGHT / 2;
    Game.Paddles[1].vel.x = 0;
    Game.Paddles[1].vel.y = 0;
    Game.Paddles[1].color = COLOR_RED;
    Game.Paddles[1].movement_bits = 0;
    Game.Paddles[1].side = RIGHT;
    Game.Paddles[1].score = 0;

    switch (game_mode)
    {
    case SINGLE_PLAYER:
        if (player_side == LEFT)
        {
            Game.Paddles[0].type = PLAYER_1;
            Game.Paddles[1].type = AI_PLAYER;
            Game.current_server = LEFT;
        }
        else if (player_side == RIGHT)
        {
            Game.Paddles[0].type = AI_PLAYER;
            Game.Paddles[1].type = PLAYER_1;
            Game.current_server = RIGHT;
        }
        Game.game_mode = SINGLE_PLAYER;
        Game.player_side = Game.current_server;
        break;
    case TWO_PLAYER:
        Game.Paddles[0].type = PLAYER_1;
        Game.Paddles[1].type = PLAYER_2;
        Game.game_mode = TWO_PLAYER;
        break;
    case AI_ONLY:
        Game.Paddles[0].type = AI_PLAYER;
        Game.Paddles[1].type = AI_PLAYER;
        Game.game_mode = AI_ONLY;
        break;
    default:
        break;
    }
    drawField(COLOR_COURT_RED, COLOR_WHITE);
    ballInit(Game.current_server);
    Game.game_status = GAME_ONGOING;
}

void ballReset(uint8_t server)
{
    Game.Ball.vel.x = 0;
    Game.Ball.vel.y = 0;
    Game.ball_served = FALSE;
    if (server == LEFT)
    {
        Game.Ball.current_pos.x = Game.Paddles[0].current_pos.x + BALL_DIAMETER;
        Game.Ball.current_pos.y = Game.Paddles[0].current_pos.y;
        Game.current_server = LEFT;
    }
    else if (server == RIGHT)
    {
        Game.Ball.current_pos.x = Game.Paddles[1].current_pos.x - BALL_DIAMETER;
        Game.Ball.current_pos.y = Game.Paddles[1].current_pos.y;
        Game.current_server = RIGHT;
    }
}

void addScore(uint8_t scoring_side)
{
    scoreSound();
    drawRectangle(120, 10, 22, 10, COLOR_COURT_RED);
    drawRectangle(170, 10, 22, 10, COLOR_COURT_RED);
    if (scoring_side == LEFT_SCORES)
    {
        Game.Paddles[0].score++;
        if (Game.Paddles[0].score == WIN_SCORE)
        {
            Game.winner = LEFT_WINS;
            Game.game_status = GAME_OVER;
        }
    }
    else if (scoring_side == RIGHT_SCORES)
    {
        Game.Paddles[1].score++;
        if (Game.Paddles[1].score == WIN_SCORE)
        {
            Game.winner = RIGHT_WINS;
            Game.game_status = GAME_OVER;
        }
    }
}
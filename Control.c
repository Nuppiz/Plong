#include "Incl_std.h"
#include "Def_kb.h"
#include "Def_game.h"
#include "Def_gen.h"
#include "Struct_k.h"
#include "Struct_g.h"
#include "Movement.h"

extern Keyboard_t Keyboard;
extern Gamedata_t Game;
extern int running;

void controlPlayer()
{
    if (Game.Paddles[0].type != AI_PLAYER)
    {
        if (KEY_IS_PRESSED(KEY_W))
            Game.Paddles[0].movement_bits |= CONTROL_UP;
        else
        {
            Game.Paddles[0].movement_bits &= ~CONTROL_UP;
            if (Game.Paddles[0].vel.y < 0)
                Game.Paddles[0].vel.y = 0;
        }
        if (KEY_IS_PRESSED(KEY_S))
            Game.Paddles[0].movement_bits |= CONTROL_DOWN;
        else
        {
            Game.Paddles[0].movement_bits &= ~CONTROL_DOWN;
            if (Game.Paddles[0].vel.y > 0)
                Game.Paddles[0].vel.y = 0;
        }
        if (KEY_IS_PRESSED(KEY_A))
            Game.Paddles[0].movement_bits |= CONTROL_LEFT;
        else
        {
            Game.Paddles[0].movement_bits &= ~CONTROL_LEFT;
            if (Game.Paddles[0].vel.x < 0)
                Game.Paddles[0].vel.x = 0;
        }
        if (KEY_IS_PRESSED(KEY_D))
            Game.Paddles[0].movement_bits |= CONTROL_RIGHT;
        else
        {
            Game.Paddles[0].movement_bits &= ~CONTROL_RIGHT;
            if (Game.Paddles[0].vel.x > 0)
                Game.Paddles[0].vel.x = 0;
        }
        if (KEY_WAS_HIT(KEY_SPACEBAR) && Game.current_server == LEFT)
        {
            if (Game.ball_served == FALSE)
            {
                ballServe();
            }
        }

    }
    if (Game.Paddles[1].type != AI_PLAYER)
    {
        if (KEY_IS_PRESSED(KEY_UP))
            Game.Paddles[1].movement_bits |= CONTROL_UP;
        else
        {
            Game.Paddles[1].movement_bits &= ~CONTROL_UP;
            if (Game.Paddles[1].vel.y < 0)
                Game.Paddles[1].vel.y = 0;
        }
        if (KEY_IS_PRESSED(KEY_DOWN))
            Game.Paddles[1].movement_bits |= CONTROL_DOWN;
        else
        {
            Game.Paddles[1].movement_bits &= ~CONTROL_DOWN;
            if (Game.Paddles[1].vel.y > 0)
                Game.Paddles[1].vel.y = 0;
        }
        if (KEY_IS_PRESSED(KEY_LEFT))
            Game.Paddles[1].movement_bits |= CONTROL_LEFT;
        else
        {
            Game.Paddles[1].movement_bits &= ~CONTROL_LEFT;
            if (Game.Paddles[1].vel.x < 0)
                Game.Paddles[1].vel.x = 0;
        }
        if (KEY_IS_PRESSED(KEY_RIGHT))
            Game.Paddles[1].movement_bits |= CONTROL_RIGHT;
        else
        {
            Game.Paddles[1].movement_bits &= ~CONTROL_RIGHT;
            if (Game.Paddles[1].vel.x > 0)
                Game.Paddles[1].vel.x = 0;
        }
        if (KEY_WAS_HIT(KEY_ENTER) && Game.current_server == RIGHT)
        {
            if (Game.ball_served == FALSE)
            {
                ballServe();
            }
        }
    }
    if (KEY_WAS_HIT(KEY_F10))
        running = FALSE;
    if (KEY_WAS_HIT(KEY_HOME))
        Game.game_status = GAME_OVER;
}

void controlLoop()
{
    controlPlayer();
    //controlAI();
}
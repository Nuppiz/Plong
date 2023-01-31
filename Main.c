#include "Def_gen.h"
#include "Def_game.h"
#include "Def_menu.h"
#include "Struct_g.h"
#include "Control.h"
#include "Draw.h"
#include "Game.h"
#include "Keyb.h"
#include "Menu.h"
#include "Movement.h"
#include "Text.h"
#include "Video.h"

int running = TRUE;
Gamedata_t Game = {0};

void initAll()
{
    initKeyboard();
    loadFont();
    setVideoMode(VGA_256_COLOR_MODE);
}

void quit()
{
    deinitKeyboard();
    setVideoMode(TEXT_MODE);
    printf("Thanks for playing Plong!\n");
}

void gameLoop()
{
    while (Game.game_status != NOT_IN_GAME && running == TRUE)
    {
        controlLoop();
        if (Game.game_status == GAME_ONGOING)
        {
            physics();
        }

        if (Game.game_status == GAME_OVER)
        {
            int response;
            gameOver(Game.winner);
            response = newGame();
            if (response == FALSE)
                running = FALSE;
            else if (response == SAME_AGAIN)
            {
                gameInit(Game.game_mode, Game.player_side);
            }
            else if (response == CHANGE_SETTINGS)
            {
                Game.game_status = NOT_IN_GAME;
            }
        }
        drawLoop();
        render();
        clearKeys();
        delay(50);
    }
}

void main()
{
    initAll();
    while (running == TRUE)
    {
        while (Game.game_status == NOT_IN_GAME && running == TRUE)
        {
            modeSelect();
            render();
        }
        gameLoop();
    }
    quit();
}
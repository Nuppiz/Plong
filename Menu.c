#include "Def_game.h"
#include "Def_gen.h"
#include "Def_kb.h"
#include "Def_menu.h"
#include "Keyb.h"
#include "Struct_k.h"
#include "Game.h"
#include "Draw.h"
#include "Text.h"
#include "Video.h"

extern Keyboard_t Keyboard;
extern int running;

void gameOver(uint8_t winner)
{
    while (!KEY_WAS_HIT(KEY_ESC))
    {
        drawLoop();
        drawRectangle(80, 50, 160, 10, COLOR_BLACK);
        if (winner == LEFT_WINS)
            drawText(87, 51, "LEFT SIDE WINS!", COLOR_WHITE);
        else if (winner == RIGHT_WINS)
            drawText(82, 51, "RIGHT SIDE WINS!", COLOR_WHITE);
        render();
    }
}

void sideSelect(uint8_t game_mode)
{
    int selection = FALSE;
    clearKeys();

    while (selection == FALSE)
    {
        drawText(1, 1, "Select your side:\n"
                    "1) Left\n"
                    "2) Right\n", COLOR_WHITE);

        if (KEY_WAS_HIT(KEY_1))
        {
            gameInit(game_mode, LEFT);
            selection = TRUE;
        }
        else if (KEY_WAS_HIT(KEY_2))
        {
            gameInit(game_mode, RIGHT);
            selection = TRUE;
        }
        render();
    }
}

void modeSelect()
{
    drawText(1, 1, "Select game mode:\n"
                    "1) Single player\n"
                    "2) Two players\n"
                    "3) AI-only\n"
                    "4) Exit game", COLOR_WHITE);

    if (KEY_WAS_HIT(KEY_1))
        sideSelect(SINGLE_PLAYER);
    else if (KEY_WAS_HIT(KEY_2))
        gameInit(TWO_PLAYER, LEFT);
    else if (KEY_WAS_HIT(KEY_3))
        gameInit(AI_ONLY, LEFT);
    else if (KEY_WAS_HIT(KEY_4))
        running = FALSE;
}

int newGame()
{
    int selection = FALSE;
    int response;

    while (selection == FALSE)
    {
        drawText(1, 1, "Start a new game?\n"
                    "1) Yes, same settings\n"
                    "2) Yes, new settings\n"
                    "3) No, I want to quit\n", COLOR_WHITE);

        if (KEY_WAS_HIT(KEY_1))
        {
            selection = TRUE;
            response = SAME_AGAIN;
        }
        else if (KEY_WAS_HIT(KEY_2))
        {
            selection = TRUE;
            response = CHANGE_SETTINGS;
        }
        else if (KEY_WAS_HIT(KEY_3))
        {
            selection = TRUE;
            response = FALSE;
        }
        render();
    }
    return response;
}
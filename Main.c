#include "Def_gen.h"
#include "Def_game.h"
#include "Def_menu.h"
#include "Def_time.h"
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

static void interrupt (far *old_Timer_ISR)(void);

uint32_t program_time = 0;
int update_interval = 1000 / 33;
long last_update = 0;

void interrupt far Timer(void)
{
    static long last_clock_time = 0;

    program_time++;

    // keeps the PC clock ticking in the background
    if (last_clock_time + 182 < program_time)
    {
        last_clock_time = program_time;
        old_Timer_ISR();
    }
}

void setTimer(uint16_t new_count)
{
    outportb(CONTROL_8253, CONTROL_WORD);
    outportb(COUNTER_0, LOW_BYTE(new_count));
    outportb(COUNTER_0, HIGH_BYTE(new_count));
}

void initTimer()
{
    old_Timer_ISR = _dos_getvect(TIME_KEEPER_INT);
    _dos_setvect(TIME_KEEPER_INT, Timer);
    setTimer(TIMER_1000HZ);
}

void initAll()
{
    initKeyboard();
    initTimer();
    loadFont();
    setVideoMode(VGA_256_COLOR_MODE);
}

void quit()
{
    deinitKeyboard();
    setTimer(TIMER_18HZ);
    _dos_setvect(TIME_KEEPER_INT, old_Timer_ISR);
    setVideoMode(TEXT_MODE);
    printf("Thanks for playing Plong!\n");
}

void gameLoop()
{
    while (Game.game_status != NOT_IN_GAME && running == TRUE)
    {
        if (last_update + update_interval < program_time)
        {
            controlLoop();
            if (Game.game_status == GAME_ONGOING)
            {
                physics();
            }
            drawLoop();
            renderWithoutClear();
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
            clearKeys();
            last_update = program_time;
        }
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
            //renderWithoutClear();
        }
        gameLoop();
    }
    quit();
}
#include "Def_gen.h"
#include "Def_draw.h"
#include "Incl_std.h"
#include "Struct_g.h"
#include "Text.h"

extern uint8_t far screen_buf []; // Double screen buffer
extern Gamedata_t Game;

int boundaryCheck(int x, int y)
{
    if (x < SCREEN_WIDTH && x >= 0 && y < SCREEN_HEIGHT && y >= 0)
        return TRUE;
    else
        return FALSE;
}

void drawField(uint8_t base_color, uint8_t line_color)
{
    int x, y;

    memset(screen_buf, base_color, SCREEN_SIZE);

    // top line first
    for (y = 0; y < FIELD_LINE_WIDTH; y++)
    {
        for (x = 0; x < SCREEN_WIDTH; x++)
        {
            SET_PIXEL(x, y, line_color);
        }
        x = 0;
    }
    y = 0;
    x = 0;

    // then bottom...
    for (y = SCREEN_HEIGHT - FIELD_LINE_WIDTH; y < SCREEN_HEIGHT; y++)
    {
        for (x = 0; x < SCREEN_WIDTH; x++)
        {
            SET_PIXEL(x, y, line_color);
        }
        x = 0;
    }
    y = 0;
    x = 0;

    // then the left...
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (x = 0; x < FIELD_LINE_WIDTH; x++)
        {
            SET_PIXEL(x, y, line_color);
        }
        x = 0;
    }
    y = 0;
    x = 0;

    // then the right...
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (x = SCREEN_WIDTH - FIELD_LINE_WIDTH; x < SCREEN_WIDTH; x++)
        {
            SET_PIXEL(x, y, line_color);
        }
        x -= FIELD_LINE_WIDTH;
    }
    y = 0;
    x = 0;

    // and finally the middle
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (x = (SCREEN_WIDTH / 2) - FIELD_LINE_WIDTH / 2; x < (SCREEN_WIDTH / 2) + FIELD_LINE_WIDTH / 2; x++)
        {
            SET_PIXEL(x, y, line_color);
        }
        x -= FIELD_LINE_WIDTH;
    }
    y = 0;
    x = 0;
}

void drawPaddle(int x, int y, uint8_t color)
{
    int index_x = 0;
    int index_y = 0;

    // given x and y is the middle point of the paddle, so these must be corrected first
    x -= PADDLE_WIDTH_HALF;
    y -= PADDLE_HEIGHT_HALF;

    // and then scaled down for drawing
    x /= COURT_MULTIPLIER;
    y /= COURT_MULTIPLIER;

    for (index_y = 0; index_y < PADDLE_HEIGHT_DRAW; index_y++)
    {
        for (index_x = 0; index_x < PADDLE_WIDTH_DRAW; index_x++)
        {
            if (boundaryCheck(x, y) == TRUE)
            {
                SET_PIXEL(x, y, color);
                x++;
            }
        }
        index_x = 0;
        x -= PADDLE_WIDTH_DRAW;
        y++;
    }
    index_y = 0;
}

void drawBall(int x, int y, uint8_t color)
{   
    int index_x = 0;
    int index_y = 0;

    // given x and y is the middle point of the ball, so these must be corrected first
    x -= BALL_RADIUS;
    y -= BALL_RADIUS;

    // and then scaled down for drawing
    x /= COURT_MULTIPLIER;
    y /= COURT_MULTIPLIER;

    for (index_y = 0; index_y < BALL_DIAMETER_DRAW; index_y++)
    {
        for (index_x = 0; index_x < BALL_DIAMETER_DRAW; index_x++)
        {
            if (boundaryCheck(x, y) == TRUE)
            {
                SET_PIXEL(x, y, color);
                x++;
            }
        }
        index_x = 0;
        x -= BALL_DIAMETER_DRAW;
        y++;
    }
    index_y = 0;
}

void drawScore()
{
    char left_score[4];
    char right_score[4];

    sprintf(left_score, "%d", Game.Paddles[0].score);
    sprintf(right_score, "%d", Game.Paddles[1].score);

    drawText(120, 10, left_score, COLOR_BLACK);
    drawText(170, 10, right_score, COLOR_BLACK);
}

void drawRectangle(int x, int y, int w, int h, uint8_t color)
{
    int index_x = 0;
    int index_y = 0;

    for (index_y = 0; index_y < h; index_y++)
    {
        for (index_x = 0; index_x < w; index_x++)
        {
            SET_PIXEL(x, y, color);
            x++;
        }
        index_x = 0;
        x -= w;
        y++;
    }
    index_y = 0;
}

void drawLoop()
{
    int i, x, y;
    uint8_t color;

    drawField(COLOR_COURT_RED, COLOR_WHITE);

    for (i = 0; i < NUM_PADDLES; i++)
    {
        x = Game.Paddles[i].pos.x;
        y = Game.Paddles[i].pos.y;
        color = Game.Paddles[i].color;
        drawPaddle(x, y, color);
    }
    x = Game.Ball.pos.x;
    y = Game.Ball.pos.y;
    color = Game.Ball.color;
    drawBall(x, y, color);
    drawScore();
}
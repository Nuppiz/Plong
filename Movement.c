#include "Def_vid.h"
#include "Def_move.h"
#include "Def_gen.h"
#include "Def_game.h"
#include "Struct_g.h"
#include "Game.h"

/* Movement and collision */

extern Gamedata_t Game;

void paddleMove(Paddle_t* paddle)
{
    if ((paddle->movement_bits & CONTROL_UP) && paddle->vel.y > -PADDLE_MAX_SPEED)
        paddle->vel.y -= PADDLE_ACCELERATION_RATE;
    if ((paddle->movement_bits & CONTROL_DOWN) && paddle->vel.y < PADDLE_MAX_SPEED)
        paddle->vel.y += PADDLE_ACCELERATION_RATE;
    if ((paddle->movement_bits & CONTROL_LEFT) && paddle->vel.x > -PADDLE_MAX_SPEED)
        paddle->vel.x -= PADDLE_ACCELERATION_RATE;
    if ((paddle->movement_bits & CONTROL_RIGHT) && paddle->vel.x < PADDLE_MAX_SPEED)
        paddle->vel.x += PADDLE_ACCELERATION_RATE;

    paddle->pos.x += paddle->vel.x;
    paddle->pos.y += paddle->vel.y;
}

void ballPaddleDetect(Ball_t* ball)
{       
    Paddle_t* paddle;
    int y_diff, x_diff;

    if (ball->vel.x < 0) // left paddle
    {
        paddle = &Game.Paddles[0];
        y_diff = paddle->pos.y - ball->pos.y;
        x_diff = ball->pos.x - paddle->pos.x;
        if (y_diff >= -PADDLE_HEIGHT_HALF && y_diff <= PADDLE_HEIGHT_HALF)
        {
            if (x_diff <= BALL_RADIUS && x_diff >= -BALL_RADIUS)
            {
                ball->vel.x = -ball->vel.x + BALL_ACCELERATION_RATE;
                if (y_diff >= 0) // ball is higher than paddle
                    ball->vel.y = y_diff;
                if (y_diff <= 0) // ball is lower than paddle
                    ball->vel.y = -y_diff;
            }
        }
    }
    else if (ball->vel.x > 0) // right paddle
    {
        paddle = &Game.Paddles[1];
        y_diff = paddle->pos.y - ball->pos.y;
        x_diff = paddle->pos.x - ball->pos.x;
        if (y_diff >= -PADDLE_HEIGHT_HALF && y_diff <= PADDLE_HEIGHT_HALF)
        {
            if (x_diff <= BALL_RADIUS && x_diff >= -BALL_RADIUS)
            {
                ball->vel.x = -ball->vel.x - BALL_ACCELERATION_RATE;
                if (y_diff >= 0) // ball is higher than paddle
                    ball->vel.y = y_diff;
                if (y_diff <= 0) // ball is lower than paddle
                    ball->vel.y = -y_diff;
            }
        }
    }
}

void ballMove(Ball_t* ball)
{
    ball->pos.x += ball->vel.x;
    ball->pos.y += ball->vel.y;
}

void ballHold(Ball_t* ball)
{
    if (Game.current_server == LEFT)
    {
        ball->pos.x = Game.Paddles[0].pos.x + BALL_DIAMETER;
        ball->pos.y = Game.Paddles[0].pos.y;
    }
    else if (Game.current_server == RIGHT)
    {
        ball->pos.x = Game.Paddles[1].pos.x - BALL_DIAMETER;
        ball->pos.y = Game.Paddles[1].pos.y;
    }
}

void ballServe()
{
    Ball_t* ball = &Game.Ball;
    if (Game.current_server == LEFT)
    {
        ball->vel.x += BALL_INITIAL_SPEED;
        ball->vel.y = Game.Paddles[0].vel.y;
    }
    else if (Game.current_server == RIGHT)
    {
        ball->vel.x -= BALL_INITIAL_SPEED;
        ball->vel.y = Game.Paddles[1].vel.y;
    }
    Game.ball_served = TRUE;
}

void paddleEdgeDetect(Paddle_t* paddle)
{
    if (paddle->pos.x - PADDLE_WIDTH_HALF <= 0) // left edge
    {
        paddle->pos.x = 0 + PADDLE_WIDTH_HALF;
        paddle->vel.x = 0;
    }
    if (paddle->pos.y - PADDLE_HEIGHT_HALF <= 0) // top edge
    {
        paddle->pos.y = 0 + PADDLE_HEIGHT_HALF;
        paddle->vel.y = 0;
    }
    if (paddle->pos.x + PADDLE_WIDTH_HALF >= COURT_WIDTH) // right edge
    {
        paddle->pos.x = COURT_WIDTH - PADDLE_WIDTH_HALF;
        paddle->vel.x = 0;
    }
    if (paddle->pos.y + PADDLE_HEIGHT_HALF >= COURT_HEIGHT) // bottom edge
    {
        paddle->pos.y = COURT_HEIGHT - PADDLE_HEIGHT_HALF;
        paddle->vel.y = 0;
    }
    if (paddle->side == LEFT)
    {
        if (paddle->pos.x + PADDLE_WIDTH_HALF >= COURT_WIDTH / 2) // middle line
        {
            paddle->pos.x = COURT_WIDTH / 2 - PADDLE_WIDTH_HALF;
            paddle->vel.x = 0;
        }
    }
    else if (paddle->side == RIGHT)
    {
        if (paddle->pos.x - PADDLE_WIDTH_HALF <= COURT_WIDTH / 2) // middle line
        {
            paddle->pos.x = COURT_WIDTH / 2 + PADDLE_WIDTH_HALF;
            paddle->vel.x = 0;
        }
    }
}

int ballEdgeDetect(Ball_t* ball)
{
    if (ball->pos.x <= 0) // left edge
        return RIGHT_SCORES;
    if (ball->pos.x >= COURT_WIDTH) // right edge
        return LEFT_SCORES;
    if (ball->pos.y - BALL_RADIUS <= 0) // top edge
    {
        ball->pos.y = 0 + BALL_RADIUS;
        ball->vel.y = -ball->vel.y;
    }
    if (ball->pos.y + BALL_RADIUS >= COURT_HEIGHT) // bottom edge
    {
        ball->pos.y = COURT_HEIGHT - BALL_RADIUS;
        ball->vel.y = -ball->vel.y;
    }
    return 0;
}

static void AIThink(Paddle_t* ai_paddle)
{
    Ball_t* ball = &Game.Ball;
    if (ai_paddle->side == LEFT)
    {
        if (ball->vel.x < 0)
        {
            if (ball->pos.y < ai_paddle->pos.y)
            {
                ai_paddle->movement_bits &= ~CONTROL_DOWN;
                ai_paddle->movement_bits |= CONTROL_UP;
                if (ai_paddle->vel.y > 0)
                    ai_paddle->vel.y = 0;
            }
            if (ball->pos.y > ai_paddle->pos.y)
            {
                ai_paddle->movement_bits &= ~CONTROL_UP;
                ai_paddle->movement_bits |= CONTROL_DOWN;
                if (ai_paddle->vel.y < 0)
                    ai_paddle->vel.y = 0;
            }
            /*if (ball->pos.x < COURT_WIDTH / 2 && ai_paddle->pos.x < COURT_WIDTH / 6)
            {
                ai_paddle->movement_bits &= ~CONTROL_LEFT;
                ai_paddle->movement_bits |= CONTROL_RIGHT;
            }
            else
            {
                ai_paddle->movement_bits &= ~CONTROL_RIGHT;
                ai_paddle->movement_bits |= CONTROL_LEFT;
            }*/
        }
    }
    else if (ai_paddle->side == RIGHT)
    {
        if (ball->vel.x > 0)
        {
            if (ball->pos.y < ai_paddle->pos.y)
            {
                ai_paddle->movement_bits &= ~CONTROL_DOWN;
                ai_paddle->movement_bits |= CONTROL_UP;
                if (ai_paddle->vel.y > 0)
                    ai_paddle->vel.y = 0;
            }
            if (ball->pos.y > ai_paddle->pos.y)
            {
                ai_paddle->movement_bits &= ~CONTROL_UP;
                ai_paddle->movement_bits |= CONTROL_DOWN;
                if (ai_paddle->vel.y < 0)
                    ai_paddle->vel.y = 0;
            }
            /*if (ball->pos.x > COURT_WIDTH / 2 && ai_paddle->pos.x > COURT_WIDTH - (COURT_WIDTH / 6))
            {
                ai_paddle->movement_bits &= ~CONTROL_RIGHT;
                ai_paddle->movement_bits |= CONTROL_LEFT;
            }
            else
            {
                ai_paddle->movement_bits &= ~CONTROL_LEFT;
                ai_paddle->movement_bits |= CONTROL_RIGHT;
            }*/
        }
    }
}

static void AIServe(Paddle_t* ai_paddle)
{
    int movement_dir = (rand() % 50);
    int movement_time = (rand() % 25);
    int timer;

    ai_paddle->movement_bits = 0;
    ai_paddle->vel.x = 0;
    ai_paddle->vel.y = 0;

    if (movement_dir < 25)
        ai_paddle->movement_bits |= CONTROL_UP;
    else
        ai_paddle->movement_bits |= CONTROL_DOWN;

    for (timer = 0; timer < movement_time; timer++)
    {
        paddleMove(ai_paddle);
    }

    delay(500);

    ballServe();
}

static void dumbAI()
{
    int i;
    Paddle_t* ai_paddle;

    for (i = 0; i < NUM_PADDLES; i++)
    {
        if (Game.Paddles[i].type == AI_PLAYER)
        {
            ai_paddle = &Game.Paddles[i];
            if (Game.ball_served == FALSE && Game.current_server == ai_paddle->side)
            {
                AIServe(ai_paddle);
                ai_paddle->movement_bits = 0;
            }
            else
                AIThink(ai_paddle);
        }
    }
}

void physics()
{
    int i = 0;
    uint8_t scoring_side;

    if (Game.game_mode != TWO_PLAYER)
        dumbAI();

    while (i < NUM_PADDLES)
    {
        Paddle_t* paddle = &Game.Paddles[i];
        paddleMove(paddle);
        paddleEdgeDetect(paddle);
        i++;
    }
    if (Game.ball_served == TRUE)
    {
        ballMove(&Game.Ball);
        scoring_side = ballEdgeDetect(&Game.Ball);
        ballPaddleDetect(&Game.Ball);

        if (scoring_side != 0)
        {
            addScore(scoring_side);
            if (scoring_side == LEFT_SCORES)
                ballReset(RIGHT);
            else if (scoring_side == RIGHT_SCORES)
                ballReset(LEFT);
        }
    }
    else if (Game.ball_served == FALSE)
        ballHold(&Game.Ball);
}
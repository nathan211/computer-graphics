#include <iostream>
#include "ball.h"
void ballInit(BALL* ball, int x, int y)
{
	ball->x = x;
	ball->y = y;
	ball->vx = velocity(); /* phát sinh ngẫu nhiên vector chuyển động */
	ball->vy = velocity();
}
void ballDraw(BALL* ball)
{
	rectDraw(ball->x, ball->y, BALL_SIZE, BALL_SIZE, CR_WHITE);
}
void ballUpdate(BALL* ball)
{
	ball->x += BALL_SPEED * ball->vx;
	ball->y += BALL_SPEED * ball->vy;
}


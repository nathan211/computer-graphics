#include <iostream>
#include "paddle.h"
void paddleInit(PADDLE* pad, int x, int y)
{
	pad->x = x;
	pad->y = y;
	pad->score = 0; /* điểm số ban đầu */
	pad->dir = PADDLE_STOP; /* hướng di chuyển ban đầu */
}
void paddleDraw(PADDLE* pad)
{
	rectDraw(pad->x, pad->y, PADDLE_WIDTH, PADDLE_HEIGHT, CR_WHITE);
}
void paddleUpdate(PADDLE* pad)
{
	if (pad->dir == PADDLE_UP) { /* di chuyển lên, có kiểm tra va chạm */
		if (pad->y - PADDLE_SPEED > PADDLE_COLLIDE_TOP)
			pad->y -= PADDLE_SPEED;
		else
			pad->y = PADDLE_COLLIDE_TOP;
	}
	else
		if (pad->dir == PADDLE_DOWN) { /* di chuyển xuống, có kiểm tra va chạm */
			if (pad->y + PADDLE_SPEED < PADDLE_COLLIDE_BOTTOM)
				pad->y += PADDLE_SPEED;
			else
				pad->y = PADDLE_COLLIDE_BOTTOM;
		}
	pad->dir = PADDLE_STOP; /* dừng chuyển động */
}


#include <iostream>
#include "game.h"
bool gameInit(GAME* g, bool fullscreen)
{
	time_t t;
	srand((unsigned)time(&t)); /* randomize */
	SDL_Init(SDL_INIT_VIDEO);
	g_window = SDL_CreateWindow("Pong Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		BOARD_WIDTH, BOARD_HEIGHT,
		SDL_WINDOW_SHOWN |
		(fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
	if (!g_window) return false;
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (!g_renderer) return false;
	SDL_RenderClear(g_renderer);
	ballInit(&g->b, BALL_START_X, BALL_START_Y);
	paddleInit(&g->p1, PADDLE_LEFT, (BOARD_HEIGHT - PADDLE_HEIGHT) >> 1);
	paddleInit(&g->p2, PADDLE_RIGHT, (BOARD_HEIGHT - PADDLE_HEIGHT) >> 1);
	g->running = false;
	return true;
}
void gameShutdown(GAME* g)
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}
void gameDraw(GAME* g)
{
	/* xóa nội dung framebuffer */
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g_renderer);
	/* vẽ màn hình trò chơi */
	rectDraw(0, 0, BOARD_WIDTH, BOARD_CELL, CR_GRAY);
	rectDraw(0, BOARD_BOTTOM, BOARD_WIDTH, BOARD_CELL, CR_GRAY);
	for (int i = 0; i < (BOARD_HEIGHT / BOARD_CELL); i += 2)
		rectDraw((BOARD_WIDTH - BOARD_CELL) >> 1, (i + 1) * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, CR_GRAY);
	/* hiển thị điểm số của 2 người chơi */
	digitDraw((BOARD_WIDTH >> 1) - BOARD_CELL * 2 - DIGIT_WIDTH * BOARD_CELL,
		BOARD_TOP * 2, g->p1.score);
	digitDraw((BOARD_WIDTH >> 1) + BOARD_CELL * 2, BOARD_TOP * 2, g->p2.score);
	ballDraw(&g->b); /* vẽ quả bóng */
	paddleDraw(&g->p1); /* vẽ ván người chơi 1*/
	paddleDraw(&g->p2); /* vẽ ván người chơi 2 */
	SDL_RenderPresent(g_renderer); /* copy framebuffer->screen */
}
COLLIDE gameCheckCollide(GAME* g)
{
	/* xây dựng bounding-box cho các đối tượng để kiểm tra vùng chồng lấp */
	SDL_Rect b = { g->b.x, g->b.y, BALL_SIZE, BALL_SIZE };
	SDL_Rect p1 = { g->p1.x, g->p1.y, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_Rect p2 = { g->p2.x, g->p2.y, PADDLE_WIDTH, PADDLE_HEIGHT };
	/* bóng va chạm với 2 đáy */
	if (g->b.y < BOARD_TOP || g->b.y > BALL_COLLIDE_BOTTOM) return HIT_HORZ;
	/* bóng va chạm với mặt trong ván bên trái */
	if (rectCollide(&b, &p1)) {
		g->b.x = g->p1.x + PADDLE_WIDTH;
		return HIT_VERT;
	}
	/* bóng va chạm với mặt trong ván bên phải */
	if (rectCollide(&b, &p2)) {
		g->b.x = g->p2.x - BALL_SIZE;
		return HIT_VERT;
	}
	return HIT_NONE; /* không phát hiện va chạm */
}
void gameGoal(GAME* g, PADDLE* paddle)
{
	paddle->score++;
	g->b.x = BALL_START_X; g->b.y = BALL_START_Y;
}
void gameUpdate(GAME* g)
{
	/* cập nhật trạng thái trò chơi */
	paddleUpdate(&g->p1);
	paddleUpdate(&g->p2);
	ballUpdate(&g->b);
	switch (gameCheckCollide(g)) { /* kiểm tra va chạm */
	case HIT_HORZ: g->b.vy *= -1; break; /* va chạm ngang: đảo vy */
	case HIT_VERT: g->b.vx *= -1; break; /* va chạm dọc: đảo vx */
	default: break;
	}
	/* tính điểm */
	if (g->b.x < 0) gameGoal(g, &g->p2);
	if (g->b.x > BOARD_WIDTH - BALL_SIZE) gameGoal(g, &g->p1);
	/* dừng trò chơi nếu có người chơi đạt đến 10 điểm */
	if (g->p1.score == GAME_MAXSCORE || g->p2.score == GAME_MAXSCORE)
		g->running = false;
}
void gameInput(GAME* g)
{
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_w: g->p1.dir = PADDLE_UP; break;
			case SDLK_s: g->p1.dir = PADDLE_DOWN; break;
			case SDLK_UP: g->p2.dir = PADDLE_UP; break;
			case SDLK_DOWN: g->p2.dir = PADDLE_DOWN; break;
			case SDLK_ESCAPE: g->running = false; break;
			}
			break;
		case SDL_QUIT:
			g->running = false; break;
		}
	}
}
void gameLoop(GAME* g)
{
	long timerBegin, timerDiff, timerSleep;
	g->running = true;
	while (g->running)
	{
		timerBegin = SDL_GetTicks();
		gameUpdate(g); /* cập nhật trạng thái trò chơi */
		gameInput(g); /* xử lý input */
		gameDraw(g); /* dựng 1 frame hình */
		/* tính toán thời gian dựng 1 frame hình để giới hạn framerate tại 50fps */
		timerDiff = SDL_GetTicks() - timerBegin;
		timerSleep = GAME_FRAME_TIME - timerDiff;
		if (timerSleep > 0)
			SDL_Delay(timerSleep);
	}
}

#include <iostream>
#include "game.h"
void gameInit(GAME* g, SDL_bool fullscreen)
{
	srand(time(0));
	SDL_Init(SDL_INIT_VIDEO);
	g_window = SDL_CreateWindow("Snake",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		BOARD_CELL * BOARD_HORZ, BOARD_CELL * BOARD_VERT,
		SDL_WINDOW_SHOWN |
		(fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
	g_renderer = SDL_CreateRenderer(g_window, -1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	g->dir = UP;
	snakeInit(&g->s);
	fruitGen(&g->f, &g->s);
}
void gameShutdown(GAME* g)
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}
void gameUpdate(GAME* g)
{
	snakeUpdate(&g->s); /* cập nhật trạng thái của rắn */
	switch (g->dir) { /* di chuyển rắn */
	case UP: g->s.coords[0].y--; break; /* đi lên */
	case DOWN: g->s.coords[0].y++; break; /* đi xuống */
	case LEFT: g->s.coords[0].x--; break; /* sang trái */
	case RIGHT: g->s.coords[0].x++; break; /* sang phải */
	}
	/* rắn đã ăn mồi */
	if (g->s.coords[0].x == g->f.loc.x &&
		g->s.coords[0].y == g->f.loc.y) {
		g->s.len++; /* thân rắn dài thêm 1 đơn vị */
		fruitGen(&g->f, &g->s); /* phát sinh lại mồi tại vị trí khác */
	}
	/* cho phép rắn đi xuyên qua các biên */
	if (g->s.coords[0].x >= BOARD_HORZ) g->s.coords[0].x = 0;
	if (g->s.coords[0].x < 0) g->s.coords[0].x = BOARD_HORZ;
	if (g->s.coords[0].y >= BOARD_VERT) g->s.coords[0].y = 0;
	if (g->s.coords[0].y < 0) g->s.coords[0].y = BOARD_VERT;
	/* kiểm tra va chạm giữa đầu và thân rắn, nếu có va chạm: kết thúc trò chơi */
	for (int i = 1; i < g->s.len; i++)
		if (g->s.coords[0].x == g->s.coords[i].x &&
			g->s.coords[0].y == g->s.coords[i].y)
			g->running = SDL_FALSE;
}
void gameDraw(GAME* g)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);
	SDL_RenderClear(g_renderer);
	fruitDraw(&g->f); /* vẽ mồi */
	snakeDraw(&g->s); /* vẽ rắn */
	SDL_RenderPresent(g_renderer);
}

void gameInput(GAME* g)
{
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) /* xác định hướng di chuyển, chống đi lùi */
		{
		case SDLK_UP: if (g->dir != DOWN) g->dir = UP; break;
		case SDLK_DOWN: if (g->dir != UP) g->dir = DOWN; break;
		case SDLK_LEFT: if (g->dir != RIGHT) g->dir = LEFT; break;
		case SDLK_RIGHT: if (g->dir != LEFT) g->dir = RIGHT; break;
		case SDLK_ESCAPE: g->running = SDL_FALSE; break;
		}
		break;
	case SDL_QUIT:
		g->running = SDL_FALSE;
		break;
	}
}
void gameLoop(GAME* g)
{
	long timerBegin, timerDiff, timerSleep;
	g->running = SDL_TRUE;
	while (g->running) {
		timerBegin = SDL_GetTicks();
		gameUpdate(g); /* cập nhật trạng thái trò chơi */
		gameInput(g); /* xử lý input */
		gameDraw(g); /* dựng một frame hình */
		/* tính toán thời gian dựng xong 1 frame hình để giới hạn frame rate */
		timerDiff = SDL_GetTicks() - timerBegin;
		timerSleep = GAME_FRAME_TIME - timerDiff;
		if (timerSleep > 0)
			SDL_Delay(timerSleep); /* chờ cho đủ thời gian 12fps */
	}
}

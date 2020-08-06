#include "global.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
/* liệt kê các giá trị màu */
unsigned long GAME_PALETTE[CR_MAX_COLORS] =
{ 0x000000, 0x0000AA, 0x00AA00, 0x00AAAA,
0xAA0000, 0xAA00AA, 0xAA5500, 0xAAAAAA,
0x555555, 0x5555FF, 0x55FF55, 0x55FFFF,
 0xFF5555, 0xFF55FF, 0xFFFF55, 0xFFFFFF,
 0x95A7C4, 0x5D6B82 };
void setColor(int c)
{
	Uint32 color = GAME_PALETTE[c];
	SDL_SetRenderDrawColor(g_renderer,
		(color >> 16), /* tách thành phần R */
		(color >> 8) & 0xFF, /* tách thành phần G */
		color & 0xFF, /* tách thành phần B */
		0xFF);
}
void rectDraw(int x, int y, int w, int h, unsigned long color)
{
	SDL_Rect rc = { x, y, w, h };
	setColor(color);
	SDL_RenderFillRect(g_renderer, &rc);
}


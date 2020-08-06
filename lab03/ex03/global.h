#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_CELL 16 /* kích thước 1 ô, nên là lũy thừa của 2 */
#define BOARD_WIDTH (BOARD_CELL * 48) /* chiều rộng cửa sổ */
#define BOARD_HEIGHT (BOARD_CELL * 30) /* chiều cao cửa sổ */
#define BOARD_TOP BOARD_CELL /* biên đỉnh */
#define BOARD_BOTTOM (BOARD_HEIGHT-BOARD_CELL) /* biên đáy */
#define CR_WHITE 0xFF /* màu trắng */
#define CR_GRAY 0x66 /* màu xám */
#define CR_BLACK 0x00 /* màu đen */
#define DIGIT_WIDTH 3 /* chiều rộng 1 ký số */
#define DIGIT_HEIGHT 5 /* chiều cao 1 ký số */
/* khai báo các biến toàn cục */
extern SDL_Window* g_window; /* SDL window */
extern SDL_Renderer* g_renderer; /* SDL renderer */
extern char DIGITS[10 * DIGIT_HEIGHT]; /* font các ký số */
/* phát sinh vector chuyển động ngẫu nhiên */
int velocity();
/* kiểm tra va chạm giữa hai SDL_Rect */
SDL_bool rectCollide(const SDL_Rect* a, const SDL_Rect* b);
/* vẽ một hình chữ nhật */
void rectDraw(int x, int y, int w, int h, int cr);
/* vẽ một ký số sử dụng font chữ đã được định nghĩa */
void digitDraw(int x, int y, int digit);




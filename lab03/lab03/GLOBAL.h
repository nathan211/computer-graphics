#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>


#define BOARD_CELL
#define BOARD_HORZ
#define BOARD_VERT 
#define CR_BLACK 0
#define CR_BLUE 1
#define CR_GREEN 2
#define CR_CYAN 3
#define CR_RED 4
#define CR_MAGENTA 5
#define CR_BROWN 6
#define CR_GRAY 7
#define CR_DKGRAY 8
#define CR_BRBLUE 9
#define CR_BRGREEN 10
#define CR_BRCYAN 11
#define CR_BRRED 12
#define CR_BRMAGENTA 13
#define CR_YELLOW 14
#define CR_WHITE 15
#define CR_SNAKE_HEAD 16
#define CR_SNAKE_BODY 17


/* tổng số màu có thể sử dụng, bao gồm 16 màu EGA chuẩn và 2 màu dành cho rắn */
#define CR_MAX_COLORS 18
/* các hướng di chuyển có thể */
typedef enum direction { DOWN, LEFT, RIGHT, UP } DIRECTION;
/* cấu trúc lưu trữ tọa độ 2D */
typedef struct coord {
	int x, y;
} COORD;
/* các biến ngoại biên */
extern SDL_Window* g_window; /* SDL window */
extern SDL_Renderer* g_renderer; /* SDL renderer */
/* bảng giá trị các màu sắc có thể sử dụng được */
extern unsigned long GAME_PALETTE[CR_MAX_COLORS];
/* thiết lập giá trị màu hiện thời, sử dụng bảng màu đã cho */
void setColor(int c);
/* vẽ một hình chữ nhật */
void rectDraw(int x, int y, int w, int h, unsigned long color);
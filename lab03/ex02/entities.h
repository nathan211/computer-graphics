#pragma once
#include "global.h"
#define SNAKE_MAXLEN 100 /* chiều dài tối đa của rắn */
#define SNAKE_INITLEN 2 /* chiều dài ban đầu của rắn */
typedef struct snake {
	COORD coords[SNAKE_MAXLEN]; /* rắn là một danh sách các tọa độ 2D */
	int len; /* độ dài hiện thời của rắn */
} SNAKE;
typedef struct fruit {
	COORD loc; /* vị trí của mồi */
	Uint32 color; /* màu sắc */
} FRUIT;
/* vẽ một ô của thân rắn hoặc đầu rắn */
void snakeCell(COORD c, SDL_bool head);
/* khởi tạo rắn */
void snakeInit(SNAKE* s);
/* vẽ rắn */
void snakeDraw(const SNAKE* s);
/* cập nhật trạng thái của rắn */
void snakeUpdate(SNAKE* s);
/* phát sinh mồi */
void fruitGen(FRUIT* f, const SNAKE* s);
/* vẽ mồi */
void fruitDraw(const FRUIT* f);
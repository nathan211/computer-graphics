#pragma once
#include "global.h"
#define BALL_SIZE BOARD_CELL /* kích thước quả bóng */
#define BALL_SPEED 4 /* tốc độ di chuyển */
#define BALL_COLLIDE_TOP (BOARD_TOP) /* biên va chạm */
#define BALL_COLLIDE_BOTTOM (BOARD_BOTTOM-BALL_SIZE)
#define BALL_START_X (BOARD_WIDTH-BALL_SIZE) >> 1 /* tọa độ ban đầu */
#define BALL_START_Y (BOARD_HEIGHT-BALL_SIZE) >> 1
typedef struct ball {
	int x, y; /* tọa độ quả bóng */
	int vx, vy; /* vector chuyển động */
} BALL;
/* khởi tạo trạng thái ban đầu của quả bóng*/
void ballInit(BALL* ball, int x, int y);
/* vẽ quả bóng */
void ballDraw(BALL* ball);
/* cập nhật vị trí quả bóng */
void ballUpdate(BALL* ball);



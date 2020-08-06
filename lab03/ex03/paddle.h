#pragma once
#include "global.h"
#define PADDLE_WIDTH BOARD_CELL /* chiều rộng ván */
#define PADDLE_HEIGHT BOARD_CELL*4 /* chiều cao ván */
#define PADDLE_SPEED 16 /* tốc độ di chuyển */
#define PADDLE_GAP BOARD_CELL*3 /* khoảng cách đến biên màn hình */
#define PADDLE_LEFT (PADDLE_GAP)
#define PADDLE_RIGHT (BOARD_WIDTH-PADDLE_WIDTH-PADDLE_GAP)
#define PADDLE_COLLIDE_TOP (BOARD_TOP) /* biên va chạm */
#define PADDLE_COLLIDE_BOTTOM (BOARD_BOTTOM-PADDLE_HEIGHT)
/* enum mô tả hướng di chuyển */
typedef enum paddle_dir { PADDLE_STOP, PADDLE_UP, PADDLE_DOWN } PAD_DIR;
typedef struct paddle {
	int x, y; /* tọa độ ván */
	int score; /* điểm số */
	PAD_DIR dir; /* hướng di chuyển */
} PADDLE;
/* khởi tạo cấu trúc dữ liệu mô tả ván */
void paddleInit(PADDLE* pad, int x, int y);
/* vẽ tấm ván */
void paddleDraw(PADDLE* pad);
/* cập nhật vị trí của tấm ván */
void paddleUpdate(PADDLE* pad);

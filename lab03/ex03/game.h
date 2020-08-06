#pragma once
#include "global.h"
#include "ball.h"
#include "paddle.h"
#define GAME_MAXSCORE 10 /* điểm số tối đa */
#define GAME_MAX_FPS 50 /* giới hạn tốc độ khung hình 50fps */
#define GAME_FRAME_TIME (1000/GAME_MAX_FPS)
/* enum mô tả dạng va chạm của quả bóng */
typedef enum collide { HIT_NONE, HIT_VERT, HIT_HORZ } COLLIDE;
typedef struct game /* cấu trúc dữ liệu mô tả trò chơi gồm */
{
	BALL b; /* một quả bóng */
	PADDLE p1, p2; /* 2 đối tượng paddle đại diện cho 2 người chơi */
	bool running; /* cờ báo hiệu trạng thái của trò chơi */
} GAME;
/* khởi tạo trò chơi gồm cửa sổ, renderer, trạng thái ban đầu của trò chơi */
bool gameInit(GAME* g, bool fullscreen);
/* đóng trò chơi */
void gameShutdown(GAME* g);
/* vòng lặp trò chơi */
void gameLoop(GAME* g);
/* cập nhật trạng thái trò chơi */
void gameUpdate(GAME* g);
/* dựng hình cho 1 frame */
void gameDraw(GAME* g);
/* xử lý sự kiện từ bàn phím */
void gameInput(GAME* g);
/* tính điểm */
void gameGoal(GAME* g, PADDLE* paddle);
/* kiểm tra va chạm giữa các đối tượng trong trò chơi */
COLLIDE gameCheckCollide(GAME* g);

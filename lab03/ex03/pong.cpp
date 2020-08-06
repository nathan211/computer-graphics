#include <iostream>
#include "game.h"
#ifdef _MSC_VER /* thông số của trình liên kết Visual C++ */
# pragma comment (lib, "sdl2main.lib")
# pragma comment (lib, "sdl2.lib")
# pragma comment (linker, "/entry:\"mainCRTStartup\"" )
# pragma comment (linker, "/subsystem:WINDOWS")
#endif
int main(int argc, char** argv)
{
	GAME game;
	if (!gameInit(&game, false)) return -1;
	gameLoop(&game);
	gameShutdown(&game);
	return 0;
}
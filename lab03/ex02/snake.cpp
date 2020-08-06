#include "game.h"
#ifdef _MSC_VER /* chỉ thị liên kết với Visual C++ */
# pragma comment (lib, "sdl2main.lib")
# pragma comment (lib, "sdl2.lib")
# pragma comment (linker, "/entry:\"mainCRTStartup\"" )
# pragma comment (linker, "/subsystem:WINDOWS")
#endif
int main(int argc, char** argv)
{
	GAME g;
	gameInit(&g, SDL_FALSE);
	gameLoop(&g);
	gameShutdown(&g);
	return 0;
}

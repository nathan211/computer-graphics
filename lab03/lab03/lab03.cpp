#include <iostream>
#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include <stdio.h>
#include    <SDL2/SDL.h>

#ifdef _MSC_VER
#pragma comment (lib,"sdl2main.lib") 
#pragma comment (lib,"sdl2.lib") 
#pragma comment (linker,"/entry:\"mainCRTStartup\"" )  
#pragma comment (linker,"/subsystem:WINDOWS") 
#endif 
// _MSC_VER

#define WWIDTH  320 
#define WHEIGHT 240
#define BLK_SIZE 16

SDL_Window* wnd;
SDL_Renderer* rend;
int x = WWIDTH / 2, vx = 2;
int y = WHEIGHT / 2, vy = 2;



void block(int x, int y)
{
    SDL_Rect r = { x,y,BLK_SIZE,BLK_SIZE };
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderFillRect(rend, &r);
}


void init(int vsync) {




    SDL_Init(SDL_INIT_VIDEO);
    wnd = SDL_CreateWindow("FPS", 100, 100, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | (vsync ? SDL_RENDERER_PRESENTVSYNC : 0));
}


int event()
{
    SDL_Event e;
    int running = 1;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
                running = 0;
        }
        if (e.type == SDL_QUIT)
            running = 0;

    }
    return running;
}


void update()
{
    x += vx; y += vy;

    if (x<0 || x>WWIDTH - BLK_SIZE) vx = -vx;
    if (y<0 || y>WWIDTH - BLK_SIZE) vy = -vy;

}


void draw()
{
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);
    block(x, y);
    SDL_RenderPresent(rend);
}


void done() {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wnd);
    SDL_Quit();
}

int main(int argc, char** argv)
{
    int timerBegin, frameCount;
    float fps;
    int running = 1;
    char buf[64];



    init(1);
    frameCount = 0;
    timerBegin = SDL_GetTicks();
    while (running)
    {
        running = event();
        update();
        draw();
        frameCount++;

        fps = frameCount / ((SDL_GetTicks() - timerBegin) / 1000.0f);

        sprintf_s(buf, "FPS=%0.2f", fps);
        SDL_SetWindowTitle(wnd, buf);
    }
    done();
    return 0;

}

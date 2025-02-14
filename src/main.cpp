#include <iostream>

#include<SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600

int main(int argc, const char * argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("\nThere is a error:%s\n",SDL_GetError());
    }
    SDL_Window* window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if(window == NULL){
        printf("\nerror is %s\n",SDL_GetError());
    }
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Rect rect = (SDL_Rect) {200, 200, 200,200};
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_UpdateWindowSurface(window);

    SDL_bool quit = SDL_FALSE;
    while (!quit) {
       SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = SDL_TRUE;
            }
         }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
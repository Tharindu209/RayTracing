#include<stdio.h>
#include<SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600

int main(void){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow('Ray Tracing', SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Delay(10000);
}
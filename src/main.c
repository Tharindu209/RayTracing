#include <stdio.h>
#include <math.h>
#include<SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOUR_WHITE 0xFFFFFFFF
#define COLOUR_BLACK 0x00000000
#define COLOUR_GRAY 0x808080FF
#define NUM_RAYS 100

struct Circle{
    double x;
    double y;
    double r;
};

struct Rays{
    double start_x, start_y;
    double angle;
};

void fillTheCircle(SDL_Surface* surface, struct Circle circle, Uint32 colour){
    double radius_square = pow(circle.r, 2);
    for (double x=(circle.x - circle.r); x < (circle.r + circle.x); x++){
        for (double y=(circle.y - circle.r); y < (circle.y + circle.r); y++){
            double distance_square = pow(x - circle.x, 2) + pow(y-circle.y, 2);
            if (distance_square <= radius_square){
                SDL_Rect pixel = (SDL_Rect) {x, y, 1, 1};
                SDL_FillRect(surface, &pixel, colour);
            }
        }
    }
}

void generateRays(struct Circle circle, struct Rays rays[NUM_RAYS]){
    for (int i=0; i<NUM_RAYS; i++){
        double angle = (2 * M_PI * i) / NUM_RAYS;
        rays[i].start_x = circle.x;
        rays[i].start_y = circle.y;
        rays[i].angle = angle;
    }
}

void fillRays(SDL_Surface* surface, struct Rays rays[NUM_RAYS], Uint32 colour, struct Circle circle){
    double radius_square = pow(circle.r, 2);
    for (int i=0; i<NUM_RAYS; i++){
        struct Rays ray = rays[i];

        int offscreen = 0;
        int objeect_hit = 0;

        double x_draw = ray.start_x;
        double y_draw = ray.start_y;
        double step = 1;

        while (!offscreen && !objeect_hit){
            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);

            SDL_Rect pixel = (SDL_Rect) {x_draw, y_draw, 1, 1};
            SDL_FillRect(surface, &pixel, colour);

            if (x_draw < 0 || x_draw >= WIDTH || y_draw < 0 || y_draw >= HEIGHT){
                offscreen = 1;
            }

            double distance_square = pow(x_draw - circle.x, 2) + pow(y_draw - circle.y, 2);
            if (distance_square <= radius_square){
                objeect_hit = 1;
            }
        }   
    }
}

int main(int argc, char * argv[]) {
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
    SDL_Rect eraseRect = (SDL_Rect) {0, 0, WIDTH, HEIGHT};

    struct Circle circle = (struct Circle){100, 100, 60};
    struct Circle shadow_circle = (struct Circle) {650, 300, 100};

    int sim_running = 1;
    SDL_Event event;
    struct Rays rays[NUM_RAYS];
    while (sim_running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                sim_running = 0;
                return 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state){
                circle.x = event.motion.x;
                circle.y = event.motion.y;  
                
            }
        }
        generateRays(circle, rays);
        SDL_FillRects(surface, &eraseRect, 1, COLOUR_BLACK);
        fillTheCircle(surface, circle, COLOUR_WHITE); 
        fillTheCircle(surface, shadow_circle, SDL_MapRGB(surface->format, 255, 0, 0));
        fillRays(surface, rays, COLOUR_GRAY, shadow_circle);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(1);
    }

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
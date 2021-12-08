#include <stdio.h>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 800

int main(int argc, int* argv[]) {
    int quit = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Lorenz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while(!quit) {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT: quit = 1;break;
            case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) quit=1;break;
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
#include <stdio.h>
#include <SDL.h>

#define WIDTH 1000
#define HEIGHT 1000

int main(int argc, int* argv[]) {
    int quit = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Lorenz Attractor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    // Lorenz equations initialization
    // https://en.wikipedia.org/wiki/Lorenz_system

    double x=0.01,y=0.01,z=0.0;
    double rho   = 28.0;
    double sigma = 10.0;
    double beta  = 8.0/3.0;  
    double dt = 0.01;

    int counter = 0, step = 1, scale = 8;

    while(!quit) {
        
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT: quit = 1;break;
            case SDL_KEYDOWN: 
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit=1;break;
                    // pause simulation
                    case SDLK_SPACE: step=step?0:1;break;
                    // clear screen
                    case SDLK_c: 
                        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                        SDL_RenderClear(renderer);
                        break;
                }
        }

        if (step) {
            double dx = (sigma * (y - x)) * dt;
            double dy = (x * (rho - z) - y) * dt;
            double dz = (x*y - beta*z) * dt;

            x = x + dx;
            y = y + dy;
            z = z + dz;
            SDL_SetRenderDrawColor(renderer, 30 + counter, 0 + counter, 40 + counter, 255);
            SDL_RenderDrawPoint(renderer, x*scale + WIDTH/2, y*scale + HEIGHT/2);
            SDL_RenderPresent(renderer);
            counter+=1;
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
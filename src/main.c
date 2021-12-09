#include <stdio.h>
#include <SDL.h>

#define WIDTH 1920
#define HEIGHT 1080
#define P_COUNT 10

typedef struct particle {
    double x, y, z;
    int    r, g, b;
}particle;

int main(int argc, int* argv[]) {
    int quit = 0;
    SDL_Event event;

    // list of particles in simulation
    particle *particles = malloc(sizeof(particle) * P_COUNT);
    for (int i = 0; i < P_COUNT; i++) {
        particles[i].x = 0.001 * i;
        particles[i].y = 0;
        particles[i].z = 0;

        particles[i].r = 100 * i + 40;
        particles[i].g = 45 * i + 45;
        particles[i].b = 200 * i + 50;
    }


    // SDL initialization
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Lorenz Attractor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // clear screen
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    // Lorenz equations variable initialization
    // https://en.wikipedia.org/wiki/Lorenz_system

    double rho   = 28.0;
    double sigma = 10.0;
    double beta  = 8.0/3.0;  
    double dt = 0.01;

    int step = 1, scale = 20;

    while(!quit) {
        
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT: quit = 1;break;
            case SDL_KEYDOWN: 
                switch (event.key.keysym.sym) {
                    // quit if you hit escape 
                    case SDLK_ESCAPE: quit=1;break;
                    // pause simulation
                    case SDLK_SPACE: step=step?0:1;break;
                    // clear screen
                    case SDLK_c: 
                        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                        SDL_RenderClear(renderer);
                        break;
                    case SDLK_r:
                        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                        SDL_RenderClear(renderer);
                        for (int i = 0; i < P_COUNT; i++) {
                            particles[i].x = 0.01 * i;
                            particles[i].y = 0;
                            particles[i].z = 0;
                        }
                        break;
                }
        }

        // if not paused, run over each particle in the array, and update it's position
        if (step) {
            for (int i = 0; i < P_COUNT; i++) {
                double dx = (sigma * (particles[i].y - particles[i].x)) * dt;
                double dy = (particles[i].x * (rho - particles[i].z) - particles[i].y) * dt;
                double dz = (particles[i].x*particles[i].y - beta*particles[i].z) * dt;

                particles[i].x += dx;
                particles[i].y += dy;
                particles[i].z += dz;

                // render each particle with it's own rgb value at it's x and y value, in the middle of the renderer
                SDL_SetRenderDrawColor(renderer, particles[i].r, particles[i].g, particles[i].b, 255);
                SDL_RenderDrawPoint(renderer, particles[i].x*scale + WIDTH/2, particles[i].y*scale + HEIGHT/2);
                SDL_RenderPresent(renderer);
            }
        }
    }

    // free memory allocated
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    free(particles);
    SDL_Quit();
    return 0;
}
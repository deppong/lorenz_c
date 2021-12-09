#include <stdio.h>
#include <SDL.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define P_COUNT 3000

typedef struct particle {
    double x, y, z;
    int    r, g, b;
}particle;

particle rotateByMatrix(int *mat4[], particle p) {
    
}

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

    float theta = 0;

    int step = 1, scale = 10;

    int last_time = SDL_GetTicks();

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

                    case SDLK_RIGHT: theta+=10;break;
                    case SDLK_LEFT: theta -=10;break;
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

                // particles[i].x = cos(theta) * particles[i].x + sin(theta) * particles[i].z;
                // particles[i].z = -sin(theta) * particles[i].x + cos(theta) * particles[i].z;
            }

        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < P_COUNT; i++) {

            // render each particle with it's own rgb value at it's x and y value, in the middle of the renderer
            SDL_SetRenderDrawColor(renderer, particles[i].r, particles[i].g, particles[i].b, 255);
            SDL_RenderDrawPointF(renderer, particles[i].x*scale + WIDTH/2, particles[i].y*scale + HEIGHT/2);
        } 


        SDL_RenderPresent(renderer);

        if (SDL_GetTicks() - last_time < 1000 * dt) {
            SDL_Delay(1000 * dt - (SDL_GetTicks() - last_time));
            last_time = SDL_GetTicks();
        }

    }

    // free memory allocated
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    free(particles);
    SDL_Quit();
    return 0;
}
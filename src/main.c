#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "ship.h"

struct player_t {
    SDL_Rect location;
    struct ship_t* ship;
};

int main(int argc, char* argv[])
{
    int running;
    struct player_t player;
    SDL_Event ev;
    SDL_Window* win = NULL;
    SDL_Renderer* rend = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);

    win = SDL_CreateWindow("Frantic", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    player.ship = (struct ship_t*)malloc(sizeof(struct ship_t));
    ship_init(player.ship, rend, SHIP_STANDARD);
    player.location.w = FRANTIC_SHIP_WIDTH;
    player.location.h = FRANTIC_SHIP_HEIGHT;
    player.location.x = 10;
    player.location.y = 50;

    running = 1;
    while (running) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, player.ship->tex, NULL, &player.location);
        SDL_RenderPresent(rend);
    }

    ship_free(player.ship);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return EXIT_SUCCESS;
}

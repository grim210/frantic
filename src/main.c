#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "input.h"
#include "ship.h"
#include "timer.h"

#define FRANTIC_SHIP_SPEED_VERTICAL      (300.0f)
#define FRANTIC_SHIP_SPEED_LATERAL       (200.0f)

/* SDL_Rect, but more accurate */
struct frect_t {
    float x, y;
    float w, h;
};

struct player_t {
    double prev_time;
    struct frect_t position;
    struct input_t* input;
    struct ship_t* ship;
};

void draw(SDL_Renderer* rend, struct player_t* player);
void update(struct player_t* player, double elapsed);

int main(int argc, char* argv[])
{
    int running;
    double elapsed;
    struct player_t player;
    struct timer_t timer;
    SDL_Event ev;
    SDL_Window* win = NULL;
    SDL_Renderer* rend = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);

    win = SDL_CreateWindow("Frantic", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    timer_init(&timer);

    player.ship = (struct ship_t*)malloc(sizeof(struct ship_t));
    ship_init(player.ship, rend, SHIP_STANDARD);

    player.input = (struct input_t*)malloc(sizeof(struct input_t));
    input_init(player.input);

    player.position.w = FRANTIC_SHIP_WIDTH;
    player.position.h = FRANTIC_SHIP_HEIGHT;
    player.position.x = 10.0f;
    player.position.y = 50.0f;

    timer_elapsed(&timer, &player.prev_time);

    running = 1;
    while (running) {
        while (SDL_PollEvent(&ev)) {
            if (!input_update(player.input, &ev)) {
                if (ev.type == SDL_QUIT) {
                    running = 0;
                }
            }
        }

        timer_elapsed(&timer, &elapsed);
        //fprintf(stdout, "Elapsed time: %f\n", elapsed);

        update(&player, elapsed);

        SDL_RenderClear(rend);
        draw(rend, &player);
        SDL_RenderPresent(rend);
    }

    ship_free(player.ship);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return EXIT_SUCCESS;
}

void draw(SDL_Renderer* rend, struct player_t* player)
{
    SDL_Rect pos;

    if (rend == NULL || player == NULL) {
        return;
    }

    pos.x = (unsigned)player->position.x;
    pos.y = (unsigned)player->position.y;
    pos.w = (unsigned)player->position.w;
    pos.h = (unsigned)player->position.h;

    SDL_RenderCopy(rend, player->ship->tex, NULL, &pos);
}

void update(struct player_t* player, double elapsed)
{
    double delta = elapsed - player->prev_time;
    player->prev_time = elapsed;

    if (input_poll(player->input, INPUT_UP)) {
        player->position.y -= delta * FRANTIC_SHIP_SPEED_VERTICAL;
    }

    if (input_poll(player->input, INPUT_DOWN)) {
        player->position.y += delta * FRANTIC_SHIP_SPEED_VERTICAL;
    }

    if (input_poll(player->input, INPUT_LEFT)) {
        player->position.x -= delta * FRANTIC_SHIP_SPEED_LATERAL;
    }

    if (input_poll(player->input, INPUT_RIGHT)) {
        player->position.x += delta * FRANTIC_SHIP_SPEED_LATERAL;
    }
}

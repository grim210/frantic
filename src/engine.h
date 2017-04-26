#ifndef FRANTIC_ENGINE_H
#define FRANTIC_ENGINE_H

#include "ftypes.h"
#include "input.h"
#include "ship.h"
#include "timer.h"

/* Not yet complicated enough to split off from the engine code. */
struct player_t {
    struct frect_t position;
    struct ship_t ship;
};

struct engine_t {
    int running;
    double prev_time;
    struct input_t input;
    struct player_t player;
    struct timer_t timer;

    SDL_Renderer* rend;
    SDL_Window* window;
};

int engine_free(struct engine_t* engine);
int engine_init(struct engine_t* engine);
int engine_run(struct engine_t* engine);

#endif

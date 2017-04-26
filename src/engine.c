#include "engine.h"

#define FRANTIC_SHIP_SPEED_VERTICAL     (300.0f)
#define FRANTIC_SHIP_SPEED_LATERAL      (200.0f)

void _engine_draw(struct engine_t* engine);
void _engine_update(struct engine_t* engine);

int engine_free(struct engine_t* engine)
{
    SDL_DestroyRenderer(engine->rend);
    SDL_DestroyWindow(engine->window);

    SDL_Quit();

    return 0;
}

int engine_init(struct engine_t* engine)
{
    /* XXX: We'll throttle back this EVERYTHING flag later on */
    SDL_Init(SDL_INIT_EVERYTHING);

    engine->window = SDL_CreateWindow("Frantic", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if (engine->window == NULL) {
        return -1;
    }

    engine->rend = SDL_CreateRenderer(engine->window, -1,
        SDL_RENDERER_ACCELERATED);
    if (engine->rend == NULL) {
        return -1;
    }

    timer_init(&engine->timer);
    ship_init(&engine->player.ship, engine->rend, SHIP_STANDARD);
    input_init(&engine->input);

    engine->player.position.w = FRANTIC_SHIP_WIDTH;
    engine->player.position.h = FRANTIC_SHIP_HEIGHT;
    engine->player.position.x = 0.0f;
    engine->player.position.y = 0.0f;

    timer_elapsed(&engine->timer, &engine->prev_time);

    return 0;
}

int engine_run(struct engine_t* engine)
{
    double elapsed;
    SDL_Event ev;

    engine->running = 1;

    while (engine->running) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_QUIT:
                engine->running = 0;
                break;
            default:
                input_update(&engine->input, &ev);
            }
        }

        _engine_update(engine);
        _engine_draw(engine);
    }

    return 0;
}

void _engine_draw(struct engine_t* engine)
{
    SDL_Rect pos;
    pos.x = (unsigned)engine->player.position.x;
    pos.y = (unsigned)engine->player.position.y;
    pos.w = (unsigned)engine->player.position.w;
    pos.h = (unsigned)engine->player.position.h;

    SDL_RenderClear(engine->rend);
    SDL_RenderCopy(engine->rend, engine->player.ship.tex, NULL, &pos);
    SDL_RenderPresent(engine->rend);
}

void _engine_update(struct engine_t* engine)
{
    double elapsed, delta;

    timer_elapsed(&engine->timer, &elapsed);
    delta = elapsed - engine->prev_time;
    engine->prev_time = elapsed;

    if (input_poll(&engine->input, INPUT_UP)) {
        engine->player.position.y -= delta * FRANTIC_SHIP_SPEED_VERTICAL;
    }

    if (input_poll(&engine->input, INPUT_DOWN)) {
        engine->player.position.y += delta * FRANTIC_SHIP_SPEED_VERTICAL;
    }

    if (input_poll(&engine->input, INPUT_LEFT)) {
        engine->player.position.x -= delta * FRANTIC_SHIP_SPEED_LATERAL;
    }

    if (input_poll(&engine->input, INPUT_RIGHT)) {
        engine->player.position.x += delta * FRANTIC_SHIP_SPEED_LATERAL;
    }
}

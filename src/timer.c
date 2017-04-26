#include "timer.h"

int timer_duplicate(struct timer_t* timer, struct timer_t* out)
{
    if (timer == NULL || out == NULL) {
        return -1;
    }

    out->start = timer->start;
    out->frequency = timer->frequency;

    return 0;
}

int timer_elapsed(struct timer_t* timer, double* out)
{
    double diff, freq;
    
    if (timer == NULL || out == NULL) {
        return -1;
    }

    diff = (double)(SDL_GetPerformanceCounter() - timer->start);
    freq = (double)timer->frequency;

    *out = diff / freq;
    return 0;
}

int timer_free(struct timer_t* timer) { return 0; }

int timer_init(struct timer_t* timer)
{
    if (timer == NULL) {
        return -1;
    }

    timer->start = SDL_GetPerformanceCounter();
    timer->frequency = SDL_GetPerformanceFrequency();

    return 0;
}

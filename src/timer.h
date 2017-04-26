#ifndef FRANTIC_TIMER_H
#define FRANTIC_TIMER_H

#include <SDL2/SDL.h>

struct timer_t {
    uint64_t start, frequency;
};

int timer_duplicate(struct timer_t* timer, struct timer_t* out);
int timer_elapsed(struct timer_t* timer, double* out);
int timer_free(struct timer_t* timer);
int timer_init(struct timer_t* timer);

#endif

#ifndef FRANTIC_INPUT_H
#define FRANTIC_INPUT_H

#include <SDL2/SDL.h>

enum input_e {
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_PAUSE,
    _input_e_len_
};

struct input_t {
    unsigned toggled[_input_e_len_];
};

int input_free(struct input_t* input);
int input_init(struct input_t* input);
int input_poll(struct input_t* input, enum input_e in);
int input_update(struct input_t* input, SDL_Event* ev);

#endif

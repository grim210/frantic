#include "input.h"

int input_free(struct input_t* input)
{
    /*
    * Nothing to here.. everything is statically allocated.
    */
    return 0;
}

int input_init(struct input_t* input)
{
    if (input == NULL) {
        return -1;
    }

    memset(&input->toggled, 0, sizeof(unsigned) * _input_e_len_);

    /*
    * I'll have an input mapping that is configured here eventually.
    */
    return 0;
}

int input_poll(struct input_t* input, enum input_e in)
{
    return input->toggled[in];
}

int input_update(struct input_t* input, SDL_Event* ev)
{
    unsigned pressed, val;
    enum input_e in;

    switch (ev->type) {
    case SDL_KEYUP:
        pressed = 0;
        val = ev->key.keysym.sym;
        break;
    case SDL_KEYDOWN:
        pressed = 1;
        val = ev->key.keysym.sym;
        break;
    case SDL_JOYAXISMOTION:
    case SDL_JOYHATMOTION:
    case SDL_JOYBUTTONUP:
    case SDL_JOYBUTTONDOWN:
        fprintf(stdout, "INFO: input_update: Joysticks not supported.\n");
    default:
        return 0;
    }

    switch (val) {
    case SDLK_w:
        in = INPUT_UP;
        fprintf(stdout, "INFO: input_update: up was ");
        break;
    case SDLK_a:
        in = INPUT_LEFT;
        fprintf(stdout, "INFO: input_update: left was ");
        break;
    case SDLK_s:
        in = INPUT_DOWN;
        fprintf(stdout, "INFO: input_update: down was ");
        break;
    case SDLK_d:
        in = INPUT_RIGHT;
        fprintf(stdout, "INFO: input_update: right was ");
        break;
    case SDLK_SPACE:
        in = INPUT_SHOOT;
        fprintf(stdout, "INFO: input_update: shoot was ");
        break;
    default:
        fprintf(stdout, "INFO: unrecognized keyboard input.\n");
        return 0;
    }

    if (pressed) {
        fprintf(stdout, "pressed.\n");
    } else {
        fprintf(stdout, "released.\n");
    }

    input->toggled[in] = pressed;
    return 1;
}

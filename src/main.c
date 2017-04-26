#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "engine.h"

int main(int argc, char* argv[])
{
    struct engine_t engine;

    engine_init(&engine);
    engine_run(&engine);
    engine_free(&engine);

    return 0;
}

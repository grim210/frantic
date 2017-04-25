#ifndef FRANTIC_SHIP_H
#define FRANTIC_SHIP_H

#include <SDL2/SDL.h>

#define FRANTIC_SHIELD_DAMAGE_RATE      (1)
#define FRANTIC_SHIP_WIDTH              (64)
#define FRANTIC_SHIP_HEIGHT             (32)

struct ship_t {
    enum ship_type_e {
        SHIP_STANDARD,
        _ship_type_len_
    } type;

    int max_health;
    int current_health;
    int shield_health;

    int alive;
    SDL_Texture* tex;
};

void ship_addhealth(struct ship_t* ship, int amount);
void ship_addshield(struct ship_t* ship, int amount);
int ship_damage(struct ship_t* ship, int amount);
int ship_free(struct ship_t* ship);
int ship_init(struct ship_t* out, SDL_Renderer* r, enum ship_type_e type);

#endif  /* FRANTIC_SHIP_H */

#include "ship.h"

void ship_addhealth(struct ship_t* ship, int amount)
{
    ship->current_health += amount;
    if (ship->current_health > ship->max_health) {
        ship->current_health = ship->max_health;
    }
}

void ship_addshield(struct ship_t* ship, int amount)
{
    ship->shield_health += amount;
}

int ship_damage(struct ship_t* ship, int amount)
{
    if (ship->shield_health > 0) {
        ship->current_health -= (amount / 2);
        ship->shield_health -= FRANTIC_SHIELD_DAMAGE_RATE;
    } else {
        ship->current_health -= amount;
    }

    if (ship->current_health <= 0) {
        ship->alive = 0;
        return 1;
    }

    return 0;
}

int ship_free(struct ship_t* ship)
{
    SDL_DestroyTexture(ship->tex);

    return 0;
}

int ship_init(struct ship_t* ship, SDL_Renderer* r, enum ship_type_e type)
{
    SDL_Surface* img = NULL;

    if (ship == NULL) {
        return -1;
    }

    ship->type = type;
    ship->alive = 1;
    ship->shield_health = 0;

    /* hard-coded values for now */
    switch (ship->type) {
    case SHIP_STANDARD:
        img = SDL_LoadBMP("assets/ship.bmp");
        if (img == NULL) {
            return -1;
        }
        ship->max_health = 10;
        break;
    default:
        return -1;
    }

    /* magenta is transarent */
    SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 0, 255));

    ship->current_health = ship->max_health;
    ship->shield_health = 0;
    ship->tex = SDL_CreateTextureFromSurface(r, img);
    if (ship->tex == NULL) {
        return -1;
    }

    SDL_FreeSurface(img);

    return 0;
}

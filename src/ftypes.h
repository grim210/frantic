#ifndef FRANTIC_FTYPES_H
#define FRANTIC_FTYPES_H

/*
* An SDL_Rect, but more accurate.  Easier to use with floating point math.
*/
struct frect_t {
    float x, y;
    float w, h;
};

struct fpoint_t {
    float x, y;
};

/* TODO: This will definitely come up as a requirement. */
int frect_intersects(struct frect_t* r1, struct frect_t* r2);

#endif /* FRANTIC_FTYPES_H */

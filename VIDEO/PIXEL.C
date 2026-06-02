#include <stdlib.h>

#include "screen.h"
#include "types.h"

struct point {
    uint16_t x;
    uint16_t y;
};

struct pixel {
    struct point coordinates;
    uint8_t color;
};

struct pixel *pixel_create(uint16_t x, uint16_t y, uint8_t color)
{
    struct pixel *pixel = malloc(sizeof(*pixel));

    pixel->coordinates.x = x;
    pixel->coordinates.y = y;
    pixel->color = color;

    return pixel;
}

void pixel_destroy(struct pixel *pixel)
{
    free(pixel);
}

void pixel_draw(struct pixel *pixel)
{
    VGA[pixel->coordinates.y * SCREEN_WIDTH + pixel->coordinates.x] = pixel->color;
}

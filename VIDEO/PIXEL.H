#ifndef PIXEL_H
#define PIXEL_H

#include "types.h"

typedef struct pixel pixel_t;

pixel_t *pixel_create(uint16_t x, uint16_t y, uint8_t color);

void pixel_destroy(pixel_t *pixel);

void pixel_draw(pixel_t *pixel);

#endif // PIXEL_H


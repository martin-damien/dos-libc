#include <dos.h>
#include <stdlib.h>

#include "math.h"
#include "types.h"
#include "video/screen.h"
#include "video/pixel.h"

/* We need to allocate even if it's pointers */
uint8_t *VGA;
uint16_t *video_clock;

static void screen_set_mode(uint8_t mode)
{
    union REGS regs;

    regs.h.ah = SCREEN_SET_MODE;
    regs.h.al = mode;
    int86(SCREEN_VIDEO_INT, &regs, &regs);
}

#ifdef __DJGPP__

#include <sys/nearptr.h>

void screen_init()
{
    __djgpp_nearptr_enable();

    VGA = (uint8_t*)(0xA0000 + __djgpp_conventional_base);
    video_clock = (uint16_t*)(0x046C + __djgpp_conventional_base);

    screen_set_mode(SCREEN_MODE_256_COLORS);
}

void screen_restore()
{
    __djgpp_nearptr_disable();
    screen_set_mode(SCREEN_MODE_TEXT);
}

#else

void screen_init()
{
    VGA = (uint8_t*)0xA0000;
    video_clock = (uint16_t*)0x046C;

    screen_set_mode(SCREEN_MODE_256_COLORS);
}

void screen_restore()
{
    screen_set_mode(SCREEN_MODE_TEXT);
}

#endif



/*
 * Draw a line based on the Bresenham's line-drawing algorithm.
 *
 * This algorithm avoid using floats to ensure good performances.
 *
 * In a more modern way, we would compute the slope (dy/dx) and multiply
 * x by this number to get y.
 *
 * For dx = 8 and dy = 3
 *
 *      dy     3
 *     ---- = --- = 0.375
 *      dx     8
 *
 * As we avoid using floats, we can :
 *
 * - Set an error accumulator (to store the times we encounter a fractional value)
 * - Add dy to this accumulator
 * - Once the accumulator becoms >= dx:
 *   - Move one pixel on the secondary axis
 *   - Substract dx from the accumulator
 */
void video_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color)
{
    int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

    dx = x2 - x1;    /* The horizontal distance of the line */
    dy = y2 - y1;    /* The vertical distance of the line */
    dxabs = abs(dx); /* The absolute horizontal distance of the line */
    dyabs = abs(dy); /* The absolute vertical distance of the line */
    sdx = sgn(dx);   /* The sign of the horizontal distance of the line */
    sdy = sgn(dy);   /* The sign of the vertical distance of the line */
    x = dyabs >> 1;  /* dyabs / 2 - Horizontal error accumulator */
    y = dxabs >> 1;  /* dxabs / 2 - Vertical error accumulator */
    px = x1;         /* Current x pixel position */
    py = y1;         /* Current y pixel position */

    pixel_t *p = pixel_create(px, py, color);
    pixel_draw(p);
    pixel_destroy(p);

    if (dxabs >= dyabs) /* The line is more horizontal than vertical  */
    {
        for (i = 0 ; i < dxabs ; i++)
        {
            y += dyabs;         /* Add the error to the accumulator */

            if (y >= dxabs)     /* Should we move on the y axis? */
            {
                y -= dxabs;     /* Remove dx from the accumulator to start "fresh" for the next pixel */
                py += sdy;      /* Move 1px in the correct vertical direction */
            }

            px += sdx;          /* Move 1px in the correct horizontal direction */

            pixel_t *p = pixel_create(px, py, color);
            pixel_draw(p);
            pixel_destroy(p);
        }
    }
    else /* The line is more vertical than horizontal  */
    {
        for (i = 0 ; i < dyabs ; i++)
        {
            x += dxabs;

            if (x >= dyabs)
            {
                x -= dyabs;
                px += sdx;
            }

            py += sdy;

            pixel_t *p = pixel_create(px, py, color);
            pixel_draw(p);
            pixel_destroy(p);
        }
    }

}



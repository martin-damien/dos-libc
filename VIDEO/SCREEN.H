#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

#define SCREEN_VIDEO_INT       0x10        /* the BIOS video interrupt */
#define SCREEN_WRITE_DOT       0x0C        /* BIOS function to plot a pixel */
#define SCREEN_SET_MODE        0x00        /* BIOS function to set the video mode */
#define SCREEN_MODE_256_COLORS 0x13        /* use to set 256-color mode */
#define SCREEN_MODE_TEXT       0x03        /* use to set 80x25 text mode */
#define SCREEN_WIDTH           320         /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT          200         /* height in pixels of mode 0x13 */
#define SCREEN_NUM_COLORS      256         /* number of colors in mode 0x13 */

/* pointer to the video memory */
extern uint8_t *VGA;

/* pointer to the 18.2hz system clock */
extern uint16_t *video_clock;

/*
 * Init video
 *
 * MUST BE CALLED BEFORE DOING ANYTHING IN VIDEO
 *
 * It must be called to handle DPMI when using DJGPP's CGG instead of OpenWatcom.
 */
void screen_init();

/*
 * Stop video
 *
 * MUST BE CALLED BEFORE ENDING APPLICATION
 *
 * It resets every things set up by video_init()
 */
void screen_restore();

void video_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);

#endif

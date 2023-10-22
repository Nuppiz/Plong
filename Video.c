#include "Incl_std.h"
#include "Video.h"

/* Video mode functions */

uint8_t *VGA=(uint8_t *)0xA0000000L;        /* this points to video memory. */
uint8_t far screen_buf [64000];             // Double screen buffer

void setVideoMode(uint8_t mode)
{
    union REGS regs;

    regs.h.ah = SET_MODE;
    regs.h.al = mode;
    int86(VIDEO_INT, &regs, &regs);
}

void render()
{     
    // copy off-screen buffer to VGA memory
    memcpy(VGA, screen_buf, SCREEN_SIZE);

    // clear off-screen buffer so the screen updates properly
    _fmemset(screen_buf, 0, SCREEN_SIZE);
}

void renderWithoutClear()
{     
    // copy off-screen buffer to VGA memory
    memcpy(VGA, screen_buf, SCREEN_SIZE);
}
/*
 * Frame_Buffer.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include "FrameBuffer.h"
#include <stdbool.h>
#include <stdint.h>

frame_buff_t fb;

void FB_printToFrameBuff(uint8_t ch)
{
  fb.buffer[fb.index] = ch;
  fb.index = (fb.index + 1) % FB_SIZE;
}

void FB_setFrameBuffIndex(uint16_t index)
{
  if (index > FB_SIZE)
  {
    return;
  }
  fb.index = index;
}

void FB_clearFrame(void)
{
  for(uint16_t i = 1; i <= FB_SIZE; i++)
  {
    fb.buffer[i] = 0;
  }
  fb.index = 1;
}

void FB_sendFrame(void)
{
  fb.buffer[0] = 0x40;
  SSD1306_FlushFrame(fb.buffer);
}


void FB_sendblock(void)
{
  for(uint16_t i = 1; i < 129*4; i++)
    {
      fb.buffer[i] = 0xff;
    }
  FB_sendFrame();
  fb.index = 1;
}




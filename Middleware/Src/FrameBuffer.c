/*
 * Frame_Buffer.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include "FrameBuffer.h"

static frame_buff_t fb;


void FB_printToFrameBuff(uint8_t ch)
{
  fb.buffer[fb.index] = ch;

  fb.index++;
  if(fb.index > FB_SIZE)
  {
    fb.index = FB_DATA_START;
  }
}

void FB_setFrameBuffIndex(uint16_t index)
{
  if (index <= FB_DATA_START && index > FB_SIZE)
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
  fb.index = FB_DATA_START;
}

void FB_sendFrame(void)
{
  fb.buffer[0] = DISP_DATA_CMD;
  SSD1306_FlushFrame(fb.buffer);
}





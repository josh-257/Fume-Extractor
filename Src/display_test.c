/*
 * display_test.c
 *
 *  Created on: 3 Sept 2026
 *      Author: joshb
 */



#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "FanControl.h"
#include "Sensor.h"
#include "Graphics.h"
#include "BSP.h"
#include "Driver_SSD1306.h"
#include "FrameBuffer.h"

void delay(uint32_t u_sec)
{
  for(uint32_t i = 0; i < u_sec; i++);
}

int main(void)
{
  BSP_init();

  SSD1306_displayInit();

  delay(50);

  GFX_clearFrame();
  GFX_setCursor(0, 0);
  GFX_drawString((uint8_t*)"FUMES!");
  GFX_setCursor(0, 1);
  GFX_drawString((uint8_t*)"FUMES!");
  GFX_sendFrame();

  while(1);
}

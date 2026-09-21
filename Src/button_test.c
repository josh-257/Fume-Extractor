/*
 * button_test.c
 *
 *  Created on: 8 Sept 2026
 *      Author: joshb
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Sensor.h"

#include "Graphics.h"

#include "BSP.h"
#include "Driver_GPIO.h"

#define DELAY_MS 0x3E80

/*********************************This is needed for using SWV printf**************************/

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        ITM_SendChar((*ptr++));
    }
    return len;
}
/**********************************************************************************************/
volatile bool btnPressed = false;
volatile uint32_t millis;

bool debounceButton(void);

void delay(uint32_t u_sec)
{
  for(uint32_t i = 0; i < u_sec; i++);
}


void setup(void)
{
  BSP_init();
//
//  SSD1306_displayInit();
//  delay(50);
//  SGP30_sensorInit();

  SysTick_Config(DELAY_MS);
//
//  FC_fanInit();
}

int main(void)
{
  setup();


  for(;;)
  {
    if(btnPressed)
    {
      btnPressed = false;
      printf("Pressed\n");
    }
  }
}


void SysTick_Handler(void)
{
  millis++;


    if(debounceButton())
    {
      btnPressed = true;
    }

}

bool debounceButton(void)
{
  static uint16_t State = 0;  // Current debounce status
  State = (State << 1) | !BSP_ButtonPressed() | 0xe000;
  if (State == 0xf000)
  {
    return true;
  }
  return false;
}



/*
 * PWM_test.c
 *
 *  Created on: 2 Sept 2026
 *      Author: joshb
 */


#include "stm32f407xx.h"
#include "BSP_Motor.h"
#include "BSP_I2C_ADT.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  Clock_Init();
  PWM_GPIOInits();
  PWM_Init();

  while(1);
}

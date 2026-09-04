/*
 * Motor.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include "BSP_Motor.h"

void PWM_GPIOInits(void)
{
  GPIO_Handle_t PWMPin;
  PWMPin.pGPIOx = GPIOB;
  PWMPin.GPIO_Config.PinNumber = 0;
  PWMPin.GPIO_Config.PinMode = GPIO_MODE_ALTFN;
  PWMPin.GPIO_Config.PinOPType = GPIO_OP_TYPE_PP;
  PWMPin.GPIO_Config.AltFunMode = 2;
  PWMPin.GPIO_Config.PinSpeed = GPIO_SPEED_HIGH;
  GPIO_Init(&PWMPin);
}

void PWM_SetMotorSpeed(uint8_t speed)
{
  PWM_SetDutyCycle(speed);
}

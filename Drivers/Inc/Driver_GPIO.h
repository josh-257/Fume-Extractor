/*
 * Driver_GPIO.h
 *
 *  Created on: 11 Aug 2026
 *      Author: joshb
 */

#ifndef INC_DRIVER_GPIO_H_
#define INC_DRIVER_GPIO_H_

#include <stdint.h>

//Configuration structure for GPIO pin
typedef struct{
  uint8_t GPIO_PinNumber;
  uint8_t GPIO_PinMode;
  uint8_t GPIO_PinSpeed;
  uint8_t GPIO_PinPuPdControl;
  uint8_t GPIO_PinOPType;
  uint8_t GPIO_AltFunMode;
}GPIO_PinConfig_t;

//Handle structure for GPIO pin
typedef struct{
  GPIO_RegDef_t *pGPIOx;
  GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

void GPIO_Init();

void GPIO_DeInit();



#endif /* INC_DRIVER_GPIO_H_ */

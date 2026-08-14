/*
 * Driver_EXTI.h
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */

#ifndef INC_DRIVER_EXTI_H_
#define INC_DRIVER_EXTI_H_

#include "mcu.h"

typedef struct{
  uint8_t PinNumber;
  uint8_t Port; //Use macros below to select port (eg. EXTI_PORT_A)
  uint8_t EdgeDetection;
}EXTI_Config_t;

//Macros to define Port
#define EXTI_PORT_A      0
#define EXTI_PORT_B      1
#define EXTI_PORT_C      2
#define EXTI_PORT_D      3
#define EXTI_PORT_E      4
#define EXTI_PORT_F      5
#define EXTI_PORT_G      6
#define EXTI_PORT_H      7

// Macros for trigger edges
#define EXTI_TRIGGER_RISING     0
#define EXTI_TRIGGER_FALLING    1
#define EXTI_TRIGGER_BOTH       2



/***************************************************************************
 * @brief
 * @param pEXTIConfig: Pointer to config structure containing user defined
 *        settings.
 */
void EXTI_Init(EXTI_Config_t *pEXTIConfig);
void EXTI_ClearPendingBit(uint8_t pinNumber);

#endif /* INC_DRIVER_EXTI_H_ */

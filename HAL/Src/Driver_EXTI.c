/*
 * Driver_EXTI.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include "Driver_EXTI.h"


void EXTI_Init(EXTI_Config_t *pEXTIConfig)
{
  //Select correct SYSCFG_EXTI control register
  uint8_t index = pEXTIConfig->PinNumber / 4;
  uint8_t shift_amount = pEXTIConfig->PinNumber % 4;
  //Route the GPIO port to the control register
  SYSCFG->EXTICR[index] &= ~(0xF << (4 * shift_amount));
  SYSCFG->EXTICR[index] |= (pEXTIConfig->Port << (4 * shift_amount));
  //Enable interrupt
  EXTI_ToggleInterrupt(pEXTIConfig->PinNumber, ENABLE);

  if(pEXTIConfig->EdgeDetection == EXTI_TRIGGER_FALLING)
  {
    EXTI->FTSR |= (1 << pEXTIConfig->PinNumber);
    EXTI->RTSR &= ~(1 << pEXTIConfig->PinNumber);
  }
  else if(pEXTIConfig->EdgeDetection == EXTI_TRIGGER_RISING)
  {
    EXTI->RTSR |= (1 << pEXTIConfig->PinNumber);
    EXTI->FTSR &= ~(1 << pEXTIConfig->PinNumber);
  }
  else if(pEXTIConfig->EdgeDetection == EXTI_TRIGGER_BOTH)
  {
    EXTI->RTSR |= (1 << pEXTIConfig->PinNumber);
    EXTI->FTSR |= (1 << pEXTIConfig->PinNumber);
  }
}


void EXTI_clearPendingBit(uint8_t pinNumber)
{
  EXTI->PR |= (1 << pinNumber);
}

void EXTI_ToggleInterrupt(uint8_t pinNumber, uint8_t EnorDi)
{
  if(EnorDi == ENABLE)
  {
    EXTI->IMR |= 1 << pinNumber;
  }
  else
  {
    EXTI->IMR &= ~(1 << pinNumber);
  }
}

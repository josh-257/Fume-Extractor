/*
 * Driver_GPIO.h
 *
 *  Created on: 11 Aug 2026
 *      Author: joshb
 */

#ifndef INC_DRIVER_GPIO_H_
#define INC_DRIVER_GPIO_H_

#include <stdint.h>
#include "mcu.h"

//Configuration structure for GPIO pin
typedef struct{
  uint8_t PinNumber;
  uint8_t PinMode;
  uint8_t PinSpeed;
  uint8_t PinPuPdControl;
  uint8_t PinOPType;
  uint8_t AltFunMode;
}GPIO_PinConfig_t;

//Handle structure for GPIO pin
typedef struct{
  GPIO_TypeDef *pGPIOx; //Holds base address of port to which the pin belongs to
  GPIO_PinConfig_t GPIO_Config; // Holds GPIO config settings
}GPIO_Handle_t;


//Pin modes
#define GPIO_MODE_IN          0
#define GPIO_MODE_OUT         1
#define GPIO_MODE_ALTFN       2
#define GPIO_MODE_ANALOG      3

//Macros to reset GPIOx peripherals
#define GPIOA_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));} while(0)
#define GPIOB_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));} while(0)
#define GPIOC_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));} while(0)
#define GPIOD_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));} while(0)
#define GPIOE_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));} while(0)
#define GPIOF_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5));} while(0)
#define GPIOG_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6));} while(0)
#define GPIOH_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));} while(0)
#define GPIOI_REG_RESET()     do{(RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8));} while(0)

//Clock disable macros for GPIOx peripherals
#define GPIOA_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()       (RCC->AHB1ENR &= ~(1 << 8))

/*******************************API's supported by this driver*******************************/

/***************************************************************************
 * @brief   Configures GPIO pin with user-defined GPIO handle structure.
 * @param   pGPIOHandle: Pointer to handle structure containing user-defined
 *          configuration.
 */
void GPIO_Init(GPIO_Handle_t *pGPIOx);

/***************************************************************************
 * @brief   Resets all registers in corresponding GPIO port.
 * @param   pGPIOHandle: Pointer to handle structure containing user-defined
 *          configuration.
 * @note    This function resets the physical port but not the handle
 *          structure.
 */
void GPIO_DeInit(GPIO_TypeDef *pGPIOx);

/***************************************************************************
 * @brief   Returns the current value held in the input data register of
 *          the specified GPIO pin.
 * @param   pGPIOx: Pointer to register definition structure
 *          containing memory address of chosen GPIO port.
 * @param   PinNumber: GPIO_PIN_NO_0 - GPIO_PIN_NO_15.
 * @retval  The value of the input data register.
 */
uint8_t GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber);

/***************************************************************************
 * @brief   Returns the current values held in the input data register of
 *          the specified GPIO port.
 * @param   pGPIOx: Pointer to register definition structure
 *          containing memory address of chosen GPIO port.
 * @retval  The value of the input data register across
 *          all pins for specific port.
 */
uint16_t GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx);

/***************************************************************************
 * @brief   Writes specified value (either SET or RESET) to chosen GPIO pin.
 * @param   pGPIOx: Pointer to register definition structure
 *          containing memory address of chosen GPIO port.
 * @param   PinNumber: GPIO_PIN_NO_0 - GPIO_PIN_NO_15.
 * @param   value: Either SET(1) or RESET(0).
 */
void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t value);

/***************************************************************************
 * @brief   Writes specified 16 bit value to set and reset
 *          register of chosen GPIO port.
 * @param   pGPIOx: Pointer to register definition structure
 *          containing memory address of chosen GPIO port.
 * @param   value: Holding set values (0-8 bits) and
 *          reset values (bits 8-15) for each pin of the GPIO port.
 */
void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint16_t value);

/***************************************************************************
 * @brief   Toggles state of specified GPIO pin.
 * @param   pGPIOx: Pointer to register definition structure
 *          containing memory address of chosen GPIO port.
 * @param   PinNumber: GPIO_PIN_NO_0 - GPIO_PIN_NO_15.
 */
void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber);


#endif /* INC_DRIVER_GPIO_H_ */

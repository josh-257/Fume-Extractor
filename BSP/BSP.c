/*
 * BSP.c
 *
 *  Created on: 7 Sept 2026
 *      Author: joshb
 */

#include "BSP.h"

//Private functions for BSP init
static void I2C1_GPIOInits(void);
static void PWM_GPIOInits(void);
static void button_GPIOInits(void);
static void Clock_init(void);
static void I2C1_inits(void);
static void button_EXTIInits(void);

static I2C_Handle_t I2CHandle;
static GPIO_Handle_t btnPin;

void BSP_init(void)
{
    Clock_init();

    button_GPIOInits();

    I2C1_GPIOInits();
    I2C1_inits();

    PWM_GPIOInits();
    NVIC_EnableIRQ(EXTI1_IRQn);
}

void BSP_sendData(const uint8_t *pTxBuffer, uint32_t len, uint8_t slave_address, uint8_t Sr)
{
  I2C_MasterSendData(&I2CHandle, pTxBuffer, len, slave_address, Sr);
}

void BSP_receiveData(uint8_t *pRxBuffer, uint32_t len, uint8_t slave_address, uint8_t Sr)
{
  I2C_MasterReceiveData(&I2CHandle, pRxBuffer, len, slave_address, Sr);
}

uint8_t BSP_ButtonPressed(void)
{
  return GPIO_ReadFromInputPin(btnPin.pGPIOx, BUTTON_PIN_NO);
}

static void I2C1_GPIOInits(void)
{
  GPIO_Handle_t I2CPins;

  I2CPins.pGPIOx = I2C_GPIO_PORT;
  I2CPins.GPIO_Config.PinMode = I2C_PIN_MODE;
  I2CPins.GPIO_Config.PinOPType = I2C_PIN_OP_TYPE;
  I2CPins.GPIO_Config.PinPuPdControl = I2C_PIN_PUPD_SETTING;
  I2CPins.GPIO_Config.AltFunMode = I2C_PIN_ALT_FUN_MODE;
  I2CPins.GPIO_Config.PinSpeed = I2C_PIN_SPEED;

  // SCL (PB6)
  I2CPins.GPIO_Config.PinNumber = I2C_SCL_PIN_NO;
  GPIO_Init(&I2CPins);

  // SDA (PB7)
  I2CPins.GPIO_Config.PinNumber = I2C_SDA_PIN_NO;
  GPIO_Init(&I2CPins);
}

static void PWM_GPIOInits(void)
{
  GPIO_Handle_t PWMPin;

  PWMPin.pGPIOx = PWM_GPIO_PORT;
  PWMPin.GPIO_Config.PinNumber = PWM_PIN_NO;
  PWMPin.GPIO_Config.PinMode = PWM_PIN_MODE;
  PWMPin.GPIO_Config.PinOPType = PWM_PIN_OP_TYPE;
  PWMPin.GPIO_Config.AltFunMode = PWM_PIN_ALT_FUN_MODE;
  PWMPin.GPIO_Config.PinSpeed = PWM_PIN_SPEED;
  GPIO_Init(&PWMPin);
}

static void button_GPIOInits(void)
{
  btnPin.pGPIOx = BUTTON_GPIO_PORT;
  btnPin.GPIO_Config.PinNumber = BUTTON_PIN_NO;
  btnPin.GPIO_Config.PinMode = BUTTON_PIN_MODE;
  btnPin.GPIO_Config.PinPuPdControl = BUTTON_PUPD_SETTING;
  GPIO_Init(&btnPin);
}

static void Clock_init(void)
{
  GPIOD_PCLK_EN();
  GPIOB_PCLK_EN();
  GPIOA_PCLK_EN();
  SYSCFG_PCLK_EN();
  I2C1_PCLK_EN();
  TIM3_PCLK_EN();
}

static void I2C1_inits(void)
{
  I2CHandle.pI2Cx = I2C_PERI_ADDR;
  I2CHandle.I2C_Config.I2C_ACKControl = I2C_ACKCONTROL;
  I2CHandle.I2C_Config.I2C_DeviceAddress = I2C_DEVICE_ADDR;
  I2CHandle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED;

  I2C_Init(&I2CHandle);
  I2C_PeripheralControl(I2CHandle.pI2Cx, ENABLE);
}

static void button_EXTIInits(void)
{
  EXTI_Config_t btn;
  btn.Port = BUTTON_EXTI_PORT;
  btn.PinNumber = BUTTON_PIN_NO;
  btn.EdgeDetection = BUTTON_EDGE_DETECT;
  EXTI_Init(&btn);
}






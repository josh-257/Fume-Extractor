/*
 * BSP_I2C_Private.c
 *
 *  Created on: 16 Aug 2026
 *      Author: joshb
 */


#include <BSP_I2C_ADT.h>
#include "Driver_I2C.h"
#include "Driver_GPIO.h"

#define MY_ADDR 0x61

struct I2C_type {
  I2C_Handle_t I2C_Handle;
};

static struct I2C_type private_handle;

I2C_ADT BSP_GetI2CHandle(void)
{
  return &private_handle;
}

static void I2C1_GPIOInits(void)
{
  GPIO_Handle_t I2CPins;
  I2CPins.pGPIOx = GPIOB;
  I2CPins.GPIO_Config.PinMode = GPIO_MODE_ALTFN;
  I2CPins.GPIO_Config.PinOPType = GPIO_OP_TYPE_OD;
  I2CPins.GPIO_Config.PinPuPdControl = GPIO_PIN_NOPUPD;
  I2CPins.GPIO_Config.AltFunMode = 4;
  I2CPins.GPIO_Config.PinSpeed = GPIO_SPEED_HIGH;

  // SCL (PB6)
  I2CPins.GPIO_Config.PinNumber = 6;
  GPIO_Init(&I2CPins);

  // SDA (PB7)
  I2CPins.GPIO_Config.PinNumber = 7;
  GPIO_Init(&I2CPins);
}


void Clock_Init(void)
{
  GPIOD_PCLK_EN();
  GPIOB_PCLK_EN();
  GPIOA_PCLK_EN();
  SYSCFG_PCLK_EN();
  I2C1_PCLK_EN();
  TIM3_PCLK_EN();

}

void I2C1_Inits(void)
{
  Clock_Init();
  I2C1_GPIOInits();

  private_handle.I2C_Handle.pI2Cx = I2C1;
  private_handle.I2C_Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
  private_handle.I2C_Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
  private_handle.I2C_Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
  private_handle.I2C_Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

  I2C_Init(&(private_handle.I2C_Handle));
  I2C_PeripheralControl(private_handle.I2C_Handle.pI2Cx, ENABLE);
}

void BSP_SendData(I2C_ADT private_handle, const uint8_t *pTxBuffer, uint32_t len, uint8_t slave_address, uint8_t Sr)
{
  I2C_Handle_t data_handle = private_handle->I2C_Handle;

  I2C_MasterSendData(&data_handle, pTxBuffer, len, slave_address, Sr);
}

void BSP_ReceiveData(I2C_ADT private_handle, uint8_t *pRxBuffer, uint32_t len, uint8_t slave_address, uint8_t Sr)
{
  I2C_Handle_t data_handle = private_handle->I2C_Handle;

  I2C_MasterReceiveData(&data_handle, pRxBuffer, len, slave_address, Sr);
}

void I2C_Reset(void)
{
  I2C_Handle_t data_handle = private_handle.I2C_Handle;

  uint8_t cmd = 0x06;

  I2C_MasterSendData(&data_handle, &cmd, 1, 0x00, DISABLE);
}



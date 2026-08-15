/*
 * Display.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include "stm32f407xx.h"
#include "Display.h"


void Clock_Init(void)
{
  GPIOD_PCLK_EN();
  GPIOB_PCLK_EN();
  GPIOA_PCLK_EN();
  SYSCFG_PCLK_EN();
  I2C1_PCLK_EN();

}

void Display_Init(I2C_Handle_t *pI2CHandle)
{
  static const uint8_t displayInitCmds[] = {
      OLED_CONTROL_BYTE_COMMAND,
      OLED_CMD_DISPLAY_OFF,
      OLED_CMD_SET_MUX_RATIO,           OLED_ARG_MUX_64_ROWS,
      OLED_CMD_SET_DISPLAY_OFFSET,      OLED_ARG_OFFSET_NONE,
      OLED_CMD_SET_START_LINE_0,
      OLED_CMD_SET_ADDRESSING_MODE,     OLED_ARG_ADDRESSING_HORIZONTAL,
      OLED_CMD_SET_SEG_REMAP,
      OLED_CMD_SET_COM_REMAP,
      OLED_CMD_SET_COM_PINS,            OLED_ARG_COM_ALTERNATIVE,
      OLED_CMD_SET_CONTRAST,            OLED_ARG_CONTRAST_50_PERCENT,
      OLED_CMD_RESUME_RAM_OUTPUT,
      OLED_CMD_SET_NORMAL_COLOR,
      OLED_CMD_SET_CLOCK_DIVIDE,        OLED_ARG_CLOCK_DIVIDE_DEFAULT,
      OLED_CMD_SET_CHARGE_PUMP,         OLED_ARG_CHARGE_PUMP_ENABLE,
      OLED_CMD_DISPLAY_ON
  };

  I2C_MasterSendData(pI2CHandle, displayInitCmds, DISPLAY_INIT_CMDS_LEN, OLED_SLAVE_ADDRESS, I2C_SR_DI);
}

void Display_SetCursor(I2C_Handle_t *pI2CHandle, uint8_t col_start, uint8_t page_start)
{
  if(col_start > 127)
  {
    col_start = 127;
  }

  if(col_start < 0)
  {
    col_start = 0;
  }

  if(page_start > 7)
  {
    page_start = 7;
  }

  if(page_start < 0)
  {
    page_start = 0;
  }
  //Array to store sequence of commands
  uint8_t cmd[SET_CURSOR_CMD_LEN];

  cmd[0] = OLED_CONTROL_BYTE_COMMAND;
  cmd[1] = OLED_CMD_SET_COLOUMN_ADDR;
  cmd[2] = col_start;
  cmd[3] = OLED_COL_END;
  cmd[4] = OLED_CMD_SET_PAGE_ADDR;
  cmd[5] = page_start;
  cmd[6] = OLED_PAGE_END;

  //Send off all commands in one go
  I2C_MasterSendData(pI2CHandle, cmd, SET_CURSOR_CMD_LEN, OLED_SLAVE_ADDRESS, I2C_SR_DI);
}

void Display_WriteChar(I2C_Handle_t *pI2CHandle, uint8_t data)
{
  uint8_t cmd[2];
  cmd[0] = OLED_CONTROL_BYTE_DATA;
  cmd[1] = data;
  I2C_MasterSendData(pI2CHandle, cmd, 2, OLED_SLAVE_ADDRESS,  I2C_SR_DI);
}

void Display_Clear(I2C_Handle_t *pI2CHandle)
{

    Display_SetCursor(pI2CHandle, 0, 0);

    uint8_t frame_buffer[1025];
    frame_buffer[0] = 0x40;

    for(int i = 1; i <= 1024; i++)
    {
        frame_buffer[i] = 0x00;
    }

    I2C_MasterSendData(pI2CHandle, frame_buffer, FRAME_BUFFER_SIZE, OLED_SLAVE_ADDRESS, I2C_SR_DI);
}

//
//void Display_WriteCmd(I2C_Handle_t pI2CHandle, uint8_t cmd)
//{
//
//}

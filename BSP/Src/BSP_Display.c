/*
 * Display.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include "BSP_I2C_ADT.h"
#include <stdbool.h>
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "BSP_Display.h"

void BSP_DisplayInit(void)
{
  I2C_ADT BSP_I2CHandle = BSP_GetI2CHandle();

  static const uint8_t displayInitCmds[] = {

       0x00,  // I2C Control Byte: Tells SSD1306 that all following bytes are COMMANDS
       0xAE,  // Display OFF (Sleep Mode)
       0xD5,  // Set Display Clock Divide Ratio / Oscillator Frequency
       0x80,  // Suggested ratio (default reset value)
       0xA8,  // Set Multiplex Ratio
       0x3F,  // 63 decimal = 64 rows (128x64 resolution layout)
       0xD3,  // Set Display Offset
       0x00,  // 0 offset (no vertical shifting)
       0x40,  // Set Display Start Line to 0
       0x8D,  // Charge Pump Command
       0x14,  // Enable internal charge pump (Crucial for 3.3V/5V microcontroller power)
       0x20,  // Set Memory Addressing Mode
       0x00,  // Horizontal Addressing Mode (easiest for linear framebuffers)
       0xA1,  // Set Segment Re-map (X-Axis Flip / Right-side up)
       0xC8,  // Set COM Output Scan Direction (Y-Axis Flip / Right-side up)
       0xDA,  // Set COM Pins Hardware Configuration
       0x12,  // Alternative COM pin configuration (Required for 128x64)
       0x81,  // Set Contrast Control (Brightness)
       0xCF,  // Set contrast value (0x00 to 0xFF)
      0xD9,  // Set Pre-charge Period
      0xF1,  // Phase 1: 1 DCLK, Phase 2: 15 DCLKs
      0xDB,  // Set VCOMH Deselect Level
      0x40,  // ~0.77 x Vcc
       0xA4,  // Entire Display ON (Resume to RAM content)
       0xA6,  // Set Normal Display (Not inverted. 1 = Pixel On, 0 = Pixel Off)
       0x2E,  // Deactivate Scroll (Safety reset)
  };

  BSP_SendData(BSP_I2CHandle, displayInitCmds, DISPLAY_INIT_CMDS_LEN, OLED_SLAVE_ADDRESS, DISABLE);

  static uint8_t buffer[1025];
  buffer[0] = 0x40;

  BSP_SendData(BSP_I2CHandle, buffer, 1025, OLED_SLAVE_ADDRESS, DISABLE);

  uint8_t start[] = {0x00, 0xAF};
  BSP_SendData(BSP_I2CHandle, start, 2, OLED_SLAVE_ADDRESS, DISABLE);
}

void BSP_FlushFrame(uint8_t frame[])
{
  I2C_ADT BSP_I2CHandle = BSP_GetI2CHandle();
  BSP_SendData(BSP_I2CHandle, frame, FRAME_BUFFER_SIZE, OLED_SLAVE_ADDRESS, DISABLE);
}

void BSP_ResetCursor(void)
{
  I2C_ADT BSP_I2CHandle = BSP_GetI2CHandle();
  //Array to store sequence of commands
  uint8_t cmd[SET_CURSOR_CMD_LEN];

  cmd[0] = OLED_CONTROL_BYTE_COMMAND;
  cmd[1] = OLED_CMD_SET_COLOUMN_ADDR;
  cmd[2] = 0;
  cmd[3] = OLED_COL_END;

  cmd[4] = OLED_CONTROL_BYTE_COMMAND;
  cmd[5] = OLED_CMD_SET_PAGE_ADDR;
  cmd[6] = 0;
  cmd[7] = OLED_PAGE_END;

  //Send off all commands in one go
  BSP_SendData(BSP_I2CHandle, cmd, SET_CURSOR_CMD_LEN, OLED_SLAVE_ADDRESS, DISABLE);
}






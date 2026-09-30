/*
 * Display.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include "Driver_SSD1306.h"

void delay_u(uint32_t u_sec)
{
  for(uint32_t i = 0; i < u_sec; i++);
}

void SSD1306_displayInit(void)
{
  const uint8_t displayInitCmds[] = {

       OLED_CONTROL_BYTE_COMMAND,
       0xA8, 0x3F, //Set Mux
       0xD3, 0x00, //Display Offset
       0x40, //Display start line
       0xA1, //Display orientation (Landscape)
       0xC8,
       0xDA, 0x12, //COM pin hardware config
       0x81, 0x7F, //Screen contrast
       0xA4,
       0xA6,
       0xD5, 0x80, //Oscillator frequency
       0x8D, 0x14, //Enable charge pump regulator
       0xAF
  };

  BSP_sendData(displayInitCmds, DISPLAY_INIT_CMDS_LEN, OLED_SLAVE_ADDRESS, DISABLE);
}

void SSD1306_FlushFrame(uint8_t *frame)
{
  SSD1306_resetCursor();
  delay_u(100);

  BSP_sendData(frame, FRAME_BUFFER_SIZE, OLED_SLAVE_ADDRESS, DISABLE);
}

void SSD1306_resetCursor(void)
{

  //Temporary buffer to store commands
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
  BSP_sendData(cmd, SET_CURSOR_CMD_LEN, OLED_SLAVE_ADDRESS, DISABLE);
}






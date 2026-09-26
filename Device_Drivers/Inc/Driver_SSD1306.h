/*
 * Display.h
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */

#ifndef INC_DRIVER_SSD1306_H_
#define INC_DRIVER_SSD1306_H_

#include "BSP.h"
#include <stddef.h>
#include <stdint.h>

//Device address
#define OLED_SLAVE_ADDRESS              0x3C

#define OLED_CONTROL_BYTE_COMMAND       0x00
#define OLED_CONTROL_BYTE_DATA          0x40

#define OLED_CMD_SET_COLOUMN_ADDR       0x21
#define OLED_CMD_SET_PAGE_ADDR          0x22

#define OLED_COL_END                    0x7F
#define OLED_PAGE_END                   0x07

#define SET_CURSOR_CMD_LEN              0x08
#define DISPLAY_INIT_CMDS_LEN           (sizeof(displayInitCmds) / sizeof(displayInitCmds[0]))

#define FRAME_BUFFER_SIZE               1024

/*****************************************************
 * @brief   Performs all commands to set up the display
 *          ready for the first frame. The display is
 *          setup in horizontal mode.
 */
void SSD1306_displayInit(void);

/*****************************************************
 * @brief Resets display cursor back to 0 before sending
 *        frame buffer to display.
 * @param frame: Pointer frame buffer.
 * @note  Contains a 12 micro second delay after set cursor
 *        command before sending frame buffer.
 */
void SSD1306_FlushFrame(uint8_t *frame);

/*****************************************************
 * @brief Resets display vertical and horizontal cursor
 *        to 0.
 */
void SSD1306_resetCursor(void);

#endif /* INC_DRIVER_SSD1306_H_ */

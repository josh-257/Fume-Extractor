/*
 * Display.h
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */

#ifndef INC_BSP_DISPLAY_H_
#define INC_BSP_DISPLAY_H_


#include <stddef.h>
#include <stdint.h>

// --- SSD1306 COMMAND REGISTER MACROS ---

//Device address
#define OLED_SLAVE_ADDRESS  0x3C

#define OLED_CONTROL_BYTE_COMMAND       0x00
#define OLED_CONTROL_BYTE_DATA          0x40

// Sleep Mode / Waking
#define OLED_CMD_DISPLAY_OFF            0xAE
#define OLED_CMD_DISPLAY_ON             0xAF

// Hardware Layout / Dimensions
#define OLED_CMD_SET_MUX_RATIO          0xA8
#define OLED_ARG_MUX_64_ROWS            0x3F  // 128x64 screens
#define OLED_ARG_MUX_32_ROWS            0x1F  // 128x32 screens

#define OLED_CMD_SET_DISPLAY_OFFSET     0xD3
#define OLED_ARG_OFFSET_NONE            0x00

#define OLED_CMD_SET_START_LINE_0       0x40  // Base address 0x40 + offset (0-63)

// Screen Orientation / Mirroring
#define OLED_CMD_SET_SEG_NORMAL         0xA0  // Column 0 is mapped to SEG0
#define OLED_CMD_SET_SEG_REMAP          0xA1  // Column 127 is mapped to SEG0 (Horizontal Flip)

#define OLED_CMD_SET_COM_NORMAL         0xC0  // Scan top to bottom
#define OLED_CMD_SET_COM_REMAP          0xC8  // Scan bottom to top (Vertical Flip)

#define OLED_CMD_SET_COM_PINS           0xDA
#define OLED_ARG_COM_ALTERNATIVE        0x02  // Interlaced row wiring layout

// Contrast / Brightness
#define OLED_CMD_SET_CONTRAST           0x81
#define OLED_ARG_CONTRAST_50_PERCENT    0x7F

// Display Output Modes
#define OLED_CMD_RESUME_RAM_OUTPUT      0xA4  // Screen mirrors internal RAM state
#define OLED_CMD_FORCE_ALL_WHITE        0xA5  // Ignores RAM, forces screen white

#define OLED_CMD_SET_NORMAL_COLOR       0xA6  // 1 = White pixel, 0 = Black pixel
#define OLED_CMD_SET_INVERT_COLOR       0xA7  // 1 = Black pixel, 0 = White pixel

// Clock & Timing
#define OLED_CMD_SET_CLOCK_DIVIDE       0xD5
#define OLED_ARG_CLOCK_DIVIDE_DEFAULT   0x80

// Internal Power Generation
#define OLED_CMD_SET_CHARGE_PUMP        0x8D
#define OLED_ARG_CHARGE_PUMP_ENABLE     0x14
#define OLED_ARG_CHARGE_PUMP_DISABLE    0x10

// Addressing Modes
#define OLED_CMD_SET_ADDRESSING_MODE    0x20
#define OLED_ARG_ADDRESSING_HORIZONTAL  0x00

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
void BSP_DisplayInit(void);

void BSP_FlushFrame(uint8_t frame[]);

void BSP_ResetCursor(void);

#endif /* INC_BSP_DISPLAY_H_ */

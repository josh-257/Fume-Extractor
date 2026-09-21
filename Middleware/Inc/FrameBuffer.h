/*
 * Frame_Buffer.h
 *
 *  Created on: 17 Aug 2026
 *      Author: joshb
 */

#ifndef INC_FRAMEBUFFER_H_
#define INC_FRAMEBUFFER_H_

#include <stdbool.h>

#include "Driver_SSD1306.h"
#include <stdint.h>

#define FRAME_WIDTH 128
#define FRAME_PAGES 8
#define FB_SIZE (FRAME_WIDTH * FRAME_PAGES)
#define DISP_DATA_CMD 0x40
#define FB_DATA_START 1 //Index at which the frame buffer data begins

typedef struct {
  uint8_t buffer[FB_SIZE + 1]; //Extra byte to send display data command
  uint16_t index;
}frame_buff_t;

/*****************************************************
 * @brief   Takes 1 byte input and places it into the
 *          frame buffer then increments index ready for
 *          next byte.
 * @param   ch - Character to be placed into frame buffer.
 */
void FB_printToFrameBuff(uint8_t ch);

/*****************************************************
 * @brief   Sets index of frame buffer to parameter given.
 * @param   index: unsigned 16 bit int representing chosen
 *          index of frame buffer.
 */
void FB_setFrameBuffIndex(uint16_t index);

/*****************************************************
 * @brief   Resets all values in frame buffer to zero.
 */
void FB_clearFrame(void);

/*****************************************************
 * @brief   Passes frame buffer to
 *          display device driver.
 */
void FB_sendFrame(void);

#endif /* INC_FRAMEBUFFER_H_ */

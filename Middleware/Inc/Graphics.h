/*
 * Mid_Graphics.h
 *
 *  Created on: 17 Aug 2026
 *      Author: joshb
 */

#ifndef INC_GRAPHICS_H_
#define INC_GRAPHICS_H_

#include "FrameBuffer.h"

#define FONT_WIDTH  8
#define FONT_HEIGHT 8
#define FONT_CHARS  95

/*****************************************************
 * @brief   Inserts a string of text into the frame buffer.
 * @param   pbuffer: Pointer to string to be copied into
 *          frame buffer.
 */
void GFX_drawString(uint8_t *pbuffer);

/*****************************************************
 * @brief   Positions the cursor to the specified line and
 *          coloumn through adjusting the frame buffer index.
 * @param   col: Unsigned int value between 0 - 127 specifying
 *          horizontal position of cursor.
 * @param   line: Unsigned int value between 0 - 7 specifying
 *          vertical position of cursor.
 */
void GFX_setCursor(uint16_t col, uint16_t line);

/*****************************************************
 * @brief   Sends current frame buffer to display via
 *          FB_sendFrame() function.
 */
void GFX_sendFrame(void);

/*****************************************************
 * @brief   Sends a blank frame to display via FB_clearFrame()
 *          function.
 */
void GFX_clearFrame(void);

#endif /* INC_GRAPHICS_H_ */

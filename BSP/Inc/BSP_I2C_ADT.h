/*
 * BSP_I2C_Private.h
 *
 *  Created on: 16 Aug 2026
 *      Author: joshb
 */

#ifndef INC_BSP_I2C_ADT_H_
#define INC_BSP_I2C_ADT_H_

#include <stdint.h>

typedef struct I2C_type *I2C_ADT;

I2C_ADT BSP_GetI2CHandle(void);
void I2C1_Inits(void);
void BSP_SendData(I2C_ADT private_handle, const uint8_t *pTxBuffer, uint32_t len, uint8_t slave_address, uint8_t Sr);

#endif /* INC_BSP_I2C_ADT_H_ */

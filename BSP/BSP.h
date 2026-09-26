/*
 * BSP.h
 *
 *  Created on: 7 Sept 2026
 *      Author: joshb
 */

#ifndef BSP_H_
#define BSP_H_

#include "Driver_GPIO.h"
#include "Driver_I2C.h"
#include "Driver_PWM.h"

#include <stdint.h>

//Button setup - PA1
#define BUTTON_PIN_NO         1
#define BUTTON_GPIO_PORT      GPIOA
#define BUTTON_PIN_MODE       GPIO_MODE_IN
#define BUTTON_PUPD_SETTING   GPIO_PIN_PU

//I2C setup - SCL (PB6), SDA (PB7)
#define I2C_SCL_PIN_NO         6
#define I2C_SDA_PIN_NO         7
#define I2C_GPIO_PORT          GPIOB
#define I2C_PIN_MODE           GPIO_MODE_ALTFN
#define I2C_PIN_OP_TYPE        GPIO_OP_TYPE_OD
#define I2C_PIN_PUPD_SETTING   GPIO_PIN_NOPUPD
#define I2C_PIN_ALT_FUN_MODE   GPIO_AF_AF4
#define I2C_PIN_SPEED          GPIO_SPEED_HIGH

#define I2C_PERI_ADDR          I2C1
#define I2C_ACKCONTROL         I2C_ACK_ENABLE
#define I2C_DEVICE_ADDR        0x61
#define I2C_SCL_SPEED          I2C_SCL_SPEED_SM

//PWM setup - PB0
#define PWM_PIN_NO            0
#define PWM_GPIO_PORT         GPIOB
#define PWM_PIN_MODE          GPIO_MODE_ALTFN
#define PWM_PIN_OP_TYPE       GPIO_OP_TYPE_PP
#define PWM_PIN_ALT_FUN_MODE  GPIO_AF_AF2
#define PWM_PIN_SPEED         GPIO_SPEED_HIGH

/*****************************************************
 * @brief   Initialises required peripheral clocks, GPIO
 *          pins, external interrupts, I2C and PWM peripherals.
 */
void BSP_init(void);

/*****************************************************
 * @brief   Completes a full transmission of I2C bus via
 *          I2C driver API - I2C_MasterSendData() with
 *          pre set I2C handle.
 * @param   pTxBuffer: Pointer to the user data buffer
 *          holding the data to be transmitted.
 * @param   len: Specifies the length (in bytes) of the
 *          transmission.
 * @param   slave_address: 7 bit address of the chosen
 *          slave to send the transmission to.
 * @param   Sr: Option for repeated start condition,
 *          I2C_SR_EN to enable andI2C_SR_DI to disable.
 * @note    This is a blocking function.
 */
void BSP_sendData(const uint8_t *pTxBuffer, uint32_t len, uint8_t slave_address, uint8_t Sr);


/***************************************************************************
  * @brief   Calls I2C driver API I2C_MasterSendData with
 *           pre set I2C handle.
 * @param    pRxBuffer: Pointer to the user receive buffer where the received
 *           data will land.
 * @param    len: Specifies the length (in bytes) of the data to be received.
 * @param    slave_address: 7 bit address of the chosen slave to read data from.
 * @param    Sr: Option for repeated start condition, I2C_SR_EN to enable and
 *           I2C_SR_DI to disable.
 * @note     This is a blocking function.
 */
void BSP_receiveData(uint8_t *pRxBuffer, uint32_t len, uint8_t slave_address, uint8_t Sr);

/**************************************************************
 * @brief   Returns the state of the button. (1 pressed, 0 not pressed)
*/
uint8_t BSP_ButtonPressed(void);

#endif /* BSP_H_ */

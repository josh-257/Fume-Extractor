/*
 * BSP_Motor.h
 *
 *  Created on: 16 Aug 2026
 *      Author: joshb
 */

#ifndef INC_BSP_MOTOR_H_
#define INC_BSP_MOTOR_H_

#include "Driver_PWM.h"
#include "Driver_GPIO.h"

void PWM_GPIOInits(void);
void PWM_SetMotorSpeed(uint8_t speed);

#endif /* INC_BSP_MOTOR_H_ */

/*
 * PWM_Fan.h
 *
 *  Created on: 7 Sept 2026
 *      Author: joshb
 */

#ifndef INC_FANCONTROL_H_
#define INC_FANCONTROL_H_


#include "Driver_PWM.h"

typedef enum {
  FAN_STOP = 0,
  FAN_LOW = 25,
  FAN_HIGH = 100
} FanSetting_t;

/*****************************************************
 * @brief   Converts speed setting into a PWM output
 *          calling driver API - PWM_setdutyCycle().
 * @param   setting - Enum of type FanSetting_t
 *          containing desired duty cycle.
 */
void FC_setFanSpeed(FanSetting_t setting);

/*****************************************************
 * @brief   Calls PWM_init().
 */
void FC_fanInit(void);

#endif /* INC_FANCONTROL_H_ */

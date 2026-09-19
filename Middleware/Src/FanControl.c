/*
 * Mid_PWM_Fan.c
 *
 *  Created on: 7 Sept 2026
 *      Author: joshb
 */
#include "FanControl.h"

void FC_setFanSpeed(FanSetting_t setting)
{
  PWM_SetDutyCycle(setting);
}

void FC_fanInit(void)
{
  PWM_Init();
}

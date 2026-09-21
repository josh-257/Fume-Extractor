/*
 * Mid_Sensor.h
 *
 *  Created on: 31 Aug 2026
 *      Author: joshb
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include <stdint.h>

#include "Driver_SGP30.h"

/*****************************************************
 * @brief   Returns an array of 2 uint16_t variables representing
 *          the TVOC and ECO2 readings.
 */
uint16_t *SNS_getSensorData(void);


#endif /* INC_SENSOR_H_ */

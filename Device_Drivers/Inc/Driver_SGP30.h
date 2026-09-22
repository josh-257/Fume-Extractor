/*
 * Driver_SGP30.h
 *
 *  Created on: 16 Aug 2026
 *      Author: joshb
 */

#ifndef INC_DRIVER_SGP30_H_
#define INC_DRIVER_SGP30_H_

#include "BSP.h"

#define SENSOR_SLAVE_ADDR           0x58

#define SENSOR_INIT_CMD_MSB         0x20
#define SENSOR_INIT_CMD_LSB         0x03
#define SENSOR_INIT_CMD_LEN         (sizeof(cmds)/sizeof(cmds[0]))

#define SENSOR_MEASURE_CMD_MSB      0x20
#define SENSOR_MEASURE_CMD_LSB      0x08
#define SENSOR_MEASURE_CMD_LEN      (sizeof(cmds)/sizeof(cmds[0]))

#define SENS_DATA_LEN 2

/*****************************************************
 * @brief Retrieves the sensor reading.
 * @note  This function has a delay of 12ms to wait for
 *        the sensing device.
 */
uint8_t *SGP30_getSensorReading(void);

/*****************************************************
 * @brief Sends init cmd to device.
 */
void SGP30_sensorInit(void);

#endif /* INC_DRIVER_SGP30_H_ */

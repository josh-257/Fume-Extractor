/*
 * BSP_Sensor.h
 *
 *  Created on: 16 Aug 2026
 *      Author: joshb
 */

#ifndef INC_BSP_SENSOR_H_
#define INC_BSP_SENSOR_H_

#include "BSP_I2C_ADT.h"

#define SENSOR_SLAVE_ADDR           0x58

#define SENSOR_INIT_CMD_MSB         0x20
#define SENSOR_INIT_CMD_LSB         0x03
#define SENSOR_INIT_CMD_LEN         (sizeof(cmds)/sizeof(cmds[0]))

#define SENSOR_MEASURE_CMD_MSB      0x20
#define SENSOR_MEASURE_CMD_LSB      0x08
#define SENSOR_MEASURE_CMD_LEN      (sizeof(cmds)/sizeof(cmds[0]))

#define SENS_DATA_LEN 2



uint8_t *BSP_GetSensorReading(void);
void BSP_SensorInit(void);

#endif /* INC_BSP_SENSOR_H_ */

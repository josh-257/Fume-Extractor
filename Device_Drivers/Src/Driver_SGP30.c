/*
 * Sensor.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include "Driver_SGP30.h"



void SGP30_sensorInit(void)
{


  static const uint8_t cmds[] = {
      SENSOR_INIT_CMD_MSB,
      SENSOR_INIT_CMD_LSB
  };

  BSP_sendData(cmds, SENSOR_INIT_CMD_LEN, SENSOR_SLAVE_ADDR, DISABLE);
}

uint8_t *SGP30_getSensorReading(void)
{
  static uint8_t sensorData[6];

  static const uint8_t cmds[] = {
        SENSOR_MEASURE_CMD_MSB,
        SENSOR_MEASURE_CMD_LSB
    };

  BSP_sendData(cmds, SENSOR_MEASURE_CMD_LEN, SENSOR_SLAVE_ADDR, DISABLE);

  //Wait 12ms to for device to send calculated reading
  for(uint32_t i = 0; i < 15000; i++);

  BSP_receiveData(sensorData, 6, SENSOR_SLAVE_ADDR, DISABLE);

  return sensorData;
}

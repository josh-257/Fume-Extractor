/*
 * Sensor.c
 *
 *  Created on: 13 Aug 2026
 *      Author: joshb
 */
#include <stdbool.h>
#include "BSP_Sensor.h"
#include "BSP_I2C_ADT.h"
#include "stm32f407xx.h"
#include "stm32f4xx.h"


void BSP_SensorInit(void)
{
  I2C_ADT BSP_I2CHandle = BSP_GetI2CHandle();

  static const uint8_t cmds[] = {
      SENSOR_INIT_CMD_MSB,
      SENSOR_INIT_CMD_LSB
//      0x26, 0x0F, 0x80, 0x00, 0xA2,
//      0x66, 0x66, 0x93

  };

  BSP_SendData(BSP_I2CHandle, cmds, SENSOR_INIT_CMD_LEN, SENSOR_SLAVE_ADDR, DISABLE);
}

uint8_t *BSP_GetSensorReading(void)
{
  I2C_ADT BSP_I2CHandle = BSP_GetI2CHandle();

  static uint8_t sensor_data[6];

  static const uint8_t cmds[] = {
        SENSOR_MEASURE_CMD_MSB,
        SENSOR_MEASURE_CMD_LSB
//      0x26, 0x0F, 0x80, 0x00, 0xA2,
//      0x66, 0x66, 0x93

    };

  BSP_SendData(BSP_I2CHandle, cmds, SENSOR_MEASURE_CMD_LEN, SENSOR_SLAVE_ADDR, DISABLE);

  //Wait 12ms to for device to send calculated reading
  for(uint32_t i = 0; i < 15000; i++);

  BSP_ReceiveData(BSP_I2CHandle, sensor_data, 6, SENSOR_SLAVE_ADDR, DISABLE);

  return sensor_data;
}

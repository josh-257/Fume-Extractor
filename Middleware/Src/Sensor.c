/*
 * Mid_Sensor.c
 *
 *  Created on: 31 Aug 2026
 *      Author: joshb
 */
#include <stdio.h>
#include "Sensor.h"

uint16_t *SNS_getSensorData(void)
{
  uint16_t static display_data[2];
  uint8_t *sens_data = SGP30_getSensorReading();

  //Take two 8 bit hex values and combine into the TVOC and ECO2 value
  display_data[0] = (uint16_t)((sens_data[0] << 8) | sens_data[1]);
  display_data[1] = (uint16_t)((sens_data[3] << 8) | sens_data[4]);

  return display_data;
}

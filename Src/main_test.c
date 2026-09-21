/*
 * Application Entry Point
 */

#include <FanControl.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Sensor.h"
#include "Graphics.h"
#include "BSP.h"

#define VOC 0
#define ECO2 1

typedef enum {
  READY_TO_START,
  NO_FUMES_DETECTED,
  FUMES_DETECTED,
  RESTART
}SystemState_t;

/*********************************This is needed for using SWV printf**************************/

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        ITM_SendChar((*ptr++));
    }
    return len;
}


void delay(uint32_t u_sec)
{
  for(uint32_t i = 0; i < u_sec; i++);
}



#define DELAY_MS 0x3E80

volatile uint32_t millis;
FanSetting_t FanSetting;
volatile SystemState_t systemState = READY_TO_START;

/*
 * pb6 --> SCL
 * pb7 --> SDA
 */

void setup(void)
{
  BSP_init();

  SSD1306_displayInit();
  delay(50);
  SGP30_sensorInit();

  SysTick_Config(DELAY_MS);

  fanInit();
}

int main(void)
{
  uint32_t prevMillis = 0;
  uint8_t sensorString[20];
  uint16_t *sensorData;
  uint32_t seconds = 0;

  setup();

  for(;;)
  {
    switch (systemState) {
      case READY_TO_START:

        FC_setMotorSpeed(FAN_STOP);

        GFX_clearFrame();

        GFX_setCursor(0,0);
        GFX_drawString((uint8_t*)"System Ready");
        GFX_setCursor(0, 3);
        GFX_drawString((uint8_t*)"Press to start");
        GFX_setCursor(0, 6);
        GFX_drawString((uint8_t*)"Press again to  stop...");
        GFX_sendFrame();
        while(systemState == READY_TO_START);
        break;

      case NO_FUMES_DETECTED:

        FC_setMotorSpeed(FAN_LOW);

        GFX_clearFrame();

        while(systemState == NO_FUMES_DETECTED)
        {
          if(millis - prevMillis >= 1000)
          {
            GFX_clearFrame();
            sensorData = SNS_getVOCReading();
            if(sensorData[VOC] > 1000)
            {
              systemState = FUMES_DETECTED;
            }
            snprintf((char*)sensorString, sizeof(sensorString), "VOC: %u", sensorData[VOC]);
            GFX_setCursor(0, 0);
            GFX_drawString((uint8_t*)sensorString);

            snprintf((char*)sensorString, sizeof(sensorString), "eC02: %u", sensorData[ECO2]);
            GFX_setCursor(0, 3);
            GFX_drawString((uint8_t*)sensorString);

            GFX_sendFrame();
            prevMillis = millis;
          }
        }
        break;
      case FUMES_DETECTED:

        FC_setMotorSpeed(FAN_HIGH);

        GFX_clearFrame();
        while(systemState == FUMES_DETECTED)
        {
          if(millis - prevMillis >= 1000)
          {
            sensorData = SNS_getVOCReading();
            if(sensorData[0] < 1000 && seconds > 10)
            {
              systemState = NO_FUMES_DETECTED;
              seconds = 0;
            }
            snprintf((char*)sensorString, sizeof(sensorString), "VOC: %u", sensorData[VOC]);
            GFX_setCursor(0, 0);
            GFX_drawString((uint8_t*)sensorString);

            snprintf((char*)sensorString, sizeof(sensorString), "eC02: %u", sensorData[ECO2]);
            GFX_setCursor(0, 3);
            GFX_drawString((uint8_t*)sensorString);

            GFX_setCursor(0, 6);
            GFX_drawString((uint8_t*)"FUMES DETECTED");
            GFX_sendFrame();
            prevMillis = millis;
            seconds++;
          }
        }
        break;
      case RESTART:
        GFX_clearFrame();
        FC_setMotorSpeed(FAN_STOP);
        GFX_setCursor(0,0);
        GFX_drawString((uint8_t*)"Shutting Down...");
        GFX_sendFrame();
        delay(2000000);
        systemState = READY_TO_START;
        break;

      default:
        break;
    }
  }

  return 0;
}



void SysTick_Handler(void)
{
  millis++;
}

void EXTI1_IRQHandler(void)
{
  const static uint8_t debounce_delay = 50; //ms
  static uint32_t last_debounce_time = 0;

  EXTI_clearPendingBit(1);

  //Wait before checking button state again
  if(millis > (last_debounce_time + debounce_delay))
  {
    if(systemState == READY_TO_START)
    {
      systemState = NO_FUMES_DETECTED;
    }
    else
    {
      systemState = RESTART;
    }
    last_debounce_time = millis;
  }


}


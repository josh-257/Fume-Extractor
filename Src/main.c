/*
 *  This code is for a solder fume extractor fan.
 *
 *  This system has 4 states of operation:
 *
 *  READY_TO_START - Fan stopped, no readings shown.
 *  NO_FUMES_DETECTED - Fan runs at 25% speed, shows air quality readings.
 *  FUMES_DETECTED - Fan runs at 100% speed, shows air quality readings and "FUMES DETECTED!" message.
 *  RESTART - Fan stopped, switches back to READY_TO_START state.
 *
 *  Air quality readings:
 *
 *  Total Volcanic Organic Compounds (TVOC) measured in parts per billion.
 *  Estimated Co2 (ECO2) calculated in parts per million.
 */
#include <stdio.h>
#include <stdbool.h>
#include "FanControl.h"
#include "Sensor.h"
#include "Graphics.h"
#include "BSP.h"

//Systick load register value to produce 1ms interrupts
#define DELAY_MS 0x3E80

#define FUME_THRESHOLD  60

#define VOC 1
#define ECO2 0

typedef enum {
  READY_TO_START,
  NO_FUMES_DETECTED,
  FUMES_DETECTED,
  RESTART
}SystemState_t;

//Count number of ms since program start
volatile uint32_t millis;

//Define global variable to hold system state
volatile SystemState_t systemState = READY_TO_START;

volatile bool btnPressed = false;

void setup(void);
void displayStartUpMsg(void);
void displaySensorData(uint16_t *sensorData);
void delay(uint32_t u_sec);
bool debounceButton(void);

int main(void)
{
  uint32_t prevMillis = 0;
  uint16_t *sensorData;
  uint32_t seconds = 0;

  //Initalise peripherals, sensor, display and fan drivers
  setup();
  FC_setFanSpeed(FAN_STOP);
  for(;;)
  {
    switch (systemState) {
      case READY_TO_START:
        //Clear frame buffer
        GFX_clearFrame();

        displayStartUpMsg();

        //Hold until button pressed
        while(btnPressed == false);
        btnPressed = false;
        FC_setFanSpeed(FAN_LOW);
        systemState = NO_FUMES_DETECTED;

        break;

      case NO_FUMES_DETECTED:

        //Check/display air quality readings every second
        if(millis - prevMillis >= 1000)
        {
          GFX_clearFrame();
          sensorData = SNS_getSensorData();
          //If reading exceeds threshold, switch into fumes detected state
          if(sensorData[VOC] > FUME_THRESHOLD)
          {
            FC_setFanSpeed(FAN_HIGH);
            systemState = FUMES_DETECTED;
          }
          displaySensorData(sensorData);
          prevMillis = millis;
        }
        if(btnPressed)
        {
          btnPressed = false;
          systemState = RESTART;
        }

        break;
      case FUMES_DETECTED:

        //Check and display air quality readings every second
        if(millis - prevMillis >= 1000)
        {
          sensorData = SNS_getSensorData();
          //If fumes dissipate after 10 sec switch back to no fumes detected state
          if(sensorData[VOC] < FUME_THRESHOLD && seconds > 30)
          {
            FC_setFanSpeed(FAN_LOW);
            systemState = NO_FUMES_DETECTED;
            seconds = 0;
          }

          GFX_clearFrame();
          displaySensorData(sensorData);

          //Alert user that fumes have been detected
          GFX_setCursor(0, 6);
          GFX_drawString((uint8_t*)"FUMES DETECTED");
          GFX_sendFrame();
          prevMillis = millis;
          seconds++;
        }
        if(btnPressed)
        {
          btnPressed = false;
          systemState = RESTART;
        }
        break;
      case RESTART:

        FC_setFanSpeed(FAN_STOP);
        systemState = READY_TO_START;
        break;

      default:
        break;
    }
  }

  return 0;
}

void setup(void)
{
  BSP_init();

  SSD1306_displayInit();
  delay(50);
  SGP30_sensorInit();

  SysTick_Config(DELAY_MS);

  FC_fanInit();
}

void delay(uint32_t u_sec)
{
  for(uint32_t i = 0; i < u_sec; i++);
}

void displayStartUpMsg(void)
{
  GFX_setCursor(0,0);
  GFX_drawString((uint8_t*)"System Ready");
  GFX_setCursor(0, 3);
  GFX_drawString((uint8_t*)"Press to start");
  GFX_setCursor(0, 6);
  GFX_drawString((uint8_t*)"Press again to  stop...");
  GFX_sendFrame();
}

void displaySensorData(uint16_t *sensorData)
{
  uint8_t sensorString[20];

  snprintf((char*)sensorString, sizeof(sensorString), "TVOC: %4u", sensorData[VOC]);
  GFX_setCursor(0, 0);
  GFX_drawString((uint8_t*)sensorString);

  snprintf((char*)sensorString, sizeof(sensorString), "eC02: %5u", sensorData[ECO2]);
  GFX_setCursor(0, 3);
  GFX_drawString((uint8_t*)sensorString);

  GFX_sendFrame();
}

void SysTick_Handler(void)
{
  millis++;

  if(millis % 5 == 0)
  {
    if(debounceButton())
    {
      btnPressed = true;
    }
  }
}

bool debounceButton(void)
{
  static uint16_t State = 0;  // Current debounce status
  State = (State << 1) | !BSP_ButtonPressed() | 0xe000;
  if (State == 0xf000)
  {
    return true;
  }
  return false;
}

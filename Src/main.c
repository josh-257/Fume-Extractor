/*
 *  This code is for a solder fume extractor fan.
 *
 *  This system has 4 states of operation:
 *
 *  READY_TO_START - Fan stopped, no readings shown.
 *  NO_FUMES_DETECTED - Fan runs at low speed, shows air quality readings.
 *  FUMES_DETECTED - Fan runs at high speed, shows air quality readings and "FUMES DETECTED!" message.
 *  RESTART - Fan stopped, switches back to READY_TO_START state.
 *
 *  Air quality readings:
 *
 *  Total Volatile Organic Compounds (TVOC) measured in parts per billion.
 *  Estimated CO2 (ECO2) calculated in parts per million.
 */
#include <stdio.h>
#include <stdbool.h>
#include "FanControl.h"
#include "Sensor.h"
#include "Graphics.h"
#include "BSP.h"

//Systick load register value to produce 1ms interrupts at 16MHz clock speed
#define SYSTICK_RELOAD 0x3E80

#define FUME_THRESHOLD  60 //Parts per billion
#define FUME_EXTRACT_TIME 10 //Seconds

#define SENS_POLL_RATE 1000 //milliseconds

//Index for sensor data array
#define TVOC 1
#define ECO2 0

#define BTN_SAMPLE_RATE 5 //milliseconds

#define DEBOUNCE_MASK 0xE000
#define DEBOUNCE_PATTERN 0xF000

#define SENS_STR_MAX_LEN 20

typedef enum {
  READY_TO_START,
  NO_FUMES_DETECTED,
  FUMES_DETECTED,
  RESTART
}SystemState_t;

//Count number of ms since program start
volatile uint32_t millis;

volatile bool btnPressEvent = false;

void setup(void);
void displayStartUpMsg(void);
void displaySensorData(uint16_t *sensorData);
void delay(uint32_t u_sec);
bool checkBtnPressEvent(void);

int main(void)
{
  SystemState_t systemState = READY_TO_START;
  uint32_t prevMillis = 0;
  uint16_t *sensorData;
  uint32_t seconds = 0;

  //Initialise peripherals, sensor, display and fan drivers
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
        while(btnPressEvent == false);

        btnPressEvent = false;
        FC_setFanSpeed(FAN_LOW);
        systemState = NO_FUMES_DETECTED;

        break;

      case NO_FUMES_DETECTED:

        //Check/display air quality readings according to poll rate
        if(millis - prevMillis >= SENS_POLL_RATE)
        {
          GFX_clearFrame();
          sensorData = SNS_getSensorData();
          //If reading exceeds threshold, switch into fumes detected state
          if(sensorData[TVOC] > FUME_THRESHOLD)
          {
            FC_setFanSpeed(FAN_HIGH);
            systemState = FUMES_DETECTED;
          }
          displaySensorData(sensorData);
          GFX_sendFrame();
          prevMillis = millis;
        }
        if(btnPressEvent)
        {
          btnPressEvent = false;
          systemState = RESTART;
        }

        break;
      case FUMES_DETECTED:

        //Check and display air quality readings according to poll rate
        if(millis - prevMillis >= SENS_POLL_RATE)
        {
          sensorData = SNS_getSensorData();
          //If fumes dissipate after 10 sec switch back to no fumes detected state
          if(sensorData[TVOC] < FUME_THRESHOLD && seconds >= FUME_EXTRACT_TIME)
          {
            FC_setFanSpeed(FAN_LOW);
            systemState = NO_FUMES_DETECTED;
            seconds = 0;
          }

          GFX_clearFrame();
          displaySensorData(sensorData);
          //Alert user that fumes have been detected
          GFX_setCursor(0, 6);
          GFX_drawString("FUMES DETECTED!");
          GFX_sendFrame();
          prevMillis = millis;
          seconds++;
        }
        if(btnPressEvent)
        {
          seconds = 0;
          btnPressEvent = false;
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

void SysTick_Handler(void)
{
  millis++;

  //Check if button pressed every 5ms
  if(millis % BTN_SAMPLE_RATE == 0)
  {
    if(checkBtnPressEvent() == true)
    {
      btnPressEvent = true;
    }
  }
}

void setup(void)
{

  BSP_init();

  SSD1306_displayInit();
  delay(50);
  SGP30_sensorInit();

  SysTick_Config(SYSTICK_RELOAD);

  FC_fanInit();
}

void delay(uint32_t u_sec)
{
  for(uint32_t i = 0; i < u_sec; i++);
}


void displayStartUpMsg(void)
{
  GFX_setCursor(0,0);
  GFX_drawString("System Ready");
  GFX_sendFrame();
}

//Convert sensor data input into string to display
void displaySensorData(uint16_t *sensorData)
{
  char sensorString[SENS_STR_MAX_LEN];

  snprintf(sensorString, sizeof(sensorString), "TVOC: %4u", sensorData[TVOC]);
  GFX_setCursor(0, 0);
  GFX_drawString(sensorString);

  snprintf(sensorString, sizeof(sensorString), "eCO2: %5u", sensorData[ECO2]);
  GFX_setCursor(0, 3);
  GFX_drawString(sensorString);
}


/*****************************************************
 * @brief Debounce button, return true once per confirmed press.
 *
 *        Should be called at a fixed rate by a timer.
 *
 *        Records one sample of the button as one bit (newest sample bit 0).
 *
 *        Based on Jack Ganssle's "A Guide to Debouncing", DebounceSwitch2().
 */
bool checkBtnPressEvent(void)
{
  static uint16_t State = 0;  // Current debounce status

  State = (State << 1) | !BSP_ButtonPressed() | DEBOUNCE_MASK;

  if (State == DEBOUNCE_PATTERN)
  {
    return true;
  }
  return false;
}

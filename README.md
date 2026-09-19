# Solder Fume Extractor Fan

## Overview

This system is designed to detect solder fumes in the air and extract the harmful fumes away from the user. It consists of 4 components; a PC fan, OLED display, gas sensor and a push button all connected to a STM32F407 dev board. 

## Operation

#### This system has 4 states of operation:

*  READY_TO_START - Fan stopped, "Ready to start..." message displayed.
*  NO_FUMES_DETECTED - Fan runs at 25% speed, shows air quality readings.
*  FUMES_DETECTED - Fan runs at 100% speed, shows air quality readings and "FUMES DETECTED!" message.
*  RESTART - Fan stopped, switches back to READY_TO_START state.

When turned on, the system will initialise all peripherals before entering the "READY_TO_START" state. The system will wait in this state until the push button is pressed. Once pressed, The system will enter the "NO_FUMES_DETECTED" state. If the air quality level passess above a certain threshold the system will move into the "FUMES_DETECTED" state. If the air quality drops below the given threshold after 10 seconds the system will switch back into the "NO_FUMES_DETECTED" state. While in both the "FUMES_DETECTED" and "NO_FUMES_DETECTED" states if the push button is pressed the system will move into the "RESTART" state.

#### Air quality readings:
 
*  Total Volcanic Organic Compounds (TVOC) measured in parts per billion.
*  Estimated Co2 (ECO2) calculated in parts per million.

## Design Choices

#### Communication Protocol

Both the OLED display and gas sensor communicate with my stm32 MCU over the I2C protocol. I chose this protocol as it only requires two wires to connect both devices, reducing the mess on my small breadboard. 

#### Fan Choice

I chose a cheap 12V PC fan for this project as I wasn't too worried about the performance and more focused on something that was quiet but also easy to control with a PWM signal.

#### Software Architecture

I wanted to test out the HAL drivers I had written whilst following the course: "Mastering Microcontroller and Embedded Driver Development" by Kiran Nayak. Therefore I only included the ARM CMSIS header file for my specific MCU. I found it challenging at first to work out how to split my code into different layers but I ended up settling with this design:

[Project Layout Diagram](Docs/FumeExtractor.drawio.svg)

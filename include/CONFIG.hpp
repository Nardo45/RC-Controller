#pragma once

#include <Arduino.h>

// Joystick 1 pin configuration
#define JOY1_VRx_PIN 36 // X-axis analog pin
#define JOY1_VRy_PIN 39 // Y-axis analog pin
#define JOY1_SW_PIN 25  // Push button pin

// Joystick 2 pin configuration
#define JOY2_VRx_PIN 34 // X-axis analog pin
#define JOY2_VRy_PIN 35 // Y-axis analog pin
#define JOY2_SW_PIN 26 // Push button pin

// NRF24L01 transceiver pins configuration
#define NRF_CE_PIN 2
#define NRF_CSN_PIN 15

// Define the GPIO pin configuration for thin film pressure sensors
#define PRESS_SENSOR_1_PIN 33 // First sensor connected to GPIO 33
#define PRESS_SENSOR_2_PIN 32 // Second sensor connected to GPIO 32

// Define the payload structure for the controller
struct Payload {
  int16_t joy1X;
  int16_t joy1Y;
  bool joy1Button;
  int16_t joy2X;
  int16_t joy2Y;
  bool joy2Button;
  int16_t pressSens1;
  int16_t pressSens2;
};
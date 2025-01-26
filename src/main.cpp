#include "radioProcesses.hpp"
#include "ButtonProcesses.hpp"
#include "CONFIG.hpp"

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Create RF24 object
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);

// Address for communication (must match on receiver)
const byte address[6] = "9TfT0";

// Create an instance of the payload
Payload payloadData;

void setup() {
  Serial.begin(115200);

  pinMode(JOY1_SW_PIN, INPUT_PULLUP); // Pull-up for the joystick 1 button
  pinMode(JOY2_SW_PIN, INPUT_PULLUP); // Pull-up for the joystick 2 button

  // Set press sense pins as input
  pinMode(PRESS_SENSOR_1_PIN, INPUT);
  pinMode(PRESS_SENSOR_2_PIN, INPUT);

  transceiverInit(address); // Initialize the NRF24L01 transceiver
}

void loop() {
  joystickHandler(payloadData);
  getPressureSensorValues(payloadData);

  // Send the payload over the radio
  radio.write(&payloadData, sizeof(payloadData));
  delay(100); // Small delay to avoid spamming radio communications
}
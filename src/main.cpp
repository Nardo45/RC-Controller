#include "func_declare.h"

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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

// Create RF24 object
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);

// Address for communication (must match on receiver)
const byte address[6] = "9TfT0";

// Define the payload structure for both joysticks
struct JoystickPayload {
  int16_t joy1X;
  int16_t joy1Y;
  bool joy1Button;
  int16_t joy2X;
  int16_t joy2Y;
  bool joy2Button;
};

// Create an instance of the payload
JoystickPayload joystickData;

void setup() {
  Serial.begin(115200);

  pinMode(JOY1_SW_PIN, INPUT_PULLUP); // Pull-up for the joystick 1 button
  pinMode(JOY2_SW_PIN, INPUT_PULLUP); // Pull-up for the joystick 2 button

  transceiverInit(); // Initialize the NRF24L01 transceiver
}

void loop() {
  joystickHandler();

  delay(100);
}

void joystickHandler() {
  // Handle joystick movement and button press events
  // Read X and Y analog values
  joystickData.joy1X = analogRead(JOY1_VRx_PIN);
  joystickData.joy1Y = analogRead(JOY1_VRy_PIN);
  joystickData.joy2X = analogRead(JOY2_VRx_PIN);
  joystickData.joy2Y = analogRead(JOY2_VRy_PIN);

  // Read button state
  joystickData.joy1Button = digitalRead(JOY1_SW_PIN);
  joystickData.joy2Button = digitalRead(JOY2_SW_PIN);

  // Send the payload
  bool success = radio.write(&joystickData, sizeof(joystickData));
  
  if (!success) {
    Serial.println("Failed to send the payload.");
  } else {
    Serial.print("Payload sent successfully.");
  Serial.print("Joystick 1 - X: ");
  Serial.print(joystickData.joy1X);
  Serial.print(", Y: ");
  Serial.print(joystickData.joy1Y);
  Serial.print(", Button: ");
  Serial.println(joystickData.joy1Button? "ON" : "OFF");

  Serial.print("Joystick 2 - X: ");
  Serial.print(joystickData.joy2X);
  Serial.print(", Y: ");
  Serial.print(joystickData.joy1Y);
  Serial.print(", Button: ");
  Serial.println(joystickData.joy2Button? "ON" : "OFF");
  }
}


void transceiverInit() {
  radio.begin(); // Initialize the nRF24L01 module
  radio.openWritingPipe(address); // Set the address for sending data
  radio.setPALevel(RF24_PA_LOW); // Set the power amplification level
  radio.stopListening(); // Stop listening for incoming data
}
#include "ButtonProcesses.hpp"
#include "CONFIG.hpp"

void joystickHandler(Payload& payloadData) {
  // Handle joystick movement, button press events, and add them to the payload
  // Read X and Y analog values
  payloadData.joy1X = analogRead(JOY1_VRx_PIN);
  payloadData.joy1Y = analogRead(JOY1_VRy_PIN);
  payloadData.joy2X = analogRead(JOY2_VRx_PIN);
  payloadData.joy2Y = analogRead(JOY2_VRy_PIN);

  // Read button state
  payloadData.joy1Button = digitalRead(JOY1_SW_PIN);
  payloadData.joy2Button = digitalRead(JOY2_SW_PIN);
}

void getPressureSensorValues(Payload& payloadData) {
  // Read the analog value from the pressure sensor
  payloadData.pressSens1 = analogRead(PRESS_SENSOR_1_PIN);
  payloadData.pressSens2 = analogRead(PRESS_SENSOR_2_PIN);
}
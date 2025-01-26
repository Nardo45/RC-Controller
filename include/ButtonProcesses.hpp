#pragma once

#include "CONFIG.hpp"

/**
 * @brief This function retrieves the current values from the pressure sensor and stores them in the provided Payload object.
 *
 * @param payloadData A reference to a Payload object where the pressure sensor values will be stored.
 *
 * @return None. The function only updates the Payload object with the pressure sensor values.
 */
void getPressureSensorValues(Payload& payloadData);

/**
 * @brief Handles joystick input and updates the payload data accordingly.
 * 
 * This function processes the joystick input and modifies the provided payload
 * data structure with the current joystick state.
 * 
 * @param payloadData Reference to the Payload structure to be updated with joystick data.
 *
 * @return None. This function does not return a value.
 */
void joystickHandler(Payload& payloadData);
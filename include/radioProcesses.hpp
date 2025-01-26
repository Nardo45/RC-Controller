#pragma once

#include <Arduino.h>

/**
 * @brief Initializes the radio transceiver.
 * 
 * This function sets up the radio transceiver with the specified address.
 * 
 * @param address A reference to a byte representing the unique address for the transceiver.
 *                This address is used to identify the device in radio communications.
 * 
 * @return None. This function does not return a value.
 */
void transceiverInit(const byte (&address)[6]);

#pragma once

void joystickHandler();

/**
 * @brief Initializes the transceiver module.
 *
 * This function sets up and configures the transceiver for wireless communication.
 * It should be called once at the beginning of the program before any transmission
 * or reception operations.
 *
 * @return void
 */
void transceiverInit();

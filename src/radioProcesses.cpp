#include "radioProcesses.hpp"

#include <RF24.h>

extern RF24 radio;

void transceiverInit(const byte (&address)[6]) {
  radio.begin(); // Initialize the nRF24L01 module
  radio.openWritingPipe(address); // Set the address for sending data
  radio.setPALevel(RF24_PA_LOW); // Set the power amplification level
  radio.stopListening(); // Stop listening for incoming data
}
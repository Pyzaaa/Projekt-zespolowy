// kod do waveshare z examples/SMS
// mamy zmodyfikowany kod z biblioteki Waveshare_SIM7600.cpp bez Powerkey bo powerkay nie działało

#include <SPI.h>
#include <mcp_can.h>

#include "newlib.h" // do obslugi modulu SIM

// Define the pins used for the CAN module
const int SPI_CS_PIN = 10;

// Initialize MCP2515 object with CS pin
MCP_CAN CAN(SPI_CS_PIN);

char phone_number[] = "**********";      //********** change it to the phone number you want to call
char text_message[] = "www.waveshare.com";      //


void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);


  printf("Sending Short Message Test:\n");
  sim7600.SendingShortMessage(phone_number,text_message);
}

void loop() {
  // Check if MCP2515 is still alive
  if (CAN.checkError() == CAN_OK) {
    Serial.println("MCP2515 is online.");
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  } else {
    Serial.println("MCP2515 is offline. Check connections!");
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  }
  
  delay(1000); // Wait for 1 second before next check
}

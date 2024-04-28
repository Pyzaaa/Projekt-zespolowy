#include <SPI.h>
#include <mcp_can.h>

// Define the pins used for the CAN module
const int SPI_CS_PIN = 10;

// Initialize MCP2515 object with CS pin
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
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

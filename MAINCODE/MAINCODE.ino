// includes:
#include <SPI.h>
#include <mcp_can.h>


// Define the pins used for the CAN module
const int SPI_CS_PIN = 10;
// Initialize MCP2515 object with CS pin
MCP_CAN CAN(SPI_CS_PIN);



// declare other functions there
String sendAT(){
  // Send data over Serial1
  Serial1.println("AT");
  
  // Wait for response
  while (!Serial1.available()) {
    // Wait for data to be available
  }
  
  // Read response
  String response = "";
  while (Serial1.available()) {
    char c = Serial1.read();
    response += c;    
    delay(100); // This makes it read full data correctly
  }
  return response; // should respond with AT \n OK
}

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600); //default baud rate
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  
  // Initialize Serial1 for communication with 4g module
  Serial1.begin(115200); // 4g module uses 115200 baud rate
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB
  }
    // Check if 4G module is up
  Serial.println("Testing 4G module with AT command, Module responded with:\n" + sendAT());
    // Check if MCP2515 is still alive
  if (CAN.checkError() == CAN_OK) {
    Serial.println("MCP2515 is online.");
  } else {
    Serial.println("MCP2515 is offline. Check connections!");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

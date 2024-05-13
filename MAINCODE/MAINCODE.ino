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

String sendcommand(String COMMAND){
  // Send data over Serial1
  Serial1.println(COMMAND.c_str());
  
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
  return response;
}

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600); //default
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  
  // Initialize Serial1 for communication with 4g module
  Serial1.begin(115200); // 4g module uses 115200 baud rate
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB
  }
// Set the built-in LED pin as an output
//pinMode(LED_BUILTIN, OUTPUT);

    // Check if 4G module is up
  Serial.println("Testing 4G module with AT command, Module responded with:\n" + sendAT());
    // Check if MCP2515 is still alive
  if (CAN.checkError() == CAN_OK) {
    Serial.println("MCP2515 is online.");
  } else {
    Serial.println("MCP2515 is offline. Check connections!");
  }
//digitalWrite(LED_BUILTIN, HIGH); // LED doesn't turn on for some reason

Serial.println("Sending command AT+CSQ:\n" + sendcommand("AT+CSQ"));
}

void loop() {
  // put your main code here, to run repeatedly:
String userInput = "";
Serial.println("Enter your input:");
  while (Serial.available() == 0) {
    // Wait for user input
  }
  // Read user input from Serial monitor and store it in userInput variable
  while (Serial.available()) {
    char c = Serial.read();
    userInput += c;
    delay(100);
  }
  
  // Print the user input for verification
  Serial.print("You entered: ");
  Serial.println(userInput);  
  Serial.println("Sending command: "+ userInput + sendcommand(userInput));
}

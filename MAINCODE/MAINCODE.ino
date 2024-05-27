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

String sendCPIN(){ //for SIM CARD PUK operation
  // Send data over Serial1
  Serial1.println("AT+CPIN=?");
  
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


String sendSMS(String text){
  // SMS send test:
    Serial.print("Setting SMS mode...\n");

  Serial.println("Sending command AT+CMGF=1:\n" + sendcommand("AT+CMGF=1"));
        // sets the SMS mode to text
    Serial.print("Sending Short Message\n");
  Serial.println("Sending command :\n" + sendcommand("AT+CMGS=\"+48*********\"")); //phone number in "" quotes \" is escape character    
  //nr Klaudii
  //  Serial.println("Sending command :\n" + sendcommand("AT+CMGS=\"+48*********\"")); //phone number in "" quotes \" is escape character
  //nr pawła
        Serial1.println(text); //SMS text content
        Serial1.write(0x1A); //sends CTRL+Z to module to send SMS message
        sendcommand("");
  return "Finished sending SMS";
}

String URL = "https://webhook.site/30d20c7f-ab86-4bbe-a03c-5b2f530a9907";
String CONTENT = "application/x-www-form-urlencoded";

// HTTP POST SENDING
String SendHTTP(String Data) {
  Serial.println("Sending command:\n" + sendcommand("AT+HTTPINIT")); // INITIALIZE HTTP
  Serial.println("Sending command:\n" + sendcommand("AT+HTTPPARA=\"URL\",\""+URL+"\""));
  Serial.println("Sending command:\n" + sendcommand("AT+HTTPPARA=\"CONTENT\",\""+CONTENT+"\""));

  String length = String(Data.length());
  Serial.println("Sending command:\n" + sendcommand("AT+HTTPDATA="+ length +",5000")); //set information about message about to be sent
  Serial.println("Sending command:\n" + sendcommand(Data)); //print sent data to serial to save it 
  Serial.println("Sending command:\n" + sendcommand("AT+HTTPACTION=1")); //Send data as post
  //Serial.println("Sending command:\n" + sendcommand("AT+HTTPACTION=0,200")); //Send data as post

  Serial.println("Sending command:\n" + sendcommand("AT+HTTPTERM")); // Terminate HTTP
  return "Finished sending HTTP";
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
String enterpin;
Serial.println("Sending command AT+CSQ:\n" + sendcommand("AT+CSQ"));
enterpin = sendcommand("AT+CPIN?");
Serial.println("Sending command AT+CPIN:\n" + enterpin); //Check if SIM card is waiting for PIN
//if (enterpin == "+CPIN: SIM PIN"){
Serial.println("Sending command AT+CPIN=0000:\n" + sendcommand("AT+CPIN=0000")); //inputs PIN NUMBER 0000 to unlock the SIM card
Serial.println("Sending command AT+CPIN:\n" + sendcommand("AT+CPIN?"));
//};
//Serial.println("Sending command AT+CPIN=0000:\n" + sendcommand("AT+CPIN=0000")); //inputs PIN NUMBER 0000 to unlock the SIM card
//Serial.println("Sending command AT+CPIN:\n" + sendcommand("AT+CPIN?"));

//HTTP Sending

//sendSMS("Siema jestem Arduino XD");
Serial.println("Sending command:\n" + sendcommand("AT+CGREG?"));
Serial.println("Sending command:\n" + sendcommand("AT+CGACT?"));
Serial.println("Sending command:\n" + sendcommand("AT+CGDCONT?"));
Serial.println("Sending command:\n" + sendcommand("AT+CGDCONT=1,\"IP\",\"internet\"")); //set IP as protocol and "internet" as ISP Access point name (From orange site https://www.orange.pl/omnibook/konfiguracja-internetu-mms-sms-w-telefonie)

Serial.println("Sending test data:\n");
SendHTTP("TEST DATA");
}




void loop() {
  // put your main code here, to run repeatedly:

 // Check if there are new CAN messages available  Bartosz Futoma
    if (CAN_MSGAVAIL == CAN.checkReceive()) {
        long unsigned int rxId;
        unsigned char len = 0;
        unsigned char rxBuf[8];
        
        // Read CAN message
        CAN.readMsgBuf(&rxId, &len, rxBuf);
        
        // Display ID and data
        Serial.print("ID: ");
        Serial.println(rxId, HEX);
        
        for (int i = 0; i < len; i++) {
            Serial.print("Data ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(rxBuf[i], HEX);
        }

        int someVariable = rxBuf[0];

        String postData = "{\"id\":";
        postData += rxId;
        postData += ", \"data\":";
        postData += someVariable;
        postData += "}";

        Serial.println("Sending CAN data to the server: " + postData);
        SendHTTP(postData);
    }
  

// Test/DEBUG code for sending HTTP Post information to test API.
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
  Serial.print("Sending input to Test API: ");
  SendHTTP(userInput);
  //String response = "";
  //response = sendcommand(userInput);
  //Serial.println("Sending command: "+ userInput + "response: " + response);
}

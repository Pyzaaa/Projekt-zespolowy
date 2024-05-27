// kod do waveshare z examples/SMS
// mamy zmodyfikowany kod z biblioteki Waveshare_SIM7600.cpp bez Powerkey bo powerkay nie działało

#include <SPI.h>
#include <mcp_can.h>

//#include "newlib.h" // do obslugi modulu SIM


// Define the pins used for the CAN module
const int SPI_CS_PIN = 10;

// Initialize MCP2515 object with CS pin
MCP_CAN CAN(SPI_CS_PIN);

char phone_number[] = "**********";      //********** change it to the phone number you want to call
char text_message[] = "www.waveshare.com";      //
uint8_t returned;




  
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  
  // Initialize Serial1 for communication with another device
  Serial1.begin(9600);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB
  }

    // Set the 1st pin (pin 0) as input
  pinMode(0, INPUT);
    // Set the 3rd pin (pin 2) as output
  pinMode(2, OUTPUT);

  // initialize digital pin LED_BUILTIN as an output.
  //sim7600.PowerOn();
  pinMode(LED_BUILTIN, OUTPUT);


  //printf("Sending Short Message Test:\n");
  //sim7600.SendingShortMessage(phone_number,text_message);
  
  //returned = sim7600.sendATcommand("AT", "OK", 1000);  
  //printf("Response from AT:\n" + returned);  // to powinno cos zwrocic ale nie zwraca
}

void loop() {

  String dataToSend = "Hello, world!";
  Serial1.println(dataToSend);    // Send the AT command 
  Serial.println("sent: AT");    //
  
  // Read response
  String response = "";
  while (Serial1.available()) {
    char c = Serial1.read();
    response += c;
  }
  
  Serial.println("Response: " + response);
  delay(1000); // Wait for 1 second before next check
}

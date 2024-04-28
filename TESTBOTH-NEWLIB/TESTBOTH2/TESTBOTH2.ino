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
uint8_t returned;




  
void setup() {
  Serial.begin(9600);

    // Set the 1st pin (pin 0) as input
  pinMode(0, INPUT);
    // Set the 3rd pin (pin 2) as output
  pinMode(2, OUTPUT);

  // initialize digital pin LED_BUILTIN as an output.
  //sim7600.PowerOn();
  pinMode(LED_BUILTIN, OUTPUT);


  printf("Sending Short Message Test:\n");
  sim7600.SendingShortMessage(phone_number,text_message);
  
  returned = sim7600.sendATcommand("AT+CFUN?", "OK", 1000);
  printf("Response from AT:\n" + returned);  // to powinno cos zwrocic ale nie zwraca
}

void loop() {

    int data = digitalRead(0);
  // Print the received data to the Serial console
  Serial.println(data);

  // Check if condition is met (for example, data is HIGH)
  if(data == 0) {
    // If condition is met, send HIGH signal to pin 2
    digitalWrite(2, HIGH);
  } else {
    // Otherwise, send LOW signal to pin 2
    digitalWrite(2, LOW);
  }

  // Check if MCP2515 is still alive
  if (CAN.checkError() == CAN_OK) {
  //  Serial.println("MCP2515 is online.");
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  } else {
    Serial.println("MCP2515 is offline. Check connections!");
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  }
  
  delay(1000); // Wait for 1 second before next check
}

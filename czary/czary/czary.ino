void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  
  // Initialize Serial1 for communication with another device
  Serial1.begin(115200);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop() {
  // Data to send
  
  String dataToSend = "AT";
  
  Serial.println("Sending: " + dataToSend);
  // Send data over Serial1
  Serial1.println(dataToSend);
  
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
  
  // Print response
  Serial.println("Response: " + response);
  
  // Delay before sending next data
  delay(1500); // Adjust delay as needed
}

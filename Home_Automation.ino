#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); // RX, TX

const int relay1 = 2;
const int relay2 = 3;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH); // relays off at start
  digitalWrite(relay2, HIGH);
  
  BT.begin(9600);   // Bluetooth baud rate
  Serial.begin(9600);
  Serial.println("Home Automation Ready");
}

void loop() {
  if (BT.available()) {
    char command = BT.read();
    Serial.println(command);

    if (command == 'A') {
      digitalWrite(relay1, LOW);  // Turn ON Relay1
    }
    else if (command == 'a') {
      digitalWrite(relay1, HIGH); // Turn OFF Relay1
    }
    else if (command == 'B') {
      digitalWrite(relay2, LOW);  // Turn ON Relay2
    }
    else if (command == 'b') {
      digitalWrite(relay2, HIGH); // Turn OFF Relay2
    }
  }
 }


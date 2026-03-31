Rain Detector System Code :-
#include <Servo.h>

#define RAIN_SENSOR 2  // Digital pin for rain sensor
#define SERVO_PIN 3    // Digital pin for servo motor

Servo myServo;  // Create Servo object

void setup() {
    pinMode(RAIN_SENSOR, INPUT); // Set rain sensor as input
    myServo.attach(SERVO_PIN);   // Attach servo to pin 3
    myServo.write(0);  // Default servo position (adjust as needed)
    Serial.begin(9600); // Start Serial Monitor
}

void loop() {
    int rainState = digitalRead(RAIN_SENSOR);  // Read sensor state

    Serial.print("Rain Sensor State: ");
    Serial.println(rainState);

    if (rainState == LOW) {  // If rain is detected
        myServo.write(90);  // Move servo to 90° (adjust if needed)
        Serial.println("Rain Detected! Closing...");
    } else {
        myServo.write(0);  // Move servo back to 0° (adjust if needed)
        Serial.println("No Rain. Opening...");
    }

    delay(1000);  // Wait before next reading
}

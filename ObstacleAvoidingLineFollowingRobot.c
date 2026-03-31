#include <Servo.h>

#define leftIR 2
#define rightIR 3
#define trigPin 9
#define echoPin 10
#define ENA 11
#define ENB 12
#define IN1 4
#define IN2 5
#define IN3 7
#define IN4 8

Servo servoMotor;
long duration;
int distance;

void setup() {
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  servoMotor.attach(6);
  servoMotor.write(90);  // Center
  
  Serial.begin(9600);
}

void loop() {
  distance = getDistance();

  if (distance < 20) {   // if obstacle within 20cm
    stopBot();
    delay(200);
    avoidObstacle();
  } 
  else {
    // Line follower logic
    int leftState = digitalRead(leftIR);
    int rightState = digitalRead(rightIR);

    if (leftState == 0 && rightState == 0) forward();
    else if (leftState == 0 && rightState == 1) turnLeft();
    else if (leftState == 1 && rightState == 0) turnRight();
    else stopBot();
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void forward() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopBot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void avoidObstacle() {
  servoMotor.write(0);
  delay(400);
  int leftDistance = getDistance();

  servoMotor.write(180);
  delay(400);
  int rightDistance = getDistance();

  servoMotor.write(90);
  delay(200);

  if (leftDistance > rightDistance) {
    turnLeft();
    delay(500);
  } else {
    turnRight();
    delay(500);
  }

  forward();
  delay(800);  // move ahead after turning
}

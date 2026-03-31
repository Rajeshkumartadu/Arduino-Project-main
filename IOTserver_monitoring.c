#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11

#define FLAME_PIN D5
#define VIB_PIN D6
#define BUZZER_PIN D7
#define RELAY_PIN D3     // Fan relay
#define MQ2_PIN A0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("ESP8266 STARTED");

  pinMode(FLAME_PIN, INPUT);
  pinMode(VIB_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, HIGH);   // Fan OFF

  dht.begin();
}

void loop() {

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT11 Read Failed!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
  }

  int flame = digitalRead(FLAME_PIN);
  int vib   = digitalRead(VIB_PIN);
  int gas   = analogRead(MQ2_PIN);

  Serial.print("Flame Sensor: ");
  Serial.println(flame == LOW ? "🔥 FIRE DETECTED" : "NO FIRE");

  Serial.print("Vibration: ");
  Serial.println(vib == HIGH ? "DETECTED" : "NORMAL");

  Serial.print("Gas Value: ");
  Serial.println(gas);

  // ALERT + FAN LOGIC
  if (temp > 40 || gas > 400 || vib == HIGH || flame == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, LOW);   // Fan ON
    Serial.println("⚠ ALERT → FAN ON");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, HIGH);  // Fan OFF
    Serial.println("System Normal → Fan OFF");
  }

  Serial.println("---------------------------");
  delay(2000);
}
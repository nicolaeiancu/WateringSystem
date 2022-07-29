#define dry 60
#define powerPin 5
#define soilSensor 25

int analogValue;
int mappedValue;

void setup() {
  Serial.begin(115200);
  pinMode(powerPin, OUTPUT);
  analogReadResolution(12);
  startMillis = millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Measuring the humidity...");
  int analogValue = analogRead(soilSensor);
  int mappedValue = map(analogValue, 0, 4095, 0, 100);
  delay(2000);
  Serial.printf("Soil moisture is: %d%\n", mappedValue);

  if (mappedValue < dry) {
    if (currentMillis - startMillis >= period) {
      startMillis = currentMillis;
      Serial.println("Turning on the water pump");
      delay(5000);
      digitalWrite(powerPin, LOW);
      Serial.println("Turning off the water pump");
      delay(1000);
      digitalWrite(powerPin, HIGH);

    }
  }
  else {
    Serial.println("Soil is already wet.");
  }

  Serial.println("Watering over.");
  delay(10000);
}

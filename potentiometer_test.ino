void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.print("-----------------------------------------");
}

void loop() {
  int analogValue = analogRead(A11);
  Serial.print("Analog: ");
  Serial.println(analogValue);
  int angle = map(analogValue, 0, 1023, -135, 135);   // Mapping to angle
  Serial.print("Angle: ");
  Serial.println(angle);

  delay(500);
}

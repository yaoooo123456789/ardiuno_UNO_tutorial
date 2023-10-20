int photoResistor = A0; // 設定光敏電阻類比訊號的腳位
int value;

void setup() {
  pinMode(photoResistor, INPUT);
  Serial.begin(9600);
}

void loop() {
  value = analogRead(photoResistor);
  Serial.print("Analog signal: ");
  Serial.println(value);

  delay(1000);
}
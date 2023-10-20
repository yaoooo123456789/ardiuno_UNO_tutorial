int photoResistor = A0; // 設定光敏電阻類比訊號的腳位
int LEDpin = 5;         // 設定 LED 的腳位 需要有小蚯蚓 ~ (PWM) 的符號
int value;

// 線性轉換的函數
int reverse_map(long x, long in_max, long in_min,
                long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  pinMode(photoResistor, INPUT);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  value = analogRead(photoResistor);
  Serial.print("Analog signal: ");
  Serial.println(value);

  value = reverse_map(value,0,250,0,255);
  Serial.print("Mapped signal: ");
  Serial.println(value);

  analogWrite(LEDpin,value);
  delay(1000);
}
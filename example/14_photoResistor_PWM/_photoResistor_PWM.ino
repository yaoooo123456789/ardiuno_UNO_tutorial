int photoResistor = A0; // 設定光敏電阻類比訊號的腳位
int LEDpin = 2;         // 設定 LED 的腳位 數位(digital)腳位
int value;              // 儲存光敏電阻的類比訊號值

void setup() {
  pinMode(photoResistor, INPUT);
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  value = analogRead(photoResistor);
  Serial.print("Analog signal: ");
  Serial.println(value);
  
  if(value > 10 & value < 20) {     // 判斷 value 是否介於 10(不包含) 到 20 之間
    Serial.println("It is dim.");
  } else if(value <= 10) {          // 判斷 value 是否小於等於 10
    Serial.println("It is dark.");
    digitalWrite(LEDpin, HIGH);     // 數位訊號給高電壓 讓 LED 亮
  } else {                          // 其他狀況
    Serial.println("It is bright.");
    digitalWrite(LEDpin, LOW);      // 數位訊號給低電壓 不讓 LED 做事
  }
  delay(1000);
}
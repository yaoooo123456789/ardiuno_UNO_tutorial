void setup() {
  pinMode(2,OUTPUT);  // 設定腳位 2 作為輸出
}

void loop() {
  digitalWrite(2,HIGH); // 腳位 2 輸出高電位， LED 亮起來
  delay(1000);          // 控制 LED 明暗間隔(1000微秒)
  digitalWrite(2,LOW);  // 腳位 2 輸出低電位，滅掉 LED
  delay(1000);
}

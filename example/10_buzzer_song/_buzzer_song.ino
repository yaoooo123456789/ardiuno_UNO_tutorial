void setup() {
  pinMode(2,OUTPUT);  // 設定腳位 2 為輸出
}

void loop() {
  digitalWrite(2,HIGH); // 輸出高電位，會叫
  delay(1000);
  digitalWrite(2,LOW);  // 輸出低電位，不會叫
  delay(1000);
}

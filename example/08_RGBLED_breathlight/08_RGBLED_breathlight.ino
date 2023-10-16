byte R = 9;   // 定義 R 腳位為9
byte G = 10;  // 定義 G 腳位為10
byte B = 11;  // 定義 B 腳位為11
int brightness = 0;  
int fadeAmount = 5;  

void setup() {
  pinMode(R,OUTPUT);  // 設定 R, G, B 三個腳位皆作為輸出
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
}

void loop() {

  analogWrite(R, brightness);
  analogWrite(G, brightness);
  analogWrite(B, brightness);

  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}

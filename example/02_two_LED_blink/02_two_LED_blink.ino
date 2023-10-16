byte R = 2; \\ 定義一變數叫做 'R' 並且給他 '2' 這個數值
byte G = 3; \\ 定義一變數叫做 'G' 並且給他 '3' 這個數值

void setup() {
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
}

void loop() {
  digitalWrite(R,HIGH);
  digitalWrite(G,LOW);
  delay(1000);
  digitalWrite(R,LOW);
  digitalWrite(G,HIGH);
  delay(1000);
}

int receiver = 5; // 接收回傳的聲波
int trigger = 4;  // 發射聲波
float distance;   // 紀錄距離用
float t;          // 紀錄時間長度用

float compute_distance(float time) {
  /*
    聲波速度為 340 m/sec
    1 microsecond = 10^(-6) second
    340 m/sec = 34000/10^(-6) cm/microsecond = 0.034 cm/microsecond

    距離 = 時間 * 速率
    distance = time * 0.034 / 2 (除以 2 是因為來回距離)
    約略等於 distance = time / 58.0
  */
  float distance;
  distance = time / 58.0;
  return distance;
}

void setup() {
  Serial.begin(9600);
  pinMode(receiver, INPUT);
  pinMode(trigger, OUTPUT);
}

void loop() {
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);

  digitalWrite(trigger,HIGH);     // 發出聲波
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);      // 停止發出聲波
  
  t = pulseIn(receiver,HIGH);     // 讀取接收超音波脈衝時間 (微秒)
  distance = compute_distance(t); // 使用函式計算長度
  
  Serial.println(x);
  delay(250);
}

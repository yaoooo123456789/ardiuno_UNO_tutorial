// 定義蜂鳴器引腳
int buzzerPin = 9;

// 定義音符和音符的持續時間（以毫秒為單位），以實現60 BPM
int melody[] = {262, 262, 392, 392, 440, 440, 392, 0, 349, 349, 330, 330, 294, 294, 262, 0};
int noteDurations[] = {500, 500, 750, 750, 667, 667, 1500, 3000, 857, 857, 1000, 1000, 750, 750, 500, 3000};

void setup() {
  // 設置蜂鳴器引腳為輸出
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // 播放音樂
  for (int i = 0; i < 16; i++) {
    int duration = noteDurations[i];
    tone(buzzerPin, melody[i], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
  delay(1000);  // 停頓一秒
}

#include "notes.h"        // 引入函式庫

int buzzerPin = 9;        // 定義蜂鳴器引腳
int size;
float BPM = 120.0;                // Beats Per minute
int quarter = (60/BPM)*1000;      // 四分音符
int half = quarter * 2;           // 半分音符
int eigth = quarter / 2;          // 八分音符

void set_beats(float BPM, int beats[]) {
  float BPS;
  BPS = BPM / 60.0;               // 換成 Beats Per second
  beats[1] = round(BPS * 1000);
  beats[0] = round(beats[1]*2);
  beats[2] = round(beats[1]/2);
}

// 簡譜對照表
// 1: C4, 2: D4, 3: E4, 4: F4, 5: G4, 6: A4
// 5. : G3

// 用陣列儲存兩隻老虎的旋律
int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4,
                NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4,
                NOTE_E4, NOTE_F4, NOTE_G4,
                NOTE_E4, NOTE_F4, NOTE_G4,
                NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
                NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
                NOTE_D4, NOTE_G3, NOTE_C4,
                NOTE_D4, NOTE_G3, NOTE_C4
                };

// 用陣列儲存兩隻老虎的節奏
int noteDurations[] = { quarter, quarter, quarter, quarter,
                        quarter, quarter, quarter, quarter,
                        quarter, quarter, half,
                        quarter, quarter, half,
                        eigth, eigth, eigth, eigth, quarter, quarter,
                        eigth, eigth, eigth, eigth, quarter, quarter,
                        quarter, quarter, half,
                        quarter, quarter, half
                      };

void setup() {
  pinMode(buzzerPin, OUTPUT);                 // 設置蜂鳴器腳位為輸出
  Serial.begin(9600);
  size = sizeof(melody) / sizeof(melody[0]);  // 計算儲存整首歌陣列的大小
}

void loop() {
  // 播放音樂
  for (int i = 0; i < size; i++) {
    int duration = noteDurations[i];
    tone(buzzerPin, melody[i], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
  delay(1000);  // 停頓一秒
}

# Arduino 呼吸燈專題 (Arduino Breathlight Project)
## 前言 
此專題受 [Joshua Hrisko](https://makersportal.com/blog/2020/3/27/simple-breathing-led-in-arduino) 啟發，並將國中、高中基礎數學結合知識，以達到科普教育的目的，希望能起到普及數學以及程式設計的目的。

適合讀這篇文章的人：
1. 對於國高中數學有基礎認識
2. 想要學習 Arduino 並且做一個簡單專題
3. 想藉由 Arduino 來學習數學
4. 有設計科普教材需求

在此文章中，將會學習到：
1. 函式的設計與使用方式
2. 將操作LED的方式，建構成數學模型
3. 知道甚麼是「平滑」的函數

## 先備知識與器材 Preliminary
在開始實作前，需要先準備一些基礎知識
1. **直線方程式中的點斜式 Point-slope**
    給定不相同兩點 $P_1(x_1,y_1),P_2(x_2,y_2)$，其斜率為 $m=\dfrac{y_2-y_1}{x_2-x_1}$，則通過兩點之直線為
    $$
    y-y_1=m(x-x_1)
    $$
2. **for迴圈 for loop**
    ```arduino
    for(起始狀態; 終止條件; 遞增) {
      執行動作;
    }
    ```
    以下為一個程式範例，這邊使用序列埠監控視窗(Serial Monitor)來查看迴圈的變化，Ctrl+Shift+M 開啟，或是在視窗工具列選擇 '工具(Tools)'->'序列埠監控視窗(Serial Monitor)'
    ```arduino
    void setup() {
      Serial.begin(9600);
      for(int i=0; i<10; i++){
        Serial.println(i); // 輸出 0~9
      }
    }
    void loop() {
    }
    ```
5. **RGB LED**
6. **Arduino UNO**


## 基本技巧 Beginner
### 變數
一般來說，當一個數值是變動的(例如腳位不定要選取9~11)我們會在寫程式上習慣使用變數(variable)儲存，如下
```arduino=
int R_pin = 9;    // Red 以 9 號腳位做為輸出
int G_pin = 10;   // Green 以 10 號腳位做為輸出
int B_pin = 11;   // Blue 以 11 號腳位做為輸出
void setup() {
  pinMode(R_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
}
void loop() {
}
```
其中`R_pin, G_pin, B_pin`三者為變數(variable)，儲存了9, 10, 11這三個數值。當想要修改腳位位置時，只要改動 1~3 行程式的數字即可。
    
### 函式
在程式語言裏頭，也是有類似數學中的函數 $f(x)$ 的概念，但有一些差異在，因為在程式語言裏頭，需要給定資料型態，如 `int, float, double` 等等，所以一個完整的函式會有以下形式：
```arduino=
int add(int a, int b){
  return a+b; // 回傳 a+b
}
void setup() {
  Serial.begin(9600);
  int a = 10; 
  int b = 5;
  int sum;
        
  sum = add(a,b);
  Serial.println(sum); // 輸出 15
}
void loop() {
}
```

### 第一個呼吸燈
最簡單的單色呼吸燈，在 [Joshua Hrisko](https://makersportal.com/blog/2020/3/27/simple-breathing-led-in-arduino) 中給出的最簡單呼吸燈模型，是以 $f(x)=x$ 這個線性函數構造的。

用點斜式來理解這個函數。$$P_1(0,0),\quad P_2(255,255)$$ 可以得到一斜率為 $m=1$的直線方程式 
\begin{equation}
    y=x
\end{equation}以下為程式碼範例
```arduino=
int R_pin = 9;    // Red 以 9 號腳位做為輸出
int G_pin = 10;   // Green 以 10 號腳位做為輸出
int B_pin = 11;   // Blue 以 11 號腳位做為輸出
void setup() {
  pinMode(R_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
}
void loop() {
  for(int i=0; i<256; i++) {
    analogWrite(R_pin, i);
    delay(10);
  }
}
```
實際上操作後，只有看到LED進行「吸」這個動作後突然就熄滅了，這樣跟原作者還有我們認知的呼吸燈好像不太一樣。所以這邊「呼」的概念就要建立起來。

LED燈亮暗要靠 `analogWrite(pin, value)` 控制 `value` 的數值，上述從暗到亮的過程是從 $0$ 至 $255$，反過來說要讓他從亮到暗，就得從 $255$ 至 $0$。

一樣給定兩個點 $$P_1(510,0),\quad P_2(255,255)$$ 從 $255$ 至 $0$ 的斜率為 $m=-1$ ，其直線方程式為 

$$
y-255=-(x-255)
$$

將兩段函數組合在一起可以得到

$$
\begin{cases}
y=x, &\text{ for } x\in[0,255], \\
y-255=-(x-255), &\text{ for }x\in[255,510].
\end{cases}
$$ 一般會稱此種分段定義的函數為分段函數(piecewise function)

如果畫出圖形，觀察可以得知是以 $x=255$ 對稱的函數，我們可以用絕對值表示

\begin{equation}
    y-255 = -\lvert x-255 \rvert, \text{ for }x\in[0,510]
\end{equation}

以下為程式碼

```arduino
int R_pin = 9;    // Red 以 9 號腳位做為輸出
int G_pin = 10;   // Green 以 10 號腳位做為輸出
int B_pin = 11;   // Blue 以 11 號腳位做為輸出

// 定義的分段函數
int piecewiseFunction(int x) {
  int y;
  y = -abs(x-255) + 255;
  return y;
}
void setup() {
  pinMode(R_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
}
void loop() {
  int R_light;
  for(int i=0; i<510; i++) {
    R_light = piecewiseFunction(i);
    analogWrite(R_pin, R_light);
    delay(10);
  }
}
```
實際做出來的效果就有「呼吸」的感覺了。

## 中等技巧 Intermediate
### 呼吸的基本函數

>是不是對稱分段函數，都會有呼吸的效果呢？該怎麼設計這樣的分段函數?

第一個問題，觀察LED燈變化的過程，從暗到亮對應到函數的斜率為 $1$，從亮到暗對應到函數的斜率為 $-1$，這件事情在暗示**呼吸的過程似乎跟斜率有關**。

對於第二個問題，也可以藉由觀察得到，呼吸的變化過程必須要「連續」的，舉第一個呼吸燈中的程式碼，沒有設計第二段函數的話，執行的過程就「不連續」。

上述的兩個概念其實就是微積分中討論函數的 **遞增性、遞減性** 與 **連續性**。

常見的連續函數有
1. 多項式函數 $P(x)=x^2+x-1$
2. 指數函數 $f(x)=2^x$
3. 根號函數 $f(x)=\sqrt{x+1}$
4. 絕對值函數 $f(x)=\vert x \vert$
5. 三角函數 $\sin{(x)}$, $\cos{(x)}$

其中絕對值函數 $f(x)=\vert x \vert$ 與二次多項式函數 $g(x)=x^2$ 有遞增與遞減的區間，可用於製作會「呼吸的函數」。

Joshua Hrisko 給了幾個設計好的函數。其中一個由圓的方程式而來，考慮以半徑$r=255$，圓心為$(0,255)$的圓方程式

\begin{equation}
    y^2+(x-255)^2 = 255^2
\end{equation}

移項開根號，可以得到上半圓的函數
\begin{equation}
    y=\sqrt{255^2-(x-255)^2}
\end{equation}

程式碼的範例為下

```arduino
int R_pin = 9;    // Red 以 9 號腳位做為輸出
int G_pin = 10;   // Green 以 10 號腳位做為輸出
int B_pin = 11;   // Blue 以 11 號腳位做為輸出

// 定義上半圓函數
int upperCircleFunction(int x) {
  int y;
  y = sqrt(pow(255.0, 2.0)-pow(x-255.0, 2.0));
  return y;
}
void setup() {
  pinMode(R_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
}
void loop() {
  int R_light;
  for(int i=0; i<510; i++) {
    R_light = upperCircleFunction(i);
    analogWrite(R_pin, R_light);
    delay(10);
  }
}
```
### 呼吸的週期
就像呼吸的快慢一樣，我們也可以將函數做週期長短的改變，呈現視覺上呼吸快慢的變化。

`void loop()` 執行一次為一個週期，在上述程式碼中，固定都是以 $i=0$ 到 $i=509$ 為一個週期，換句話說一次呼吸會做 $1+509=510$ 次的變化。

假設現在一次週期有 $N$ 次變化，以 $x=\frac{N}{2}$ 做對稱軸時，第一條線段會通過 $P_1(0,0),P_2(\frac{N}{2},255)$，第二條線段會通過$P_2(\frac{N}{2},255),P_3(N,0)$。將上述的分段函數寫成

\begin{cases}
    y = \dfrac{510}{N}x, &\text{for } x\in\left[0,\frac{N}{2}\right], \\
    y-255 = -\dfrac{510}{N}\left(x-\frac{N}{2}\right), &\text{for } x\in\left[\frac{N}{2},N\right].
\end{cases} 用絕對值表示的話

\begin{align}
    y
    & =-\dfrac{510}{N}\left\vert x-\frac{N}{2} \right\vert+255 \\
    & = 255\left(1-\frac{2}{N}\left\vert x-\frac{N}{2} \right\vert\right) \\
    & = 255\left(1-\left\vert \frac{2x}{N}-1 \right\vert\right)
\end{align}

```arduino
int R_pin = 9;    // Red 以 9 號腳位做為輸出
int G_pin = 10;   // Green 以 10 號腳位做為輸出
int B_pin = 11;   // Blue 以 11 號腳位做為輸出
int NumPoint = 200; // 調整數值的大小來改變閃爍的快慢
// 定義的分段函數
int piecewiseFunction(int x, int NumPoint) {
  float y;
  y = 255.0 *(1.0-abs(2.0*x/NumPoint - 1.0));
  return int(y);
}
void setup() {
  pinMode(R_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
}
void loop() {
  int R_light;
  for(int i=0; i<NumPoint; i++) {
    R_light = piecewiseFunction(i, NumPoint);
    analogWrite(R_pin, R_light);
    delay(10);
  }
}
```


\begin{equation}
\end{equation}


### RGB參數式

## 進階技巧 Advanced
### 分段線性插植 Piecewise Linear Interpolation
### ChatGPT
## 思考
### 為何顏色看起來會有所不同?
### 如何設計出有「美感」呼吸燈
### 更「自然」的呼吸燈
參考高斯函數 Gaussian Wave in [Joshua Hrisko](https://makersportal.com/blog/2020/3/27/simple-breathing-led-in-arduino)
## 參考資料 Reference
1. Hrisko, J. (2020). Arduino Breathing LED Functions. Maker Portal. https://makersportal.com/blog/2020/3/27/simple-breathing-led-in-arduino

/* Arduino Nano with HC-12, JoyStick, TB6612FNG, 2DCMotor
 * Retrofit the recycle IRRemote car
 * Slave code
 * 
 * HC-12 Setting
 * Baud Rate:2400
 * Channel:001
 * Mode:FU3
 * Power:P8
 * 
 * Enjoy the racing game
 * Let's start playing
 * 
 * Made by Yu-Chun Chen  (EricChen) 2022.03.21
 */

#include <EasyTransfer.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //建立軟體串列埠腳位 (RX, TX)

int x, y;            // 抓取x.y值
int checkx, checky;  // 紀錄x.y值
int delaytime = 10;  // 延遲時間
long LastTime;       // 紀錄最後一次發送訊號間隔時間
long Interval = 500; // 容許最後一次發送訊號間隔區間

//Pin Setting
int PWMA = 5;
int AIN1 = 9;
int AIN2 = 10;

int PWMB = 6;
int BIN1 = 7;
int BIN2 = 8;

int LED = 4;
int HC12 = 11;

//create object
EasyTransfer ET;

struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t gox;
  int16_t goy;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

void setup() {
  Serial.begin(2400);    // 建立串口序列埠
  mySerial.begin(2400);  // 建立HC-12串口序列埠

  ET.begin(details(mydata), &mySerial);  // 開啟EasyTransfer

  pinMode(LED, OUTPUT);     // LED燈
  //前進後退
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  //左右轉
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  digitalWrite(LED, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void loop() {
  if (ET.receiveData()) {        // 如果ET收到訊息
    x = mydata.gox;              // 將 mydata中的gox賦予x
    y = mydata.goy;              // 將 mydata中的goy賦予y
    //Serial.println(x);
    //Serial.println(y);

    if (x <= 30 && x >= (-30)) {   // x小於30大於-30
      analogWrite(PWMA, 0);
      digitalWrite(LED, LOW);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      delay(delaytime);
    }
    if (x >= 30) {                 // x大於30 checkx輸出x值
      digitalWrite(LED, HIGH);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      checkx = x;
      analogWrite(PWMA, checkx);
      delay(delaytime);
    }
    if (x <= (-30)) {              // x小於-30 checkx輸出x的絕對值
      digitalWrite(LED, HIGH);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      checkx = abs(x);
      analogWrite(PWMA, checkx);
      delay(delaytime);
    }

    if (y <= 30 && y >= (-30)) {   // y小於30大於-30
      analogWrite(PWMB, 0);
      digitalWrite(LED, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
      delay(delaytime);
    }
    if (y >= 30) {                 // y大於30 checky輸出y值
      digitalWrite(LED, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      checky = y;
      analogWrite(PWMB, checky);
      delay(delaytime);
    }
    if (y <= (-30)) {              // y小於-30 checky輸出y的絕對值
      digitalWrite(LED, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      checky = abs(y);
      analogWrite(PWMB, checky);
      delay(delaytime);
    }
    LastTime = millis();
  }
  
  if ((millis() - LastTime) >= Interval) {
    digitalWrite(LED, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
}

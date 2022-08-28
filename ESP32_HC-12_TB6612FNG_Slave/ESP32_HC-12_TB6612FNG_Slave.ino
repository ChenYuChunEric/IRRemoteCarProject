/* ESP32 with HC-12, JoyStick, TB6612FNG, 2DCMotor
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
 * Made by Yu-Chun Chen  (EricChen) 2022.05.02
 */

#include <EasyTransfer.h>
#include <analogWrite.h>

#define RXD2 16  //(RX2)
#define TXD2 17 //(TX2)
#define HC12 Serial2  //Hardware serial 2 on the ESP32

int x, y;            // 抓取x.y值
int checkx, checky;  // 紀錄x.y值
int delaytime = 10;  // 延遲時間
long LastTime;       // 紀錄最後一次發送訊號間隔時間
long Interval = 500; // 容許最後一次發送訊號間隔區間

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

int LED = 17;
int PWMA = 32, AIN1 = 5, AIN2 = 18;
int PWMB = 33, BIN1 = 19, BIN2 = 23;
int xrange = 50, yrange = 50;

void setup() {
  Serial.begin(2400);    // 建立串口序列埠
  HC12.begin(2400, SERIAL_8N1, RXD2, TXD2);
  ET.begin(details(mydata), &mySerial);  // 開啟EasyTransfer

  pinMode(LED, OUTPUT);
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

    if (x <= xrange && x >= (-xrange)) {   // x小於50大於-50
      analogWrite(PWMA, 0);
      digitalWrite(LED, LOW);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      delay(delaytime);
    }
    if (x > xrange) {                 // x大於50 checkx輸出x值
      digitalWrite(LED, HIGH);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      checkx = x;
      analogWrite(PWMA, checkx);
      delay(delaytime);
    }
    if (x < (-xrange)) {              // x小於-50 checkx輸出x的絕對值
      digitalWrite(LED, HIGH);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      checkx = abs(x);
      analogWrite(PWMA, checkx);
      delay(delaytime);
    }

    if (y <= yrange && y >= (-yrange)) {   // y小於50大於-50
      analogWrite(PWMB, 0);
      digitalWrite(LED, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
      delay(delaytime);
    }
    if (y > yrange) {                 // y大於50 checky輸出y值
      digitalWrite(LED, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      checky = y;
      analogWrite(PWMB, checky);
      delay(delaytime);
    }
    if (y < (-yrange)) {              // y小於-50 checky輸出y的絕對值
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

//Slave

#include <EasyTransfer.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //建立軟體串列埠腳位 (RX, TX)

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

void setup() {
  Serial.begin(2400);    // 建立串口序列埠
  mySerial.begin(2400);  // 建立HC-12串口序列埠

  ET.begin(details(mydata), &mySerial);  // 開啟EasyTransfer

  pinMode(4, OUTPUT);     // LED燈
  //前進後退
  pinMode(5, OUTPUT);     // AIN1
  pinMode(6, OUTPUT);     // AIN2
  //左右轉
  pinMode(9, OUTPUT);     // BIN1
  pinMode(10, OUTPUT);    // BIN2

  digitalWrite(4, LOW);   // LED燈
  digitalWrite(5, LOW);   // AIN1
  digitalWrite(6, LOW);   // AIN2
  digitalWrite(9, LOW);   // BIN1
  digitalWrite(10, LOW);  // BIN2
}

void loop() {
  if (ET.receiveData()) {        // 如果ET收到訊息
    x = mydata.gox;              // 將 mydata中的gox賦予x
    y = mydata.goy;              // 將 mydata中的goy賦予y
    Serial.println(x);
    Serial.println(y);

    if (x <= 30 && x >= (-30)) {   // x小於30大於-30
      analogWrite(5, 0);
      analogWrite(6, 0);
      digitalWrite(4, LOW);
      delay(delaytime);
    }
    if (x >= 30) {                 // x大於30 checkx輸出x值
      digitalWrite(4, HIGH);
      checkx = x;
      analogWrite(5, checkx);
      delay(delaytime);
    }
    if (x <= (-30)) {              // x小於-30 checkx輸出x的絕對值
      digitalWrite(4, HIGH);
      checkx = abs(x);
      analogWrite(6, checkx);
      delay(delaytime);
    }

    if (y <= 30 && y >= (-30)) {   // y小於30大於-30
      analogWrite(9, 0);
      analogWrite(10, 0);
      digitalWrite(4, LOW);
      delay(delaytime);
    }
    if (y >= 30) {                 // y大於30 checky輸出y值
      digitalWrite(4, HIGH);
      checky = y;
      analogWrite(9, checky);
      delay(delaytime);
    }
    if (y <= (-30)) {              // y小於-30 checky輸出y的絕對值
      digitalWrite(4, HIGH);
      checky = abs(y);
      analogWrite(10, checky);
      delay(delaytime);
    }
    LastTime = millis();
  }

  if ((millis() - LastTime) >= Interval) {
    digitalWrite(4, HIGH);   // LED燈
    digitalWrite(5, LOW);    // AIN1
    digitalWrite(6, LOW);    // AIN2
    digitalWrite(9, LOW);    // BIN1
    digitalWrite(10, LOW);   // BIN2
  }
}

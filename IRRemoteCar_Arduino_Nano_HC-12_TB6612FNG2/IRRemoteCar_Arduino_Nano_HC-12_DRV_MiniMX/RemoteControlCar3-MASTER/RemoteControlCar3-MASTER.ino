/* Arduino Nano with HC-12, JoyStick, TB6612FNG, 2DCMotor
 * Retrofit the recycle IRRemote car
 * Master code
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

int x, y;
int checkx, checky;

//create object
EasyTransfer ET;

struct SEND_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t gox;
  int16_t goy;
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;

void setup() {
  Serial.begin(2400);
  mySerial.begin(2400);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &mySerial);
}

void loop() {
  x = analogRead(A0);
  y = analogRead(A1);


  mydata.gox = map(x, 0, 1023, -255, 255);
  mydata.goy = map(y, 0, 1023, 255, -255);

  ET.sendData();
  checkx = x;
  checky = y;

  //Serial.println(x);
  //Serial.println(y);
  delay(30);
}

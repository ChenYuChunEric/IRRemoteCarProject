/* ESP32 with HC-12, JoyStick, TB6612FNG, 2DCMotor
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
 * Made by Yu-Chun Chen  (EricChen) 2022.05.02
 */

#include <EasyTransfer.h>

#define RXD2 16  //(RX2)
#define TXD2 17 //(TX2)
#define HC12 Serial2  //Hardware serial 2 on the ESP32

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
  HC12.begin(2400, SERIAL_8N1, RXD2, TXD2);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &HC12);
}

void loop() {
  x = analogRead(36);
  y = analogRead(39);


  mydata.gox = map(x, 0, 4096, -255, 255);
  mydata.goy = map(y, 0, 4096, 255, -255);

  ET.sendData();
  checkx = x;
  checky = y;

  Serial.println(x);
  Serial.println(y);
  delay(30);
}

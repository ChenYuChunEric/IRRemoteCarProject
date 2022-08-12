//Slave

#include <EasyTransfer.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);  //建立軟體串列埠腳位 (RX, TX)

int x, y;
int checkx, checky;
int delaytime = 10;

//create object
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t gox;
  int16_t goy;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE mydata;

void setup(){
  Serial.begin(115200);
  mySerial.begin(115200);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(mydata), &mySerial);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void loop(){
  //check and see if a data packet has come in. 
  if(ET.receiveData()){
    x = mydata.gox;
    y = mydata.goy;
  }
  if(x >= 80){
    digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    checkx = x;
    analogWrite(5,checkx);
    delay(delaytime);
  }
  else if(x <= (-80)){
    digitalWrite(4,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    checkx = abs(x);
    analogWrite(5,checkx);
    delay(delaytime);
  }
  if(y >= 80){
    digitalWrite(4,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    checky = y;
    analogWrite(6,checky);
    delay(delaytime);
  }
  else if(y <= (-80)){
    digitalWrite(4,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    checky = abs(y);
    analogWrite(6,checky);
    delay(delaytime);
  }
  else{
    digitalWrite(4,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
  }
}

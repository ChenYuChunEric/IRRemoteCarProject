//Slave
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);  //建立軟體串列埠腳位 (RX, TX)

int delaytime = 50;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}

void loop() {
  int input = mySerial.read()-48;
  if(input == 1){
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    Serial.println(input);
    delay(delaytime);
  }
  else if(input == 2){
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    Serial.println(input);
    delay(delaytime);
  }
  else if(input == 3){
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    Serial.println(input);
    delay(delaytime);
  }
  else if(input == 4){
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    Serial.println(input);
    delay(delaytime);
  }
  else if(input == 5){
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    Serial.println(input);
    delay(delaytime);
  }
  else if(input == 6){
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    Serial.println(input);
    delay(delaytime);
  }
  else if(input == 7){
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    Serial.println(input);
    delay(delaytime);
  }
  else if(input == 8){
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,HIGH);
    Serial.println(input);
    delay(delaytime);
  }
  else{
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
  }
}

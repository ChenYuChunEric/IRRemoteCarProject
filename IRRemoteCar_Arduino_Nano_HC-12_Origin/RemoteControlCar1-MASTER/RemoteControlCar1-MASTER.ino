//Master
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);  //建立軟體串列埠腳位 (RX, TX)

int input;
int delaytime = 40;
void setup() {
 Serial.begin(115200);
 mySerial.begin(115200);
 pinMode(5,INPUT);
 pinMode(6,INPUT);
 pinMode(7,INPUT);
 pinMode(8,INPUT);
}

void loop() {
  if(digitalRead(5) == HIGH && digitalRead(6) == LOW && digitalRead(7) == LOW && digitalRead(8) == LOW){
    input = 1;
    mySerial.print(input);
    Serial.println(input);
  }
  else if(digitalRead(6) == HIGH && digitalRead(5) == LOW && digitalRead(7) == LOW && digitalRead(8) == LOW){
    input = 2;
    mySerial.print(input);
    Serial.println(input);
  }
  else if(digitalRead(7) == HIGH && digitalRead(5) == LOW && digitalRead(6) == LOW && digitalRead(8) == LOW){
    input = 3;
    mySerial.print(input);
    Serial.println(input);
  }
  else if(digitalRead(8) == HIGH && digitalRead(5) == LOW && digitalRead(6) == LOW && digitalRead(7) == LOW){
    input = 4;
    mySerial.print(input);
    Serial.println(input);
  }
  else if(digitalRead(5) == HIGH && digitalRead(7) == HIGH && digitalRead(6) == LOW && digitalRead(8) == LOW){
    input = 5;
    mySerial.print(input);
    Serial.println(input);
  }
  else if(digitalRead(5) == HIGH && digitalRead(8) == HIGH && digitalRead(6) == LOW && digitalRead(7) == LOW){
    input = 6;
    mySerial.print(input);
    Serial.println(input);
  }
  else if(digitalRead(6) == HIGH && digitalRead(7) == HIGH && digitalRead(5) == LOW && digitalRead(8) == LOW){
    input = 7;
    mySerial.print(input);
    Serial.println(input);
  }
  else if(digitalRead(6) == HIGH && digitalRead(8) == HIGH && digitalRead(5) == LOW && digitalRead(7) == LOW){
    input = 8;
    mySerial.print(input);
    Serial.println(input);
  }
  else{
    input =0;
    mySerial.print(input);
  }
  delay(delaytime);
}

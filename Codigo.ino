//http://stackoverflow.com/questions/18376468/arduino-using-serial-and-software-serial-with-bluetooth-module
//http://fuenteabierta.teubi.co/2013/07/utilizando-el-modulo-serie-bluetooth-en.html
#include <SoftwareSerial.h>
#include <string.h>

#define rxPin A0
#define txPin A1

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
char myChar ;

char buffer[255];
int i = 0;
int pinVal = 0;

void setup() {
  Serial.begin(9600);   
  Serial.println("Goodnight moon!");

  mySerial.begin(9600);
  mySerial.println("Hello, world?");
  pinMode(13,OUTPUT);
  digitalWrite(13,pinVal);
  flush_buffer();
}

void loop(){
  while(mySerial.available()){
    myChar = mySerial.read();
    Serial.print(myChar);
    
   append_buffer(myChar);  
    if(myChar =='\n') {
       if(strstr(buffer,"led")!=0) {
         digitalWrite(13,pinVal^=1);
       }
       flush_buffer();
    }  
  }

  while(Serial.available()){
   myChar = Serial.read();
   mySerial.print(myChar);
  }
  
}

void flush_buffer() {
  for(int j=0;j<=i;j++) {
    buffer[j] = 0;
  }
  i = 0;
}

void append_buffer(char c) {
  if(i<255) {
    buffer[i++] = c;
  } else {
    flush_buffer();
  }
}

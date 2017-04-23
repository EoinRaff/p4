#include <SoftwareSerial.h>

const byte rxPin = 0;
const byte txPin = 1;  

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup()  
{

  mySerial.begin(9600); 
 
}

void loop() 
{  

  char c = mySerial.read();
  mySerial.print(c); 

  delay(500);
  
  
}

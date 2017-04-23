#include <SoftwareSerial.h>

const byte rxPin = 0;
const byte txPin = 1;

const int ledPin = 12; 

int incomingByte;

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup()  
{
   mySerial.begin(9600);

   Serial.begin(9600);

   //pinMode(rxPin, INPUT);
   //pinMode(txPin, OUTPUT);

   pinMode(ledPin, OUTPUT);

   Serial.println("Start Listening...");
}

void loop() 
{

   

  
  if (mySerial.available())
  { 

      incomingByte = mySerial.read();

      Serial.println(incomingByte,DEC);

      //Serial.print((char)mySerial.read());

       //if(incomingByte == 2) 
       //Serial.println("Change has happened");
      
  } 

 

     if(incomingByte == 2) {
     Serial.println("Change has happened");

     digitalWrite(ledPin, HIGH);

     } else {

      digitalWrite(ledPin, LOW);
      
     }

  

 


  
}

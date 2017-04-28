//#include <Serial.h>

const byte rxPin = 0;
const byte txPin = 32;

const byte butPin = 5;
int buttonState;

int byteToSend = 1;
// set up a new serial object
//Serial mySerial = Serial  (rxPin, txPin);


void setup() {
  // put your setup code here, to run once:

  Serial5.begin(9600);

  pinMode(butPin, INPUT);
  

  

}

void loop() {
  // put your main code here, to run repeatedly:

  //buttonState = digitalRead(butPin);

 
 // if (buttonState == HIGH) {
  byteToSend = 2; 
  Serial5.write(byteToSend);


  delay (500);
  //mySerial.println(byteToSend);
  
  //} else if(buttonState == LOW) {

  byteToSend = 1;
  Serial5.write(byteToSend);
  //mySerial.println(byteToSend);
 
 // }

   delay(500);
  
  

 

}

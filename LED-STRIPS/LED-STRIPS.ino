
int led = 12;
bool turnOnLights = false;

void setup() {                
  // initialize the digital pin as an output.
   pinMode(led, OUTPUT); 
   Serial.begin(9600);
}


void loop() {



     digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  

  
}

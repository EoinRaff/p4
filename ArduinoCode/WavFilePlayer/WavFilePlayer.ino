#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playWav1;
AudioPlaySdWav           playWav2;
AudioOutputI2S           audioOutput; // Use one of these 3 output types: Digital I2S, Digital S/PDIF, or Analog DAC
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;

// Use these with the audio adaptor board
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

const int buttonPin1 = 24;     // the number of the pushbutton pin
const int buttonPin2 = 25;
const int buttonPin3 = 26;


int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;
int buttonState3 = 0;


 
void setup() {
  Serial.begin(9600);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
    pinMode(buttonPin1, INPUT);    
    pinMode(buttonPin2, INPUT);  
    pinMode(buttonPin3, INPUT);  


 

   
}

void playFile(const char *filename,int wavNum)
{
  Serial.print("Playing file: ");
  Serial.println(filename);
  Serial.println(wavNum);


  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);
 


  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (playWav1.isPlaying()) {
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    // sgtl5000_1.volume(vol);
  }


    
}


void loop() {

   buttonState1 = digitalRead(buttonPin1);
   buttonState2 = digitalRead(buttonPin2);
   buttonState3 = digitalRead(buttonPin3);




    if (buttonState1 == HIGH) {     
    playFile("INST6BIP.WAV",1); 
    delay(500);
  } 

  if (buttonState2 == HIGH) {     
    playFile("ISFLAK.WAV",1); 
    delay(500);
  } 

   if (buttonState3 == HIGH) {     
    playFile("SIDE.WAV",1); 
    delay(500);
  } 




  
}


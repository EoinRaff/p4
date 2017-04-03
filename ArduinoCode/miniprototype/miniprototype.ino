#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=321,69
AudioPlaySdWav           playSdWav2; //xy=326,111
AudioPlaySdWav           playSdWav3;
AudioMixer4              mixer1;         //xy=643,70
AudioMixer4              mixer2; //xy=644,137
AudioOutputI2S           i2s1;           //xy=926,90
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord5(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord6(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord7(mixer1, 0, i2s1, 0);
AudioConnection          patchCord8(mixer2, 0, i2s1, 1);
AudioControlSGTL5000    sgtl5000_1;
// GUItool: end automatically generated code


const int button0 = 24;
const int button1 = 25;
const int button2 = 26;

int buttonState0 = 0;
int buttonState1 = 0;
int buttonState2 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(7);
  SPI.setSCK(14);
  if(!(SD.begin(10))){
    while(1){
      Serial.println("Unable to read SD card");
      delay(500);
    }
  }
  
  pinMode(13, OUTPUT); //LED 
  mixer1.gain(0, 0.3);
  mixer1.gain(1, 0.3);
  mixer2.gain(0, 0.3);
  mixer2.gain(1, 0.3);
  delay(1000);
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  buttonState0 = digitalRead(button0);
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  if(buttonState0 == HIGH && !playSdWav1.isPlaying()){
    Serial.println("Start Playing 1");
    playSdWav1.play("INST6BIP.WAV");
    delay(10);
  }
  if(buttonState1 == HIGH && !playSdWav2.isPlaying()){
    Serial.println("Start Playing 2");
    playSdWav2.play("ISFLAK.WAV");
    delay(10);
  }
  if(buttonState2 == HIGH && !playSdWav3.isPlaying()){
    Serial.println("Start Playing 3");
    playSdWav3.play("SIDE.WAV");
    delay(10);
  }
}

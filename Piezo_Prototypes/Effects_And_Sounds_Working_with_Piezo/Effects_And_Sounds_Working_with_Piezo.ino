#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// Every variable for sounds and effects goes here

AudioPlaySdWav           playSdWav4;     //xy=112,348
AudioPlaySdWav           playSdWav3;     //xy=115,284
AudioPlaySdWav           playSdWav2;     //xy=118,228
AudioPlaySdWav           playSdWav1;     //xy=119,177
AudioMixer4              mixer1;         //xy=371,203
AudioMixer4              mixer2;         //xy=375,301
AudioMixer4              mixer3;         //xy=536,255
AudioFilterStateVariable filter1;        //xy=714,473
AudioEffectFlange        flange1;        //xy=715,401
AudioEffectReverb        reverb1;        //xy=719,340
AudioMixer4              mixer4;         //xy=884,265
AudioOutputI2S           i2s2;           //xy=1098,259
AudioConnection          patchCord1(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord2(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord3(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord4(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord5(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord6(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord7(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord8(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord9(mixer1, 0, mixer3, 0);
AudioConnection          patchCord10(mixer2, 0, mixer3, 1);
AudioConnection          patchCord11(mixer3, reverb1);
AudioConnection          patchCord12(mixer3, 0, mixer4, 0);
AudioConnection          patchCord13(mixer3, flange1);
AudioConnection          patchCord14(mixer3, 0, filter1, 0);
AudioConnection          patchCord15(filter1, 1, mixer4, 3);
AudioConnection          patchCord16(flange1, 0, mixer4, 2);
AudioConnection          patchCord17(reverb1, 0, mixer4, 1);
AudioConnection          patchCord18(mixer4, 0, i2s2, 0);
AudioConnection          patchCord19(mixer4, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=382,484

// For using buttons instead of Piezo
//const int button0 = 36;
//const int button1 = 37;
//const int button2 = 38;
const int buttonEffect0 = 35;
const int buttonEffect1 = 34;
//const int buttonEffect2 = 29;

// For sounds
const int piezo1 = 39;
const int piezo2 = 38;
const int piezo3 = 37;
const int piezo4 = 36;

// For Effects
//const int piezoEffect1 = 35;
//const int piezoEffect2 = 34;

#define THRESHOLD 150 // Threshold for sensitivity of Piezo's
#define EFFECTTHRESHOLD 30

// For using buttons instead of piezo
//int buttonState0 = 0;
//int buttonState1 = 0;
//int buttonState2 = 0;
int buttonStateEffect0 = 0;
int buttonStateEffect1 = 0;
//int buttonStateEffect2 = 0;

int MovementSensor = 27;

// Variables for effects
int reverbAmount = 2;
short delay_line [4096];
bool effectOn = false;

// Bytes to store the velocity of the piezo's
byte PiezoVal1 = 0;
byte PiezoVal2 = 0;
byte PiezoVal3 = 0;
byte PiezoVal4 = 0;
byte PiezoEffectVal1 = 0;
byte PiezoEffectVal2 = 0;

void setup() {

  Serial.begin(9600);

  AudioMemory(32);
  AudioMemory(8);

  sgtl5000_1.enable(); // Controls of Audio shield
  sgtl5000_1.volume(0.8);

  SPI.setMOSI(7); //Controls for SD reader
  SPI.setSCK(14); //Controls for SD reader
  if (!(SD.begin(10))) {
    while (1) {
      Serial.println("Unable to read SD card");
      delay(500);
    }
  }

  // Set gains for first mixer
  mixer1.gain(0, 0.25);
  mixer1.gain(1, 0.25);
  mixer1.gain(2, 0.25);
  mixer1.gain(3, 0.25);

  // Sets gains for second mixer
  mixer2.gain(0, 0.25);
  mixer2.gain(1, 0.25);
  mixer2.gain(2, 0.25);
  mixer2.gain(3, 0.25);

  // Set gains for third mixer
  mixer3.gain(0, 0.5);
  mixer3.gain(1, 0.5);
  delay(1000); // Probably not neccesary

  // Set gains to passthrough sound without effects
  mixer4.gain(0, 1);
  mixer4.gain(1, 0);
  mixer4.gain(2, 0);
  mixer4.gain(3, 0);

  // Initialize effects
  reverb1.reverbTime(reverbAmount); // Reverb
  flange1.begin(delay_line, 4096, 1024, 90, 0.5); // Flanger
  filter1.frequency(1000); // Bandpass filter
  filter1.resonance(2.0); // Bandpass filter

  // For use with buttons instead of piezo's
  //pinMode(button0, INPUT);
  //pinMode(button1, INPUT);
  //pinMode(button2, INPUT);
  pinMode(buttonEffect0, INPUT);
  pinMode(buttonEffect1, INPUT);
  //pinMode(buttonEffect2, INPUT);

  pinMode(MovementSensor, INPUT);
}

void loop() {

  // For use with buttons instead of piezo's
  //buttonState0 = digitalRead(button0);
  //buttonState1 = digitalRead(button1);
  //buttonState2 = digitalRead(button2);
  buttonStateEffect0 = digitalRead(buttonEffect0);
  buttonStateEffect1 = digitalRead(buttonEffect1);
  //buttonStateEffect2 = digitalRead(buttonEffect2);

  int movementStatus = digitalRead(MovementSensor);

  // Create variable that reads the value from the piezo
  PiezoVal1 = analogRead(piezo1);
  PiezoVal2 = analogRead(piezo2);
  PiezoVal3 = analogRead(piezo3);
  PiezoVal4 = analogRead(piezo4);
  //PiezoEffectVal1 = analogRead(piezoEffect1);
  //PiezoEffectVal2 = analogRead(piezoEffect2);

  if (PiezoVal1 > THRESHOLD) {
    Serial.println("Start Playing 1");

    if (!effectOn) { // Set the mixer to passthrough sound without effects
      mixer4.gain(0, 1);
      mixer4.gain(1, 0);
      mixer4.gain(2, 0);
      mixer4.gain(3, 0);
    }
    playSdWav1.play("FLLONG.WAV");
    delay(10);
  }

  if (PiezoVal2 > THRESHOLD) {
    Serial.println("Start Playing 2");

    if (!effectOn) {
      mixer4.gain(0, 1);
      mixer4.gain(1, 0);
      mixer4.gain(2, 0);
      mixer4.gain(3, 0);
    }
    playSdWav2.play("SIXBIP.WAV");
    delay(10);
  }

  if (PiezoVal3 > THRESHOLD) {
    Serial.println("Start Playing 3");

    if (!effectOn) {
      mixer4.gain(0, 1);
      mixer4.gain(1, 0);
      mixer4.gain(2, 0);
      mixer4.gain(3, 0);
    }
    playSdWav3.play("ISFLAK.WAV");
    delay(10);
  }

  if (PiezoVal4 > THRESHOLD) {
    Serial.println("Start Playing 4");

    if (!effectOn) {
      mixer4.gain(0, 1);
      mixer4.gain(1, 0);
      mixer4.gain(2, 0);
      mixer4.gain(3, 0);
    }
    playSdWav4.play("SITAR.WAV");
    delay(10);
  }

  // As it is right now, the effects work. but the programmed method for the interaction does not.
  // the piezo are not able to tell whether the person is still standing on the effect, which is a problem.

  // Possible Solutions:
  // - Make a PiezoThreshold that would ensure it will keep reading values as long as it is stepped. Would probably
  //   Need some testing
  // - Use another sensor e.g. buttons
  // - Make a timer that starts when the effect is pressed so it will be applied for e.g. 5 seconds at a time. Is probably not going to be effecient.


  if (movementStatus == HIGH) {
    effectOn = true;
    addReverb();
    //delay(10);
  } else {
    effectOn = false;
  }

  if (buttonStateEffect1 == HIGH) {
    effectOn = true;
    addBandpass();
   // delay(10);
  } else {
    effectOn = false;
  }
}

// Functions for effects

void addReverb () {
  //Serial.println("Reverb on!");
  mixer4.gain(0, 0);
  mixer4.gain(1, 1);
  mixer4.gain(2, 0);
  mixer4.gain(3, 0);

}

void addFlanger () {
  //Serial.println("Flanger on!");
  mixer4.gain(0, 0);
  mixer4.gain(1, 0);
  mixer4.gain(2, 1);
  mixer4.gain(3, 0);
}

void addBandpass () {
  //Serial.println("Bandpass on!");
  mixer4.gain(0, 0);
  mixer4.gain(1, 0);
  mixer4.gain(2, 0);
  mixer4.gain(3, 1);

}

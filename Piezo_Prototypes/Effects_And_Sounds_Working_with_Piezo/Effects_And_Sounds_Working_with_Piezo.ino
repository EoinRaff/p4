#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=119,177
AudioPlaySdWav           playSdWav3;     //xy=119,304
AudioPlaySdWav           playSdWav2;     //xy=120,235
AudioPlaySdWav           playSdWav4;     //xy=123,378
AudioMixer4              mixer2;         //xy=359,327
AudioMixer4              mixer1;         //xy=360,223
AudioMixer4              mixer3;         //xy=549,273
AudioEffectDelay         delay1;         //xy=653,477
AudioEffectBitcrusher    bitcrusher1;    //xy=753,314
AudioEffectReverb        reverb1;        //xy=913,470
AudioMixer4              mixer4;         //xy=1019,271
AudioOutputI2S           i2s1;           //xy=1181,260
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord3(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord4(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord5(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord6(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord7(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord8(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord9(mixer2, 0, mixer3, 1);
AudioConnection          patchCord10(mixer1, 0, mixer3, 0);
AudioConnection          patchCord11(mixer3, 0, mixer4, 0);
AudioConnection          patchCord12(mixer3, delay1);
AudioConnection          patchCord13(mixer3, bitcrusher1);
AudioConnection          patchCord14(mixer3, reverb1);
AudioConnection          patchCord15(delay1, 0, mixer3, 3);
AudioConnection          patchCord16(delay1, 0, mixer4, 2);
AudioConnection          patchCord17(bitcrusher1, 0, mixer4, 1);
AudioConnection          patchCord18(reverb1, 0, mixer4, 3);
AudioConnection          patchCord19(mixer4, 0, i2s1, 0);
AudioConnection          patchCord20(mixer4, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=426,498
// GUItool: end automatically generated code

// For Effects
const int buttonEffect0 = 35;
const int buttonEffect1 = 34;
const int buttonEffect2 = 33;

// For sounds
const int piezo1 = 39;
const int piezo2 = 38;
const int piezo3 = 37;
const int piezo4 = 36;

#define THRESHOLD 50 // Threshold for sensitivity of Piezo's

// For Buttons
int buttonStateEffect0 = 0;
int buttonStateEffect1 = 0;
int buttonStateEffect2 = 0;

// Variables for effects
int delayTime = 400;
bool effectOn = false;

// Bytes to store the velocity of the piezo's
byte PiezoVal1 = 0;
byte PiezoVal2 = 0;
byte PiezoVal3 = 0;
byte PiezoVal4 = 0;

void setup() {

  Serial.begin(9600);

  AudioMemory(160);

  sgtl5000_1.enable(); // Controls of Audio shield
  sgtl5000_1.volume(0.7);

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
  mixer3.gain(3, 0);

  // Set gains to passthrough sound without effects
  mixer4.gain(0, 0.4);
  mixer4.gain(1, 0);
  mixer4.gain(2, 0);
  mixer4.gain(3, 0);

  // Initialize effects
  bitcrusher1.bits(10);
  bitcrusher1.sampleRate(16000);
  reverb1.reverbTime(4);
  delay1.delay(1, 0);
  delay(1000);

  pinMode(buttonEffect0, INPUT);
  pinMode(buttonEffect1, INPUT);
  pinMode(buttonEffect2, INPUT);
}

void loop() {

  buttonStateEffect0 = digitalRead(buttonEffect0);
  buttonStateEffect1 = digitalRead(buttonEffect1);
  buttonStateEffect2 = digitalRead(buttonEffect2);

  // Create variable that reads the value from the piezo
  PiezoVal1 = analogRead(piezo1);
  PiezoVal2 = analogRead(piezo2);
  PiezoVal3 = analogRead(piezo3);
  PiezoVal4 = analogRead(piezo4);

  if (PiezoVal1 > THRESHOLD) {
    Serial.println("Start Playing 1");

    if (!effectOn) { // Set the mixer to passthrough sound without effects
      mixer4.gain(0, 0.4);
      mixer4.gain(1, 0);
      mixer4.gain(2, 0);
      mixer4.gain(3, 0);
      mixer3.gain(3, 0);
      delay1.delay(0, 0);
    }
    playSdWav1.play("FLLONG.WAV");
    delay(10);
  }

  if (PiezoVal2 > THRESHOLD) {
    Serial.println("Start Playing 2");

    if (!effectOn) {
      mixer4.gain(0, 0.4);
      mixer4.gain(1, 0);
      mixer4.gain(2, 0);
      mixer4.gain(3, 0);
      mixer3.gain(3, 0);
      delay1.delay(0, 0);
    }
    playSdWav2.play("SIXBIP.WAV");
    delay(10);
  }

  if (PiezoVal3 > THRESHOLD) {
    Serial.println("Start Playing 3");

    if (!effectOn) {
      mixer4.gain(0, 0.4);
      mixer4.gain(1, 0);
      mixer4.gain(2, 0);
      mixer4.gain(3, 0);
      mixer3.gain(3, 0);
      delay1.delay(0, 0);
    }
    playSdWav3.play("ISFLAK.WAV");
    delay(10);
  }

  if (PiezoVal4 > THRESHOLD) {
    Serial.println("Start Playing 4");

    if (!effectOn) {
      mixer4.gain(0, 0.4);
      mixer4.gain(1, 0);
      mixer4.gain(2, 0);
      mixer4.gain(3, 0);
      mixer3.gain(3, 0);
      delay1.delay(0, 0);
    }
    playSdWav4.play("SITAR.WAV");
    delay(10);
  }

  if (buttonStateEffect0 == HIGH) {
    effectOn = true;
    addDistort();
  } else {
    effectOn = false;
  }

  if (buttonStateEffect1 == HIGH) {
    effectOn = true;
    addDelay();
  } else {
    effectOn = false;
  }

  if (buttonStateEffect2 == HIGH) {
    effectOn = true;
    addReverb();
  } else {
    effectOn = false;
  }
}
// Functions for effects

void addDistort () {
  mixer4.gain(0, 0);
  mixer4.gain(1, 0.4);
  mixer4.gain(2, 0);
  mixer4.gain(3, 0);
}

void addDelay () {
  delay1.delay(0, delayTime);
  mixer4.gain(0, 0);
  mixer4.gain(1, 0);
  mixer4.gain(2, 0.4);
  mixer4.gain(3, 0);
  mixer3.gain(3, 0.7);
}

void addReverb () {
  mixer4.gain(0, 0);
  mixer4.gain(1, 0);
  mixer4.gain(2, 0);
  mixer4.gain(3, 1);
}

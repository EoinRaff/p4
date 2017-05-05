#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=119,177
AudioPlaySdWav           playSdWav3;     //xy=119,304
AudioPlaySdWav           playSdWav2;     //xy=120,235
AudioPlaySdWav           playSdWav4;     //xy=121,376
AudioMixer4              mixer1;         //xy=356,214
AudioSynthSimpleDrum     drum1;          //xy=357,410
AudioMixer4              mixer2;         //xy=359,327
AudioSynthKarplusStrong  string1;        //xy=360,467
AudioMixer4              mixer7;         //xy=553.5555114746094,292.66668701171875
AudioMixer4              mixer4;         //xy=1113.5714111328125,179.2381591796875
AudioOutputI2S           i2s1;           //xy=1319.4285278320312,281.0952949523926
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord3(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord4(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord5(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord6(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord7(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord8(playSdWav4, 1, mixer2, 3);
AudioConnection          patchCord9(mixer1, 0, mixer7, 0);
AudioConnection          patchCord10(drum1, 0, mixer7, 2);
AudioConnection          patchCord11(mixer2, 0, mixer7, 1);
AudioConnection          patchCord12(string1, 0, mixer7, 3);
AudioConnection          patchCord13(mixer7, 0, i2s1, 0);
AudioConnection          patchCord14(mixer7, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1148.888916015625,455.6667175292969
// GUItool: end automatically generated code

// For Effects
const int buttonEffect0 = 35;
const int buttonEffect1 = 34;

// For sounds
const int piezo1 = 39;
const int piezo2 = 38;
const int piezo3 = 37;
const int piezo4 = 36;

#define THRESHOLD 30 // Threshold for sensitivity of Piezo's

// For Buttons
int buttonStateEffect0 = 0;
int buttonStateEffect1 = 0;

// Variables for effects
bool effectOn = false;

// Bytes to store the velocity of the piezo's
byte PiezoVal1 = 0;
byte PiezoVal2 = 0;
byte PiezoVal3 = 0;
byte PiezoVal4 = 0;

bool startEffectOff = false; 

void setup() {

  Serial.begin(9600);

  AudioMemory(255); // This is allocateed memory blocks. One block can contain 128 ms of audio samples, corresponding with 2.9 ms.

  sgtl5000_1.enable(); // Controls of Audio shield
  sgtl5000_1.volume(0.9);

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

  // Set gains for Last sound mixer
  mixer7.gain(0, 0.33);
  mixer7.gain(1, 0.33);
  mixer7.gain(2, 0.33);
  mixer7.gain(3, 0.33);

  /*
  // Set gains for ozzy mixer
  mixer3.gain(0, 0.5);
  mixer3.gain(3, 0.5);

  // Set gains to passthrough sound without effects
  mixer4.gain(0, 0.5);
  mixer4.gain(1, 0);

  
  // Initialize Ozzy
  waveform1.begin(20, 220, WAVEFORM_SQUARE);
  waveform2.begin(20, 523.25, WAVEFORM_SAWTOOTH);

  filter1.frequency(122);
  filter1.resonance(0);

  envelope1.attack(0);
  envelope1.decay(500);
  envelope1.sustain(0.2);
  envelope1.release(600);

  envelope2.attack(0);
  envelope2.decay(1000);
  envelope2.sustain(1.0);
  envelope2.release(600);

  */

  drum1.frequency (220);
  drum1.length (1000);

  


  // Initialize effects

  pinMode(buttonEffect0, INPUT);
  pinMode(buttonEffect1, INPUT);
}

void loop() {

  buttonStateEffect0 = digitalRead(buttonEffect0);
  buttonStateEffect1 = digitalRead(buttonEffect1);

  Serial.println(buttonStateEffect0);

  //Serial.println (AudioMemoryUsageMax());
  //Serial.println (AudioProcessorUsageMax());

  // Create variable that reads the value from the piezo
  PiezoVal1 = analogRead(piezo1);
  PiezoVal2 = analogRead(piezo2);
  PiezoVal3 = analogRead(piezo3);
  PiezoVal4 = analogRead(piezo4);

  /*
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
      playSdWav1.play("SAFRIDUO.WAV");
      delay(10);
    }
  

  if (PiezoVal2 > THRESHOLD) {
    Serial.println("Start Playing 2");

    
    if (!effectOn) {
      mixer4.gain(0, 0.4);
      mixer4.gain(1, 0);
    }
    
    playSdWav2.play("LIONKING.WAV");
    delay(10);
  }

  if (PiezoVal3 > THRESHOLD) {
    Serial.println("Start Playing 3");

     

    if (!effectOn) {
      mixer4.gain(0, 0.4);
      mixer4.gain(1, 0);
    }
    
    playSdWav3.play("FREE.WAV");
    delay(10);
  }

  if (PiezoVal4 > THRESHOLD) {
    Serial.println("Start Playing 4");

     
    if (!effectOn) {
      mixer4.gain(0, 0.4);
      mixer4.gain(1, 0);
    }

    
    playSdWav4.play("SAND.WAV");
    delay(10);
  }

  */
  if (buttonStateEffect0 == HIGH) {
    effectOn = true;
    startEffectOff = true;
    //envelope1.noteOn();
    //envelope2.noteOn();



    
  

    drum1.noteOn();
    
    //addOzzy();
  } else {
    //envelope1.noteOff();
    //envelope2.noteOff();
   // effectOFF ();

    
    //effectOn = false;
    
  }
/*
  if (buttonStateEffect1 == HIGH) {
    effectOn = true;
    startEffectOff = true;

    drum1.noteOn();
    //envelope1.noteOn();
    //envelope2.noteOn();
    //addOzzy();
  } else {
    // envelope1.noteOff();
    // envelope2.noteOff();

    //effectOFF ();
    
    //effectOn = false;

  }
}
// Functions for effects

void addOzzy () {
  mixer4.gain(0, 0.4);
  mixer4.gain(1, 0.4);
}

void effectOFF () {

  if (startEffectOff) {
    //envelope1.noteOff();
    //envelope2.noteOff();
    startEffectOff = false;
    
  }

  */
}



/* Will Burgin (waburgin), 2015.
 * If you find my files helpful, please give credit!
 */
#include <Arduino.h>
#include <Canbus.h>

#include "can.h"
#include "LEDTach.h"

LEDTach::LEDTach(){
  //Initialize LED Tach pins
  pinMode(GR1, OUTPUT);
  pinMode(GR2, OUTPUT);
  pinMode(GR3, OUTPUT);
  pinMode(GR4, OUTPUT);
  pinMode(YL1, OUTPUT);
  pinMode(YL2, OUTPUT);
  pinMode(YL3, OUTPUT);
  pinMode(RD1, OUTPUT);
  pinMode(RD2, OUTPUT);
  pinMode(BL_SHIFT, OUTPUT);
  pinMode(SPKR, OUTPUT);
}

LEDTach::~LEDTach(){
  //Turn off all LED's
  digitalWrite(GR1, LOW);
  digitalWrite(GR2, LOW);
  digitalWrite(GR3, LOW);
  digitalWrite(GR4, LOW);
  digitalWrite(YL1, LOW);
  digitalWrite(YL2, LOW);
  digitalWrite(YL3, LOW);
  digitalWrite(RD1, LOW);
  digitalWrite(RD2, LOW);
  digitalWrite(BL_SHIFT, LOW);
}

//Takes the vehicles RPM from the BufferedMap and adjusts the display accordingly
//Piston engine only, rotary should be 0-12,000RPM
void LEDTach::update(int rpm) const{
  //Check shift point first.
  if(rpm >= SHIFT_POINT){
      alarm();
  }else if(rpm < 1200){
    bool ledSet[9] = {HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
    setAll(ledSet);
  }else if(rpm >= 1200 && rpm < 1700){
    bool ledSet[9] = {HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
    setAll(ledSet);
  }else if(rpm >= 1700 && rpm < 2300){
    bool ledSet[9] = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, LOW};
    setAll(ledSet);
  }else if(rpm >= 2300 && rpm < 2900){
    bool ledSet[9] = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
    setAll(ledSet);
  }else if(rpm >= 2900 && rpm < 3400){
    bool ledSet[9] = {HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW};
    setAll(ledSet);
  }else if(rpm >= 3400 && rpm < 4200){
    bool ledSet[9] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW};
    setAll(ledSet);
  }else if(rpm >= 4200 && rpm < 5000){
    bool ledSet[9] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
    setAll(ledSet);
  }else if(rpm >= 5000 && rpm < 5500){
    bool ledSet[9] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
    setAll(ledSet);
  }else if(rpm >= 5500 && rpm < 9000){
    bool ledSet[9] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
    setAll(ledSet);
  }else{
      //Skip false input
  }
  
  return;
}

void LEDTach::ready(){
  digitalWrite(GR1, HIGH);
  delay(50);
  digitalWrite(GR2, HIGH);
  delay(50);
  digitalWrite(GR3, HIGH);
  delay(50);
  digitalWrite(GR4, HIGH);
  delay(50);
  digitalWrite(YL1, HIGH);
  delay(50);
  digitalWrite(YL2, HIGH);
  delay(50);
  digitalWrite(YL3, HIGH);
  delay(50);
  digitalWrite(RD1, HIGH);
  delay(50);
  digitalWrite(RD2, HIGH);
  delay(50);
  digitalWrite(BL_SHIFT, HIGH);
  
  delay(300);

  digitalWrite(GR1, LOW);
  digitalWrite(GR2, LOW);
  digitalWrite(GR3, LOW);
  digitalWrite(GR4, LOW);
  digitalWrite(YL1, LOW);
  digitalWrite(YL2, LOW);
  digitalWrite(YL3, LOW);
  digitalWrite(RD1, LOW);
  digitalWrite(RD2, LOW);
  digitalWrite(BL_SHIFT, LOW);

  return;
}

//Waiting signal is a 2 sets of 2 LED's blinking, GR4&YL3 and YL1&RD1
void LEDTach::waiting(int time){
  //Each iteration is 1000ms.
  for(int i = 0; i < time; i++){
   digitalWrite(GR4, HIGH);
   digitalWrite(YL3, HIGH);
   delay(500);
   digitalWrite(YL1, HIGH);
   digitalWrite(RD1, HIGH);
   digitalWrite(GR4, LOW);
   digitalWrite(YL3, LOW);
   delay(500);
   digitalWrite(YL1, LOW);
   digitalWrite(RD1, LOW);
  }
  return;
}

void LEDTach::errorSD(){
  //Blink RD1 and RD 2
  digitalWrite(RD1, HIGH);
  digitalWrite(RD2, HIGH);
  delay(100);
  digitalWrite(RD1, LOW);
  digitalWrite(RD2, LOW);
  delay(100);
  digitalWrite(RD1, HIGH);
  digitalWrite(RD2, HIGH);
  delay(100);
  digitalWrite(RD1, LOW);
  digitalWrite(RD2, LOW);
  
  return;
}

void LEDTach::alarm() const{
  //Flash LED's and pulse speaker. Delay 10+10+10=30, or one read cycle.
    digitalWrite(BL_SHIFT, HIGH);
    digitalWrite(SPKR, HIGH);
    delay(10);                     
    digitalWrite(BL_SHIFT, LOW);
    digitalWrite(SPKR, LOW);
    delay(10);
    digitalWrite(BL_SHIFT, HIGH);
    digitalWrite(SPKR, HIGH);
    delay(10);
    digitalWrite(BL_SHIFT, LOW);
    digitalWrite(SPKR, LOW);
    
  return;
}

void LEDTach::setAll(bool lights[]) const{
  int tacho_lights[9] = {GR1, GR2, GR3, GR4, YL1, YL2, YL3, RD1, RD2};
  for(int i = 0; i < 9; i++){
    digitalWrite(tacho_lights[i], lights[i]);
  }
  return;
}

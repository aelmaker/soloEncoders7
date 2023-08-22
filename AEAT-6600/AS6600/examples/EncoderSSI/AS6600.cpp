#include "AS6600.h"
#include "Arduino.h"

void AS6600::init(){
  pinMode(PWRDOWN, OUTPUT);
  pinMode(Data, INPUT);
  pinMode(Clock, OUTPUT);
  pinMode(ChipSel, OUTPUT);
  pinMode(MAG_HI, INPUT);
  pinMode(MAG_LO, INPUT);

  digitalWrite(Clock, HIGH);
  digitalWrite(ChipSel, HIGH);
  digitalWrite(PWRDOWN, LOW);
}

float AS6600::readSSI(){
	unsigned long sample1 = shift();
	unsigned long sample2 = shift();
	delayMicroseconds(20); // Clock must be high for 20 microseconds before a new sample can be taken
	if (sample1 != sample2){
		return -1.0;
}
	return ((sample1 & 0xFFFF) * 360UL) / 65536.0;

}
unsigned long AS6600::shift(){
	unsigned long data = 0;
	digitalWrite(ChipSel, LOW);
  	for (int i = 0; i < 16; i++){
    data <<= 1;
    digitalWrite(Clock, LOW);
    delayMicroseconds(1);
    digitalWrite(Clock, HIGH);
    delayMicroseconds(1);
    data |= digitalRead(Data);
  }
  digitalWrite(ChipSel, HIGH);
  return data;
}

void AS6600::disable(){
	digitalWrite(PWRDOWN, HIGH);
  digitalWrite(ChipSel, LOW);
}

void AS6600::magnetError(){
  HI = digitalRead(MAG_HI);
  LO = digitalRead(MAG_LO);
}


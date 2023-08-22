#ifndef AS6600_H
#define AS6600_H

#include "Arduino.h"

class AS6600
{
public:
  AS6600(int MHI, int MLO, int PWRDOWN, int CS, int CLK, int DATA)
    :MAG_HI(MHI), MAG_LO(MLO), PWRDOWN(PWRDOWN), ChipSel(CS), Clock(CLK), Data(DATA){};
  float readSSI();
  void init();
  void disable();
  void magnetError();
  bool HI = false; 
  bool LO = false;

  private:
  unsigned long shift();
  
  //SSI
  int Data;
  int Clock;
  int ChipSel;
  //error pins
  int MAG_HI;
  int MAG_LO;
  //
  int PWRDOWN;
};

#endif
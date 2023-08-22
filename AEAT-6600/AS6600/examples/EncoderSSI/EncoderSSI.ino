#include "AS6600.h"
//AS6600(int MHI, int MLO, int PWRDOWN, int CS, int CLK, int DATA)
// if pins not use, just put "-1"
AS6600 enc(-1, -1, 8, 10, 13, 12);
void setup() {
  enc.init();
  Serial.begin(115200);
} 
          
void loop() {
  float reading = enc.readSSI();
  if (reading >= -0.5)
  {
 //   Serial.print("Reading: ");
    Serial.println(reading, 2);
  }
  delay(10);
}           
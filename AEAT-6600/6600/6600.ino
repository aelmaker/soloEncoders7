// https://github.com/bstadlbauer/aeat-6012/blob/master/arduino/aeat_6012_readout/aeat_6012_readout.ino
#include <SPI.h>

const int NCS = 10; // Chip select
const int CLK = 13; // Clock signal
const int DO = 12;  // Digital Output from the encoder which delivers me a 0 or 1, depending on the bar angle..

unsigned int sensorWaarde = 0;

void setup()
{

  Serial.begin(115200);
  Serial.println("Hello World!"); // send sample text to monitor for debug

  // Fix de tris

  pinMode(NCS, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DO, INPUT);

  ///////////////////////////////////////////////
}

void loop()
{
unsigned long data = 0;
  digitalWrite(NCS, HIGH);
  digitalWrite(CLK, HIGH);
  delayMicroseconds(1);
  digitalWrite(NCS, LOW);
  delayMicroseconds(500/1000);

	for (int i = 0; i < 16; i++){
    data <<= 1;
    digitalWrite(CLK, LOW);
    delayMicroseconds(1);
    digitalWrite(CLK, HIGH);
    delayMicroseconds(1);
    data |= digitalRead(Data);
  }
  delayMicroseconds(20);
  digitalWrite(NCS, HIGH);

  Serial.println(data, 2);

  delay(300);
}




// unsigned int readSensor() {
//   unsigned int dataOut = 0;

//   digitalWrite(CSn, LOW);
//   delayMicroseconds(1);  //Waiting for Tclkfe

//   //Passing 12 times, from 0 to 11
//   for (int x = 0; x < 12; x++) {
//     digitalWrite(CLK, LOW);
//     delayMicroseconds(1);  //Tclk/2
//     digitalWrite(CLK, HIGH);
//     delayMicroseconds(1);                        //Tdo valid, like Tclk/2
//     dataOut = (dataOut << 1) | digitalRead(DO);  //shift all the entering data to the left and past the pin state to it. 1e bit is MSB
//   }

//   digitalWrite(CSn, HIGH);  //deselects the encoder from reading
//   Serial.println(dataOut);
//   return dataOut;
// }
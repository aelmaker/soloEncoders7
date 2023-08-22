// https://github.com/bstadlbauer/aeat-6012/blob/master/arduino/aeat_6012_readout/aeat_6012_readout.ino
#include <SPI.h>

const int SSI_SPI_SEL = 10; // Chip select
const int SCK_PIN = 13;     // Clock signal
const int DOUT = 12;        // Digital Output from the encoder which delivers me a 0 or 1, depending on the bar angle..
const int NSL = 11;

unsigned int sensorWaarde = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello World!"); // send sample text to monitor for debug
  // Fix de tris
  pinMode(SSI_SPI_SEL, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(DOUT, INPUT);
  pinMode(NSL, OUTPUT);
  digitalWrite(NSL, HIGH); // enable
  delayMicroseconds(5);    // treq
  ///////////////////////////////////////////////
}

int SSI_Read()
{
  digitalWrite(NSL, HIGH); // enable
  digitalWrite(SCK_PIN, HIGH);
  digitalWrite(SSI_SPI_SEL, HIGH);
  delayMicroseconds(2); // tsw(SEL)
  // digitalWrite(NSL, LOW);
  // delayMicroseconds(1); // treq

  String dataOut = "";
  for (int i = 0; i <= 20; i++)   
  {
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(1);
    digitalWrite(SCK_PIN, HIGH);
    dataOut += String(digitalRead(DOUT));
    delayMicroseconds(1);
  }
  
  delayMicroseconds(16); // tREQ2
  Serial.println(dataOut);
  // int value = dataOut & 0x0F;
  // Serial.println(strtol(dataOut.c_str(), NULL, 2));

  return 0;
}

void loop()
{

  SSI_Read();
  delay(1000);
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
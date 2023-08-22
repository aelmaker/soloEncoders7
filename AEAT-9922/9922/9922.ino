// https://github.com/bstadlbauer/aeat-6012/blob/master/arduino/aeat_6012_readout/aeat_6012_readout.ino
#include <SPI.h>


//SPI4 USED 


const int NCS = 5;          //M0            io5   // Chip select
const int SCK = 18;         //M2            io18      // Clock signal
const int DOUT = 23;        //M3 Data out   io23         // Digital Output from the encoder which delivers me a 0 or 1, depending on the bar angle..
const int NSL = 19;         //M1  MOSI      IO19
const int Msel = 26;        // MSEL     if msel = 0 - ssi   if msel =1 - spi                                        
//SPID = MOSI = data out            
//SPIQ = MISO = data in
unsigned int sensorWaarde = 0;

void setup() {

  Serial.begin(115200);
  Serial.println("Hello World!");  //send sample text to monitor for debug

  //Fix de tris

  pinMode(SSI_SPI_SEL, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(DOUT, INPUT);
  pinMode(NSL, OUTPUT);

  ///////////////////////////////////////////////
}



void loop() {
String dataOut = "";

  digitalWrite(NSL, HIGH);
  digitalWrite(SSI_SPI_SEL, HIGH);

  digitalWrite(SCK_PIN, HIGH);
  delayMicroseconds(3);
  digitalWrite(NSL, LOW);
  delayMicroseconds(1);  //treq

  for (int i = 0; i <= 19; i++) {
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(1);
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(1);
    dataOut += String( digitalRead(DOUT));   
  //  Serial.print(dataOut);     
 //  Serial.print("");   
  }

  // int value = dataOut & 0x0F; 
   Serial.println(strtol(dataOut.c_str(), NULL, 2));   

  digitalWrite(SSI_SPI_SEL, HIGH);  
  delayMicroseconds(1);  //treq2

  digitalWrite(NSL, HIGH);
  delayMicroseconds(1);  //tNSLH  
  digitalWrite(NSL, LOW); 

 // Serial.println(" "); 
  delay(100); 
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
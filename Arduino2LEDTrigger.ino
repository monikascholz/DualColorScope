#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINRed 10 // this is the red LED signal pin
#define PINGreen 6 // this is the green LED signal pin
int camPin = 9; // camera trigger on Pin 

int frameTime = 9; // time between frames in ms (for double our normal frame rate use 8 ms)

// global red/green switch
boolean RED = true;
unsigned long oldTime = 0; // last time update

// initialize both LED rings
Adafruit_NeoPixel stripRed = Adafruit_NeoPixel(12, PINRed, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripGreen = Adafruit_NeoPixel(12, PINGreen, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600); //serial port for monitoring
  pinMode(camPin, OUTPUT);      // sets the digital pin as output for trigger signal
  stripRed.begin(); //intitialize LED array
  stripRed.show(); // Initialize all pixels to 'off'
  stripGreen.begin(); //intitialize LED array
  stripGreen.show(); // Initialize all pixels to 'off'
}

void loop() {
 unsigned long currentTime = micros();
 if(currentTime - oldTime >= frameTime*1000) {
     capture(camPin);
     RED = !RED;
     // trigger off for a short time (minimum is 100 ns for camera)
     //delayMicroseconds(10);
     digitalWrite(camPin, LOW);
     delayMicroseconds(10);
     Serial.println(currentTime - oldTime);
     oldTime = currentTime;  
  }
}

void capture(int camPin)
{
  if (RED){
     for(uint16_t i=0; i<stripRed.numPixels(); i++) {
        stripRed.setPixelColor(i, stripRed.Color(1,0,0));
     }
     for(uint16_t i=0; i<stripGreen.numPixels(); i++) {
        stripGreen.setPixelColor(i, stripGreen.Color(0,0,0));
  }
  }
  else{
    for(uint16_t i=0; i<stripRed.numPixels(); i++) {
        stripRed.setPixelColor(i, stripRed.Color(0,0,0));
    }
     for(uint16_t i=0; i<stripGreen.numPixels(); i++) {
        stripGreen.setPixelColor(i, stripGreen.Color(0,255,0));
     }
  }
 
  stripGreen.show();
  stripRed.show();
  digitalWrite(camPin, HIGH);
}
//void capture(int camPin)
//{
//  if (RED){
//    takeBF(camPin);
//  }
//  else{
//    takeFL(camPin);
//  }
//}
//void takeBF(int camPin) {
//  colorWipe(&stripGreen, stripGreen.Color(0, 0, 0)); // Green off
//  // switch LED array to red
//  colorWipe(&stripRed, stripRed.Color(4, 0, 0)); // Red
//  // start camera trigger
//  digitalWrite(camPin, HIGH);
//  }
//
//void takeFL(int camPin) {
//  // switch LED array to green
//  colorWipe(&stripRed, stripRed.Color(0, 0,0)); // Red off
//  colorWipe(&stripGreen, stripGreen.Color(0, 255,0)); // Green
//  // start camera trigger
//  digitalWrite(camPin, HIGH);
//  }
//  
//
//// Fill the dots one after the other with a color
//void colorWipe(Adafruit_NeoPixel *strip, uint32_t c) {
//  for(uint16_t i=0; i<(*strip).numPixels(); i++) {
//    (*strip).setPixelColor(i, c);
//  }
//  (*strip).show();
//}
//
//


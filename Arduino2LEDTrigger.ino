#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINRed 6 // this is the red LED signal pin
#define PINGreen 8 // this is the green LED signal pin
int camPin = 9; // camera trigger on Pin 

int frameTime = 8; // time between frames in ms (for double our normal frame rate use 8 ms)

// global red/green switch
boolean RED = true;
unsigned long oldTime = 0; // last time update

// initialize both LED rings
Adafruit_NeoPixel stripRed = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripGreen = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600); //serial port for monitoring
  pinMode(camPin, OUTPUT);      // sets the digital pin as output for trigger signal
  stripRed.begin(); //intitialize LED array
  stripRed.show(); // Initialize all pixels to 'off'
  stripGreen.begin(); //intitialize LED array
  stripGreen.show(); // Initialize all pixels to 'off'
}

void loop() {
 unsigned long currentTime = millis();
 if(currentTime - oldTime >= frameTime) {
     capture(camPin);
     RED = !RED;
     
     // trigger off for a short time (minimum is 100 ns for camera)
     delayMicroseconds(10);
     digitalWrite(camPin, LOW);
     delayMicroseconds(10);
     Serial.println(currentTime - oldTime);
     oldTime = currentTime;  
  }
}


void takeBF(int camPin) {
  
  //switch green off
  stripGreen.show();
  // switch LED array to red
  colorWipe(stripRed, stripRED.Color(5, 0, 0)); // Red
  // start camera trigger
  digitalWrite(camPin, HIGH);
  }

void takeFL(int camPin) {
  //turn red off
  stripRed.show();
  // switch LED array to red
  colorWipe(stripGreen, stripGreen.Color(0, 255,0)); // Green
  // start camera trigger
  digitalWrite(camPin, HIGH);
  }
  
void capture(int camPin)
{
  if (RED){
    takeBF(camPin);
  }
  else{
    takeFL(camPin);
  }
}
// Fill the dots one after the other with a color
void colorWipe(strip, uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}


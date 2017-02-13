#include <Adafruit_NeoPixel.h>


#ifdef __AVR__
  #include <avr/power.h>
#endif


#define PIN 6 // this is the LED signal pin
int camPin = 9; // camera trigger on Pin 

int frameTime = 8; // time between frames in ms (for double our normal frame rate use 8 ms)

// global red/green switch
boolean RED = true;
unsigned long oldTime = 0; // last time update

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


void capture(int camPin)
{
  if (RED){
    takeBF(camPin);
  }
  else{
    takeFL(camPin);
  }
}


void setup() {
  Serial.begin(9600); //serial port for monitoring
  pinMode(camPin, OUTPUT);      // sets the digital pin as output for trigger signal
  strip.begin(); //intitialize LED array
  strip.show(); // Initialize all pixels to 'off'

}
void loop() {
 unsigned long currentTime = millis();
 if(currentTime - oldTime >= frameTime) {
     capture(camPin);
     // trigger off for a short time (minimum is 100 ns for camera)
     RED = !RED;
     delayMicroseconds(10);
     digitalWrite(camPin, LOW);
     delayMicroseconds(10);
     Serial.println(currentTime - oldTime);
     oldTime = currentTime;  
  }
}


void takeBF(int camPin) {
  //Serial.println("Red");
  // switch LED array to red
  colorWipe(strip.Color(5, 0, 0)); // Red
  // start camera trigger
  digitalWrite(camPin, HIGH);
  }

void takeFL(int camPin) {
  //Serial.println("Fl");
  // switch LED array to red
  colorWipe(strip.Color(0, 255,0)); // Green
  // start camera trigger
  digitalWrite(camPin, HIGH);
  }

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}


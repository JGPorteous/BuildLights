#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
char currentCommand;
bool hasDelay = true;
bool showStateUpdate = true;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  Serial.begin(115200);
  Serial.println("BuildLights V1 Starting...");

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  runLed(strip.Color(255, 0, 0), 50); // Green
  
  currentCommand = 'z';
  Serial.println("Available commands: ");
  Serial.println("Whipe: qwertyu");
  Serial.println("Solid: QWERTYU");
  Serial.println("Theater Chase: asdfghj");
  Serial.println("Running LED: ASDFGHJ");
  Serial.println("Rainbow: 1, Theater Chase Rainbow: 2");
  Serial.println("Off: o");
  
}

void loop() {
  checkForCommand();

  updateLights(currentCommand);
  if (hasDelay == true)
  {   
    delay(50);
    updateLights('o'); //maybe this can also be optional
  }
}

bool checkForCommand() {
  while(Serial.available() > 0) {
    char tmpCommand;
    tmpCommand = Serial.read(); 
    if ((tmpCommand >= 'a' && tmpCommand <= 'z')
      || (tmpCommand >= 'A' && tmpCommand <= 'Z')
      || (tmpCommand >= '0' && tmpCommand <= '9')) {
      
      currentCommand = tmpCommand;
      showStateUpdate = true;
      Serial.print("Got Command: ");
      Serial.println(currentCommand);
      return true;
      }
    }
    return false;
}

void updateLights(char command) {
  switch (command) {
//Whipe Effect with Delay
    case 'q' :
      updateState("wipeGreen");
      hasDelay = true;
      colorWipe(strip.Color(255, 0, 0), 50); // Green
      colorWipe(strip.Color(0, 0, 0), 50); // Off
      break;

    case 'w' :
      updateState("wipeRed");
      hasDelay = true;
      colorWipe(strip.Color(0, 255, 0), 50); // Red
      colorWipe(strip.Color(0, 0, 0), 50); // Off
      break;
   
    case 'e' :
      updateState("wipeBlue");
      hasDelay = true;
      colorWipe(strip.Color(0, 0, 255), 50); // Blue
      colorWipe(strip.Color(0, 0, 0), 50); // Off
      break;

    case 'r' :
      updateState("wipeYellow");
      hasDelay = true;
      colorWipe(strip.Color(255, 255, 0), 50); // Yellow
      colorWipe(strip.Color(0, 0, 0), 50); // Off
      break;

    case 't' :
      updateState("wipeCyan");
      hasDelay = true;
      colorWipe(strip.Color(255, 0, 255), 50); // Cyan
      colorWipe(strip.Color(0, 0, 0), 50); // Off
      break;

    case 'y' :
      updateState("wipePurple");
      hasDelay = true;
      colorWipe(strip.Color(0, 255, 255), 50); // Purple
      colorWipe(strip.Color(0, 0, 0), 50); // Off
      break;

    case 'u' :
      updateState("wipeWhite");
      hasDelay = true;
      colorWipe(strip.Color(255, 255, 255), 50); // White
      colorWipe(strip.Color(0, 0, 0), 50); // Off
      break;

//Solid On
    case 'Q' :
      updateState("wipeGreen");
      hasDelay = false;
      colorWipe(strip.Color(255, 0, 0), 10); // Green
      break;

    case 'W' :
      updateState("wipeRed");
      hasDelay = false;
      colorWipe(strip.Color(0, 255, 0), 10); // Red
      break;
   
    case 'E' :
      updateState("wipeBlue");
      hasDelay = false;
      colorWipe(strip.Color(0, 0, 255), 10); // Blue
      break;

    case 'R' :
      updateState("wipeYellow");
      hasDelay = false;
      colorWipe(strip.Color(255, 255, 0), 10); // Yellow
      break;

    case 'T' :
      updateState("wipeCyan");
      hasDelay = false;
      colorWipe(strip.Color(255, 0, 255), 10); // Cyan
      break;

    case 'Y' :
      updateState("wipePurple");
      hasDelay = false;
      colorWipe(strip.Color(0, 255, 255), 10); // Purple
      break;

    case 'U' :
      updateState("wipeWhite");
      hasDelay = false;
      colorWipe(strip.Color(255, 255, 255), 10); // White
      break;

//Theater Chase
    case 'a' :
      updateState("theaterChaseGreen");
      hasDelay = false;
      theaterChase(strip.Color(255, 0, 0), 50); // Green
      break;

    case 's' :
      updateState("theaterChaseRed");
      hasDelay = false;
      theaterChase(strip.Color(0, 255, 0), 50); // Red
      break;
   
    case 'd' :
      updateState("theaterChaseBlue");
      hasDelay = false;
      theaterChase(strip.Color(0, 0, 255), 50); // Blue
      break;

    case 'f' :
      updateState("theaterChaseYellow");
      hasDelay = false;
      theaterChase(strip.Color(255, 255, 0), 50); // Yellow
      break;

    case 'g' :
      updateState("theaterChaseCyan");
      hasDelay = false;
      theaterChase(strip.Color(255, 0, 255), 50); // Cyan
      break;

    case 'h' :
      updateState("theaterChasePurple");
      hasDelay = false;
      theaterChase(strip.Color(0, 255, 255), 50); // Purple
      break;

  case 'j' :
      updateState("theaterChaseWhite");
      hasDelay = false;
      theaterChase(strip.Color(255, 255, 255), 50); // White
      break;

//Running LED
    case 'A' :
      updateState("runLedGreen");
      hasDelay = false;
      runLed(strip.Color(255, 0, 0), 50); // Green
      break;

    case 'S' :
      updateState("runLedRed");
      hasDelay = false;
      runLed(strip.Color(0, 255, 0), 50); // Red
      break;
   
    case 'D' :
      updateState("runLedBlue");
      hasDelay = false;
      runLed(strip.Color(0, 0, 255), 50); // Blue
      break;

    case 'F' :
      updateState("runLedYellow");
      hasDelay = false;
      runLed(strip.Color(255, 255, 0), 50); // Yellow
      break;

    case 'G' :
      updateState("runLedCyan");
      hasDelay = false;
      runLed(strip.Color(255, 0, 255), 50); // Cyan
      break;

    case 'H' :
      updateState("runLedPurple");
      hasDelay = false;
      runLed(strip.Color(0, 255, 255), 50); // Purple
      break;

  case 'J' :
      updateState("runLedWhite");
      hasDelay = false;
      runLed(strip.Color(255, 255, 255), 50); // White
      break;

// Special Effects (sometimes long running)

    case '1':
      updateState("rainbow");
      hasDelay = false;
      rainbow(10);
      break;

    case '2':
      updateState("theaterChaseRainbow");
      hasDelay = false;
      theaterChaseRainbow(60);
      break;
    
 

    case '6': 
      updateState("test command");
      hasDelay = false;
      runLed(strip.Color(255, 0, 0), 50);
      break;

// Lights Off     
    case 'o':
      updateState("lightsOff");
      hasDelay = true;
      colorWipe(strip.Color(0, 0, 0), 10); // Off
      break;

  }
}

void updateState(String state) 
{
  if (showStateUpdate) {
    Serial.println(state);
    showStateUpdate = false;
  }
} 

void loopOLD() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Green
  colorWipe(strip.Color(0, 255, 0), 50); // Red
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50); // Red
  theaterChase(strip.Color(0, 0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void runLed(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(i, 0);
    if (checkForCommand()) 
      return;
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      if (checkForCommand()) 
        return;
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      if (checkForCommand()) 
        return;
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
        if (checkForCommand()) 
          return;
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
        if (checkForCommand()) 
          return;
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        if (checkForCommand()) 
          return;
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
        if (checkForCommand()) 
          return;
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

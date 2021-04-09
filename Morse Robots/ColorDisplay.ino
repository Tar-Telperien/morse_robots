/* ColorDisplay - Color Beacon for use with Core Spartan system
  (c) Modern Robotics Inc. 2016  http://www.modernroboticsinc.com
      
  The Color Beacon uses an RGB LED to produce over 16 million colors. A color can be
  set by the user via programming or it can be set to RED or BLUE team colors by swiping 
  a magnet over the side of the device.
  
  This example cycles through the 8 main colors(states) the Color Beacon can be set to.
    
  Connections:
  Color Beacon(default addr 0x4C *0x26*)    = Port I2C
  *Arduino Address*
  
  NOTE* When using any Core sensor and its accompanying library, the pinMode() function
  should never be used as some sensors change or hold the mode as input/output at 
  certain times to function correctly. All mode initializations are automatically done 
  when the sensor constructor is calbeacon. i.e. CORE_TOUCH().
  
  Core Spartan language reference can be found at http://modernroboticsinc.com/spartan  
  Arduino language reference can be found at http://arduino.cc/en/Reference/HomePage  
  Windows: USE SERIAL MONITOR -> Ctrl+Shift+M
  Mac:     USE SERIAL MONITOR -> Cmd+Shift+M
-------------------------------------------------------------------------------------------*/
#include "CORE.h"

// Create an instance of class CORE_TRICOLOR named beacon on port S3
CORE_COLOR_BEACON beacon;

void setup(){
// No setup code required
}


/* 
* LETTER TO MORSE CODE KEY
* . = RED, - = BLUE, GREEN = NEXT LETTER/CHAR
* space = WHITE
* 
*/

// .-
void A(){
  beacon.setColor(beacon.RED); 
  delay(200);
  beacon.setColor(beacon.BLUE); 
  delay(200);
}
// -...
void B(){
  beacon.setColor(beacon.BLUE); 
  delay(200);
  beacon.setColor(beacon.RED); 
  delay(200);
  beacon.setColor(beacon.OFF);
  delay(200);
  beacon.setColor(beacon.RED);
  delay(200);
  beacon.setColor(beacon.OFF);
  delay(200);
  beacon.setColor(beacon.RED);
  delay(200);
  beacon.setColor(beacon.OFF);
  delay(200);
}

void space(){
  beacon.setColor(beacon.WHITE);
  delay(200);
}

// Encode letters to lights
void encode(String s){
  for (int i = 0; i < s.length(); i++){
    if (s.charAt(i) == 'A')
      A();
    if (s.charAt(i) == 'B')
      B();
    if (s.charAt(i) == ' ')
      space();
    
    // NEXT CHAR
    beacon.setColor(beacon.GREEN);
    delay(200);
  }
  // END OF MESSAGE
  beacon.setColor(beacon.WHITE);
  delay(300);
  beacon.setColor(beacon.OFF);
  delay(300);
  beacon.setColor(beacon.OFF);
  delay(300);
}

// Enter string, encode, and transmit
void loop(){
  beacon.setColor(beacon.OFF);

  String message = "A B";
  encode(message);
}

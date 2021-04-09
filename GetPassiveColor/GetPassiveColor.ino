/* GetPassiveColor - Color Sensor for use with Core Spartan Controller
  (c) Modern Robotics Inc. 2015  http://www.modernroboticsinc.com
        
  The Color Sensor uses various channels of color to determine the approximate color of an 
  object. This data includes a color number that corresponds to the color line in the 
  documentation, as well as raw and adjusted readings. Best results will be attained in a 
  well-lit area and the object no more than 7cm away from the sensor. 
  
  This example takes passive readings at 50Hz and displays all data registers to the serial 
  monitor. When in passive mode, the white LED does not turn on, making it harder for the 
  sensor to detect the exact color of a surface but useful when detecting the color of a light 
  source. Press the Touch Sensor to take a single passive color reading of a light source and 
  display the reading values to the serial terminal. Refer to the documentation for more 
  information on calibrating and descriptions of the returned values.
    
  Connections:
  Color Sensor(default addr 0x3C *0x1E*)  = Port I2C
  Touch Sensor(TOUCH)                     = Port D7
  *Arduino Address*
  
  NOTE* When using any Core sensor and its accompanying library, the pinMode() function
  should never be used as some sensors change or hold the mode as input/output at 
  certain times to function correctly. All mode initializations are automatically done 
  when the sensor constructor is called. i.e. CORE_PCB(). 
    
  Core Spartan language reference can be found at http://modernroboticsinc.com/spartan  
  Arduino language reference can be found at http://arduino.cc/en/Reference/HomePage  
  Windows: USE SERIAL MONITOR -> Ctrl+Shift+M
  Mac:     USE SERIAL MONITOR -> Cmd+Shift+M
-------------------------------------------------------------------------------------------*/
#include "CORE.h"

// Create an instance of the class CORE_COLOR_SENSOR named color using the default I2C Address
CORE_COLOR_SENSOR color;

// Create an instance of the class CORE_DIGITAL named push on port D7
CORE_DIGITAL push(7);

// Create four variables to store all the color Sensor readings
int red, green, blue, white;

void setup(){
  // Initialize serial communications at 9600 baud
  Serial.begin(9600);
  
  // Set the mode of the color Sensor to PASSIVE at 50Hz 
  color.colorSetup(color.PASSIVE, color.SIXTY);
}

void loop(){
   // When the touch sensor is pressed, determine color number value 
   Serial.println("Press the TOUCH sensor to read the COLOR sensor");
   while(push.read() == 0);
   Serial.print("Color Number = ");
   Serial.println(color.getColorNumber()); 
   
   // Get the current values of the three color channels and the white channel.
   color.getColorValue(red, green, blue, white);
   Serial.print("Color Value Red = ");
   Serial.println(red);
   Serial.print("Color Value Green = ");
   Serial.println(green);
   Serial.print("Color Value Blue = ");
   Serial.println(blue);
   Serial.print("Color Value White = ");
   Serial.println(white);
   
   // Return 6 bit color index in one byte to the Serial Monitor
   Serial.print("Color Index = 0x");
   Serial.println(color.getColorIndex(), HEX);
   
   // Get the analog values of the three primary color channels with an intenstity correction all at once.
   // 0xFF is the strongest signal.
   color.getRGBIndex(red, green, blue);
   Serial.print("Color Index Red = 0x");
   Serial.println(red, HEX);
   Serial.print("Color Index Green = 0x");
   Serial.println(green, HEX);
   Serial.print("Color Index Blue = 0x");
   Serial.println(blue, HEX);

   // Get the analog values of the three primary color channels with an intensity correction individually.
   // 0xFF is the strongest signal.
   Serial.print("Color Red = 0x");
   Serial.println(color.getRGB(color.RED), HEX);
   Serial.print("Color Green = 0x");
   Serial.println(color.getRGB(color.GREEN), HEX);
   Serial.print("Color Blue = 0x");
   Serial.println(color.getRGB(color.BLUE), HEX);
   
   // Get the analog value of the color channels in a 16 bit format.
   // This color reading has much more detail than the index reading.
   color.getColorReading(red, green, blue, white);
   Serial.print("Color Reading Red = ");
   Serial.println(red);
   Serial.print("Color Reading Green = ");
   Serial.println(green);
   Serial.print("Color Reading Blue = ");
   Serial.println(blue);
   Serial.print("Color Reading White = ");
   Serial.println(white);
   
   // Get the analog value of the color channel adjusted by the calibration values.
   color.getColorNormalized(red, green, blue, white);
   Serial.print("Color Normalized Red = ");
   Serial.println(red);
   Serial.print("Color Normalized Green = ");
   Serial.println(green);
   Serial.print("Color Normalized Blue = ");
   Serial.println(blue);
   Serial.print("Color Normalized White = ");
   Serial.println(white);
   
   Serial.println("******************************");
}

/*  Fabduino Dimming
 *  
 *  This program will fade the on-board LED on pin D-5
 *  Using the analogWrite() function.
 *  
 *  */

// The Fabduino has an LED attached to pin 5 ( D5)
int led_pin = 5;
int fading = 0;

void setup() {
  // initialize digital pin 5 (D5) as an output.  
  pinMode(led_pin, OUTPUT);
  analogWrite(led_pin, fading);
  
  /*  AnalogWrite : int value
   *   the value is a % between 0 and 100
   *   
   *   0 = 0% or always OFF
   *  As the LED is ACTIVE LOW, this will mean it is ON
   *  
   *  255 = 100% or always ON
   *  As the LED is ACTIVE LOW, this will mean it is OFF
   *  
   */
  
}

void loop() {
  // Decrease brightness
  fading = fading + 2;

  // Make sure it does not exceed maximum of 100% (255)
  if(fading >= 255)
  {
    // When it does, start agian at 0
    fading = 0;
  }

  // Set new value as output
  analogWrite(led_pin, fading);

  // delay 50ms as else far too quick...
  delay(50); 
  
}

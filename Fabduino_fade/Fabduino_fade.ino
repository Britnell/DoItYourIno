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
  
}

void loop() {
  fading += 2;

  if(fading >= 255)
  {
    fading = 0;
  }
  
  analogWrite(led_pin, fading); // 1 or HIGH switches the LED OFF
  delay(50); 
  
}

/*  Fabduino Blink
 *  
 *  This program will blink the on-board LED on pin D-5
 *  
 *  */

// The Fabduino has an LED attached to pin 5 ( D5)
int led_pin = 5;

void setup() {
  // initialize digital pin 5 (D5) as an output.  
  pinMode(led_pin, OUTPUT);
  
}

int wait = 500;

// the loop function runs over and over again forever
void loop() {
  
  
  digitalWrite(led_pin, 0); // 0 or LOW switches the LED ON
  delay(300);
  // Delay creates a 1000ms = 1s delay before executing the next line of code
  digitalWrite(led_pin, 1); // 1 or HIGH switches the LED OFF
  delay(300); 
  
}

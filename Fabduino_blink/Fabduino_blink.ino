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

int wait = 200;

// the loop function runs over and over again forever
void loop() {
  
  digitalWrite(led_pin, 0); // 0 or LOW = 0V switches the LED ON
  // Also correct: 
  //  digitalWrite(5, 0);
  //  digitalWrite(led_pin, LOW);
  
  delay(500);
  // Delay creates a 1000ms = 1s delay before executing the next line of code
    
  digitalWrite(led_pin, 1); // 1 or HIGH = 5V switches the LED OFF
  // Also correct:
  //  digitalWrite(5, 1);
  //  digitalWrite(led_pin, HIGH);
  
  delay(500); 
  
}

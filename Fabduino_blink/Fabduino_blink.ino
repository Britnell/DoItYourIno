/*  Fabduino Blink
 *  
 *  This program will blink the on-board LED on pin D-5
 *  The LED will be ON when we write a LOW / 0 to the led-pin
 *  It will be OFF when we write a HIGH / 1 to the led-pin
 *  
 *  Try varying the delay time to see the effect
 *  and replace the delay time with the 'wait' variable
 *  
 *  Try using #define to replace 0 and 1 with LED_ON and LED_OFF
 *  
 *  */

// The Fabduino has an LED attached to pin 5
int led_pin = 5;

void setup() {
  // initialize digital pin 5 (D5) as an output.  
  // Function : pinMode(pin, INPUT or OUTPUT );
  // Reference : https://www.arduino.cc/en/Reference/PinMode
  pinMode(led_pin, OUTPUT);
  
}

int wait = 500;

// the loop function runs over and over again forever
void loop() {
  
  
  digitalWrite(led_pin, 0); // 0 or LOW switches the LED ON
  delay(1000);
  // Delay creates a 1000ms = 1s delay before executing the next line of code
  digitalWrite(led_pin, 1); // 1 or HIGH switches the LED OFF
  delay(1000); 
  
}

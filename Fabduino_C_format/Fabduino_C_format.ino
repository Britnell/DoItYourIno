/*  Fabduino 
 *   
 *   Title, say what it does, or what it needs
 *  
 *  */

// Include libraries
#include <Servo.h>

// Defines - constant variables
#define PI     3.46218

// Global variables
int led_pin = 5;
int wait = 10;

// CODE CAN NOT BE HERE
// CODE MUST BE INSIDE setup() or main()

void setup() {
  // This code will run ONCE
  // always when chip starts up 

  // setup variables
  // these only exist within the setup{ ...} function
  int led_pin_mode = OUTPUT;
  
  // In here, set things up, configurations
  // e.g. Input and Output
  pinMode(led_pin, OUTPUT);
  
}



void loop() {
  // the loop function repeats forever
  // main program, because most things run in a loop

   // Here you will control, calculate things or read sensors
  digitalWrite(led_pin, 0); // 0 or LOW switches the LED ON
  delay(2*wait);
  
  // Delay creates a 1000ms = 1s delay before executing the next line of code
  digitalWrite(led_pin, 1); // 1 or HIGH switches the LED OFF
  delay(wait); 

  wait = wait + wait/ 10;
  
  
}

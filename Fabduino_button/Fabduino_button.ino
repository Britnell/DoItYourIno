
#define LED_ON    0
#define LED_OFF   1

int led_pin = 5;
int but_pin = 2;
int dela = 300;

void setup() {
  // Set pins as OUTPUTs and INPUTs
  pinMode(led_pin, OUTPUT);
  pinMode(but_pin, INPUT);
  
}

void loop() {
  int b = digitalRead(but_pin);
  // returns an int / bool for state:
  // HIGH or 1 if pin connected to 5V
  // LOW or 0 if pin is connected to 0V
  
  if( b){
    //  Pin HIGH when button is NOT pressed
    digitalWrite(led_pin, LED_OFF);
  }
  else
  {
    //  Pin LOW when button is pressed
    digitalWrite(led_pin, LED_ON);
  }

  delay(300);   
}

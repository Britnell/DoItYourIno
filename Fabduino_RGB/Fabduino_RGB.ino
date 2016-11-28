// #define LOW 0

#define LED_ON    0
#define LED_OFF   1

int led_pin = 5;

int led_green = 3;
int led_blue = 4;
int led_red = 1;



void setup() {
  // initialize digital pins as outputs to control the LEDs
  pinMode(led_green,OUTPUT);
  pinMode(led_blue,OUTPUT);
  pinMode(led_red,OUTPUT);
  
  RGB_off( );     // first turn the LED OFF

  delay(1000);    // wait 1s before beginning program
  
}


void loop() {
  // LED goes from red to green, and back to red.
  
  RGB_purple();
  delay(2000);    // LED will be Purple for 2s
  
  RGB_yellow();
  delay(1000);    // LED will be Yellow for 1s
  
  RGB_green();     
  delay(1000);     // LED will be Green for 1s
  
  RGB_yellow();
  delay(500);    // LED will be Yellow for 0.5s

  RGB_purple();
  delay(3000);    // LED will be Purple for 3s
}

void RGB_off( )
{
  digitalWrite(led_red, LED_OFF);
  digitalWrite(led_green, LED_OFF);
  digitalWrite(led_blue, LED_OFF);
}

void RGB_purple( )
{
  digitalWrite(led_red, LED_ON);
  digitalWrite(led_green, LED_OFF);
  digitalWrite(led_blue, LED_ON);
}

void RGB_yellow( )
{
  digitalWrite(led_red, LED_ON);
  digitalWrite(led_green, LED_ON);
  digitalWrite(led_blue, LED_OFF);
}

void RGB_green( )
{
  digitalWrite(led_red, LED_OFF);
  digitalWrite(led_green, LED_ON);
  digitalWrite(led_blue, LED_OFF);
}

//

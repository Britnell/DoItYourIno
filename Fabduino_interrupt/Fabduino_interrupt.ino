/*
 *  Fabduino Arduino Tutorial
 */
 
#define LED_ON    0
#define LED_OFF   1

int led_pin = 5;
int but_pin = 2;

long debounce_time, last_button;

void setup() {
  // Set LED as OUTPUT  & turn it OFF
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LED_OFF);
  
  // initialise interrupt pin as INPUT
  pinMode(but_pin, INPUT);

  attachInterrupt(digitalPinToInterrupt(but_pin), interrupt_function, FALLING);
  // Alternatively, also correct is :
  //   attachInterrupt( INT0, interrupt_function, FALLING);
  
  /*  * * Function : 
   *   
   *   --- attachInterrupt( )
   *  
   *  Inputs
   *  
   *    1. Interrupt number
   *     To be found in datasheet.
   *     On atmega328:
   *        INT0 - D2 = pin 2 
   *        INT1 - D3 = pin 3
   * 
   *    2. Interrupt function-name
   *        Name of function containing interrupt
   *        code will be run everytime interrupt is triggered
   *    
   *    3. Trigger mode
   *        Interrupt can be triggered on different 'edges'
   *        
   *        RISING  - Signal changes from LOW to HIGH state
   *        FALLING - Signal changes from HIGH to LOW state
   *        CHANGE  - Triggers on both RISING and FALLING
   *        
   */

   // Initialise variables with values
   last_button = 0;
   debounce_time = 300;
}

int math = 10;
void loop() {
  math = math + math /11;

  digitalWrite(led_pin, LED_OFF);
  delay(1200);   
}


// This function is only executed then the interrupt is triggered
void interrupt_function( ){
  digitalWrite(led_pin, LED_ON);
  
}

void interrupt_toggle( ) {
    if( led_state ){   // when led_state == 1
      led_state = 0;
      digitalWrite(led_pin, LED_OFF);
    }
    else{   // when led_state == 0
      led_state = 1;
      digitalWrite(led_pin, LED_ON);
    }
    
  //
}

void interrupt_debounce( ) {

  // software debouncing
  if( millis() -last_button > debounce_time) // enough time has passed (since last button) )
  {
      if( led_state ){    // when led_state == 1
        led_state = 0;
        digitalWrite(led_pin, LED_OFF);
      }
      else{ // when led_state == 0
        led_state = 1;
        digitalWrite(led_pin, LED_ON);
      }
      last_button = millis(); // time in milli-seconds
      // time of last button press
  }
}

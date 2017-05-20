/* 
 *  IR remote USB device
 *  
 *  Combines Arduino Micro's built in USB capabilities
 *  with IR receiver and old IR TV-remote
 *  
 *  Decoding remote button-codes was done before with another program.
 *  Here functions are mapped to buttons and buttons are de-bounced etc.
 *  
 *  Code is Shared for Open Source
 *  / Thomas Britnell 
 *  github.com/Britnell
 */

#include "remote.h"


/*  puls = the Arduino pin that is connected to the IR-receiver output. 
 *  It is only used to set as input. */
#define puls  0

/* Len = Length of array necessary to record incoming decoded IR-message */
#define Len   68

/* DEBUG = used to turn debug serial-messages on and off  */
#define DEBUG 0

/* warten = Delay, sleep time in between main loop iterations. Also used in debouncing calculations  */
#define warten  50

/* pulses array = used to record incoming message through interrupt, and is then split into
 *  ontime and offtime */
unsigned long  pulses[Len];
unsigned long  ontime[Len];
unsigned long  offtime[Len];
int counter ;

/* msg  = ontime pulse width is then decoded and stored as binary array in msg */
uint8_t msg[Len];
uint8_t m;

/* buff = char array used for serial print messages */
char buff[100];

unsigned long cmd;
unsigned int checkbyte, ir_cmd;

/* Variables for accelerated mouse scrolling and button debouncing */
uint8_t mouse_step = 4;
unsigned long last_push=0;
uint8_t holding = 0;
uint8_t SUP, SDOWN, SLEFT, SRIGHT, SSHUTTL, SSHUTTR, SPOW, SEJECT;

/* Reset temporary arrays to 0 for new decoding process.  */
void rst(){
  counter = 0;
  m=0;
  for(int i=0; i<Len; i++)
  {
    pulses[i] = 0;
    ontime[i] = 0;
    offtime[i] = 0;
    msg[i] = 0;
  }
  k_letgo();
  // done
}

/* Reset binary msg array only */
void msg_begin(){
  m = 0;
  for(int i=0; i<Len; i++){
    msg[i] = 0;
  }
  Mouse.begin();
  
}

// #    #   #   #   #   # SETUP
// #
void setup() {
  // Set IR pin as input and attach interrupt
  pinMode(puls, INPUT);
  // Interrupt on pin-CHANGE to record rising & falling, hence on-time
  attachInterrupt(INT0, IntCounter, CHANGE);
  
  if(DEBUG) {
  Serial.begin(9600);
  Serial.println("New life");
  }
  
  rst();
}   // Eo setup()

uint8_t printed = 0;
unsigned long L;

//    #   #   #   #   #   #   #   LOOP
//    #
void loop() {
  /* counter = number of bits read by interrupt
   *   
   */
  
  if(counter>=Len)    // when message read complete
  {
    //printray_l(pulses, Len);
    
    for( int i=0; i<Len-1; i++)
    {
      // OFF
      if(i%2==0)
      { 
        offtime[i]=pulses[i+1]-pulses[i];
        if(offtime[i] > 600 && offtime[i] < 760)
        {
          //Serial.print(".\t");
        }
        //
      }
      else  // ON
      {
        ontime[m]=pulses[i+1]-pulses[i];
        
        if( ontime[m] > 300 && ontime[m] < 710)
        {
          msg[m] = 0;
          m++;
        }
        else if( ontime[m] > 1300 && ontime[m] < 1750)
        {
          msg[m] = 1;
          m++;
        }
        else if(ontime[m] > 4000)
        {
          msg_begin();
        }
        
      }
      
    } // Eo for

    if(DEBUG){
      //printray_l(pulses, Len);
      printray_l(ontime, 32);             // print on pulse times
      printray_d(msg, 32);                // print binary msg
      //sprintf(buff,"length: %d\n", m);    // print msg length
      //Serial.print(buff);
    }
    
    checkbyte = IR_checkbyte(msg);    
    
    ir_cmd = IR_decode(msg);
    
    if(DEBUG){
      sprintf(buff,"checkbyte: %d,\tremote: %d", checkbyte, ir_cmd);
      Serial.print(buff);
    }
    
    if(checkbyte==CHECKBYTE)
    {
      // identify holding donw button
      if( millis()-last_push <=4*warten){
        holding = 1;
      }
      else{
        holding = 0;
      }
      
      CmdList(ir_cmd);
      last_push = millis();
        
    }   // Eo if
    rst();
  }
  else
  {
    //holding = 0;
    //CmdList(0);
  }
  
  delay(warten);
  
  // Eo loop
}

void CmdList(unsigned int cmd)
{
  // 
  if(!holding)
  {
    k_letgo();
  }
  
  switch(cmd)
  {
        case BB0:
          //Serial.print("0");
          break;
        case BB1:
          //Serial.print("1");
          break;
        case B2:
          //Serial.print("2");
          break;
        case B3:
          //Serial.print("3");
          break;
        case BPOW:
          if(!SPOW)
            k_logout();
          break;
        case BEJECT:
          if(!SEJECT)
            k_ctraltdel();
          break;
        case BUP:
          m_dynamic();
          Mouse.move( 0,-mouse_step,0);
          //Keyboard.write( KEY_UP_ARROW );
          break;
        case BDOWN:
          m_dynamic();
          Mouse.move( 0,mouse_step,0);
          //Keyboard.write( KEY_DOWN_ARROW );
          break;
        case BLEFT:
          m_dynamic();
          Mouse.move( -mouse_step,0,0);
          //Keyboard.write( KEY_LEFT_ARROW );
          break;
        case BRIGHT:
          m_dynamic();
          Mouse.move( mouse_step,0,0);
          //Keyboard.write( KEY_RIGHT_ARROW );
          break;
        case BSHUTTL:
          if(!SSHUTTL){
            Mouse.click(MOUSE_LEFT);
            SSHUTTL=1;  }
          break;
        case BSHUTTR:
          if(!SSHUTTR){
            Mouse.click(MOUSE_RIGHT);
            SSHUTTR=1;  }
          break;
        case BDISPLAY:
          k_alt(KEY_F5);
          break;
        case BAUDIO:
          k_alt(KEY_F6);
          break;
        default:
          k_letgo();
          break;
      }// Eo switch
      //
}

void m_dynamic()
{
  if(!holding)
    mouse_step=3;
  else if(mouse_step<12)
    mouse_step++;
}

void k_letgo(){
  SUP=0;
  SDOWN=0;
  SLEFT=0;
  SRIGHT=0;
  SSHUTTL=0;
  SSHUTTR=0;
  SPOW=0;
  SEJECT=0;
  Mouse.release(MOUSE_LEFT);
  Mouse.release(MOUSE_RIGHT);
}

void k_alt(int F){
  Keyboard.press( KEY_LEFT_ALT );
  Keyboard.write( F );
  Keyboard.release(  KEY_LEFT_ALT );
}
void k_logout(){
  Keyboard.press( KEY_LEFT_GUI );
  Keyboard.write( 'l' );
  Keyboard.release(  KEY_LEFT_GUI );
}

void k_ctraltdel(){
  Keyboard.press( KEY_LEFT_CTRL );
  Keyboard.press( KEY_LEFT_ALT );
  Keyboard.write( KEY_DELETE );
  Keyboard.release(  KEY_LEFT_ALT );
  Keyboard.release(  KEY_LEFT_CTRL );
}

unsigned int IR_decode( uint8_t *ray){

  unsigned int dec = 0;
  unsigned int sing;
    
  for(int i=0; i<16; i++)
  {
    // bits 16 to 31
    if( ray[i+16]){
      sing = 1;
      dec |= (sing<<i);
    } 
  }

  return dec;
}

unsigned int IR_checkbyte( uint8_t *ray){

  unsigned int dec = 0;
  unsigned int sing;
    
  for(int i=0; i<16; i++)
  {
    
    if( ray[i]){
      sing = 1;
      dec |= (sing<<i);
    } 
  }

  return dec;
}

unsigned long ray_to_int( uint8_t *ray, int len){

  unsigned long dec = 0;
  unsigned long sing;
    
  for(int i=0; i<len; i++)
  {
    
    if( ray[i]){
      sing = 1;
      dec |= (sing<<i);
    } 
  }

  return dec;
}


// ISR //ON PIN CHange
void IntCounter( ) {
  if(counter <Len)  // if buffer is not full
  {
    pulses[counter] = micros();
    counter++;
  }
}

void printray_l( unsigned long *ray, int len)
{
  for(int i=0; i<len; i++)
  {
    Serial.print(ray[i]);
    Serial.print("\t");
  }
  Serial.print("\n");
}

void printray_d( uint8_t *ray, int len)
{
  for(int i=0; i<len; i++)
  {
    Serial.print(ray[i]);
    Serial.print(",");
  }
  Serial.print("\n");
}

// End

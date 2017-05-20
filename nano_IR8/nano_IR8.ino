/* 
 *  IR remote control receiver 
 *  - IR receiver on Interrupt pin
 *  - Here Nano, where INT0 is on pin D2
 *  
 *  Reads and decode 32-bit IR command
 *  First 16 bit = checkbyte, always the same
 *  Last 16 bit = command bytes
 *  
 *  Decode command bytes to integer, with LSB first
 *  Then display check-bytes and command bytes as int in serial
 *  
 *  Universal IR Receiver module
 *  When facing you, 3 pins:
 *  Left : Output signal
 *  Middle : ground/VSS 
 *  Right : VCC(+5V)
 *  
 *  IR output signal = active low
 *  Interrupt thus waits for falling edge, logs time in us(micro s), 
 *  then waits for next positive edge and logs again.
 *  Continues until 32bit complete, in this case 68 edges.
 *  
 *  When array complete, decoder begins.
 *  Signal is active low, but information is in the width of the ON (5V) pulses,
 *  i.e. the remote transmits constant on-time pulses at different intervals.
 *  There is a short and a long interval, which I chose arbitrarily as 1 and 0.
 *  
 *  Use this code to read remote control message bytes and identify each button.
 *  
 *  Works on any arduino with Interrupt pin.
 *  
 *  Code is Shared for Open Source
 *  / Thomas Britnell
 *  github.com/Britnell
 */

#include "remote.h"

// IR rreceiver on D2
#define puls  2
#define led   5

#define Len   68

unsigned long  pulses[Len];
unsigned long  ontime[Len];
unsigned long  offtime[Len];
int counter ;

uint8_t msg[Len];
uint8_t m;
char buff[100];
unsigned long cmd;
unsigned int checkbyte, ir_cmd;

//unsigned long timeout = 50000;  // in us

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
  // done
}

void msg_begin(){
  m = 0;
  for(int i=0; i<Len; i++){
    msg[i] = 0;
  }
}
void setup() {
  // LED
  pinMode(puls, INPUT);
  attachInterrupt(INT0, IntCounter, CHANGE);

  
  DDRB |= (1<<led);
  PORTB &= ~(1<<led);
  
  //pinMode(puls, INPUT);
  
  Serial.begin(9600);

  rst();
  
  Serial.println("New life");
  // begin
}

uint8_t printed = 0;
unsigned long L;

void loop() {
  //   L    H     L     H     L
  //   0    1     2     3     4     5     6
  //   41.. 41..  42..
  //   OFF  ON    OFF   On    OFF..
  
  if(counter>=Len)
  {
    // pulses times
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
        else{
          //Serial.print( offtime[i] );
          //Serial.print("\t");
        }
      }
      else  // ON
      {
        ontime[m]=pulses[i+1]-pulses[i];
        
        if( ontime[m] > 300 && ontime[m] < 700)
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
    
    //Serial.println();

    //printray_l(pulses, Len);
    
    //printray_l(ontime, 32);             // print on pulse times
    
    //printray_d(msg, 32);                // print binary msg
    
    //sprintf(buff,"length: %d\n", m);    // print msg length
    //Serial.print(buff);

    //cmd = ray_to_int(msg, 32);          // convert entire msg
    //sprintf(buff,"int: %ld\n", cmd);    Serial.print(buff);
    //Serial.println(cmd);

    checkbyte = IR_checkbyte(msg);    

    ir_cmd = IR_decode(msg);

    sprintf(buff,"checkbyte: %d,\tremote: ", checkbyte);
    Serial.print(buff);
    Serial.println(ir_cmd);
    
    if(checkbyte==CHCKBT)
    {
      switch(ir_cmd){
        case BB0:
          Serial.println("0");
          break;
        case BB1:
          Serial.println("1");
          break;
        case B2:
          Serial.println("2");
          break;
        case B3:
          Serial.println("3");
          break;
        case B4:
          Serial.println("4");
          break;
        case B5:
          Serial.println("5");
          break;          
        case B6:
          Serial.println("6");
          break;
        case B7:
          Serial.println("7");
          break;
        case B8:
          Serial.println("8");
          break;
        case B9:
          Serial.println("9");
          break;
        case BPOW:
          Serial.println("Power");
          break;
        case BEJECT:
          Serial.println("eject");
          break;
        case BUP:
          Serial.println("Up");
          break;
        case BDOWN:
          Serial.println("Down");
          break;
        case BLEFT:
          Serial.println("Left");
          break;
        case BRIGHT:
          Serial.println("Right");
          break;
        default:
          Serial.println("Pardon?");
          break;
      }  
    }   // Eo if
    rst();
  }
  delay(500);
  
  // Eo loop
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

// - record time
// - 
// - count
// End

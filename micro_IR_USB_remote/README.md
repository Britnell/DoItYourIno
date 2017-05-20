
# IR remote USB device

This Program Demonstrates use of TV IR-remote as USB remote device. I am using Arduino Pro Micro as a HID USB device. Additionally a 3-pin IR receiver-IC is used to receive signals from a TV IR-remote.
 
The IR-receiver signals is mapped using interrupts, it must therefore be connected to an interrupt pin on you Arduino, pin INT0 or INT1.
See [Arduino Interrupts](https://www.arduino.cc/en/Reference/AttachInterrupt). For the Arudino Pro Micro, INT0 is on pin D2.

This program demonstrates a running program that reads IR remote's signals, decodes them and performs different tasks based on different signals.

In my case, as I configured 4 buttons to move the mouse, I am not "debouncing" repeated signals from the same button.
Contrary, I was attempting to identify when a button is being help down and released to make scrolling quicker and more intuitive.
The mouse buttons on the other hand are debounced using a binary 'state'-like variable.

I hope it helps for other projects though the code is pretty specific for this case. 
Transferrable functions however are
* IR_checkbyte - turns 16 bit binary array into an integer (unsigned int, LSB first)

* ray_to_int - turns an X bit binary array into a decimal (unsigned long, LSB first)


Code includes debug-messages that can be turned on with #define DEBUG.
On Arduino Micro however, since Serial messaging is done through the otherwise USB connection, it is best to debug with Serial messages, or run code as USB device, as switching does not work / causes Problems.

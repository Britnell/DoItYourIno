##Fabduino

# Interrupt

This is an example for an interrupt set up to monitor a button signal

###Hardware
* Button, at FabLab we used the RGB-button module which has the button connected as a pull-down / active LOW.

###Functions
* pinMode(pin, INPUT);
* digitalRead( pin )
* [Arduino Reference](https://www.arduino.cc/en/Reference/)

1.  Run the code and see how it works:
	The LED is turned on when the button is pushed, then turns off after ~1 second
	* The code in the interrupt_function is executed once when the button is pushed and the interrupt is triggered
	* The main code can do something completely different, here an example of a math calculation.
	* The main code then turns off the LED every 1.2s
	* The interrupt can be triggered at any point during the main program, therefore the time after which the LED turns off varies, depending on when the button is pushed

2. Change the code to attach the 'interrupt_toggle' function to the button interrupt. See the definition of the function at the bottom of the code
	* Do this by changing the line in setup() :
	attachInterrupt(digitalPinToInterrupt(but_pin), interrupt_function, FALLING);
	* This toggles the LED each time the button is pressed, just like a light-switch
	* Upload the code and observe the behariour....
	> > >

3. The interrupt_toggle function is not working and makes the LED blink funny?? Perfect!
* The button pin requires a "pull-up resistor". 
* This is a large resistor which connects it to 5V in order to constantly "pull up" the voltage.
* It is connected to ground when the button is pressed but else is not connected and left what we call 'floating'. The pull-up resistor connects it to 5V so it is not left "floating"
* The ATmega328 has internal pull-up resistors which can be used/ activated in the set-up using the pinMode function.
* Change it to:
	pinMode(but_pin, INPUT_PULLUP);
* Upload and observe the program now working correctly?

4. Try this program and press the button a few times quickly and slowly
* You should observe the LED switch ON when the button is pushed and the interrupt is triggered. 
* Sometimes however the interrupt will be triggered a second time when you let go of the button. This should be impossible as the interrupt is configured for the FALLING edge, not the RISING edge.
* What is happening is that the button is "bouncing" by a tiny amount which means it connects and disconnects a few times instead of smoothly once. This creates several pulses and thus extra edges which can trigger the interrupt.

5. Change the code to attach the 'interrupt_debounce' function to the interrupt.
*  This functions 'debounces' the button signal but only allowing the interrupt to be triggered once every X milliseconds. This time is set by the debounce_time variable in the setup()




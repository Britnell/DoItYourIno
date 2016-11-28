##Fabduino

# Traffic light

This sketch will control an RGB-LED 
> LED with 3 internal LEDs in red, green and blue (R G B) 
> LEDs can be combine to produce many colours

This sketch defines custom functions to change the LED color or turn it off
This helps us re-use code and type less

###Functions
* pinMode(pin, INPUT or OUTPUT );
* digitalWrite( pin, 1 or 0 / HIGH or LOW)
* [Arduino Reference](https://www.arduino.cc/en/Reference/)

1.  Try varying the delays to change the timing of the traffic light
2. 	Try writing you own functions to turn the LED Red or Blue and replace them in the main loop to fix the colours. To do this you can copy one of the existing functions.
> It will look something like:  
> void RGB_color(){ digitalWrite(..)... }
3. Try and produce some other colours by mixing 2 color LEDs
4. Try producing white by turning all LEDs on

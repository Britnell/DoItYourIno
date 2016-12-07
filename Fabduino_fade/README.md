##Fabduino

# Fade

This sketch will show you how to fade an LED using Pulse-Width-Modulation

###Functions
* Compound operator '+='
* analogWrite(pin, percentage)
* See [Arduino Reference](https://www.arduino.cc/en/Reference/) for details. 

> The analgWrite() function sets the percent of power that is supplied to a pin.
> Instead of 0 to 100% this will be 0 to 255
> At 0 it will be always Off
> At 1 it will be always On
> At 127 it will be on 50% of the time
> At 190 it will be on 75% of the time 
> At 25 it will be on 10% of the time

1.  Observe how the brightness varies non-linearly! We can not see any significant change for about 50% of the time, from 0 to 120
2. Observe how just like before, 0 means always OFF which turns the LED ON, 255 means always ON which turns the LED OFF. Therefore when the fading value goes from 0 to 255, the LED goes from bright to dark.
3. Replace the delay time to change the speed of the dimming
4. Replace the integer where the addition of +2 is carried out, to change the size of the steps of the dimming.
5. Change the delay-time to change how quickly the LED is dimmed.
6. Create variables for the minimum and maximum values of fading and replace them in the loop()
7. With these variables change the range of the fading to start at 120 and end at 255
8. Change the direction by subtracting instead of adding. Remember to also adjust the initial values and the values in the if-statement so that it works.
9. Bonus : change the code so that the fade value increases from 0 to 255 (min to max). When it reaches 255 (max)  it turns around and decreases in steps to 0 where it turns around again.
> Tip: you can achieve this with if-statements and extra variables.


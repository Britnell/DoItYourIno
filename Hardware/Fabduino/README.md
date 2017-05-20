# DoItYourIno

#Fabduino

Fabduino::Versions

Fabduino is a simplified, single layer Arduino without on-board programmer. It was made from what FabLab had in stock, trying to minimise board layout, components, and especially jumpers (as single sided)

Mainly, I designed some with ISP programming header, and some with Serial programming header.

#ISP
ISP programming works nicely as we can manufature our own programmers from FabIsp with Attinys. Drawback is we can't use this to read the serial output.

#FTDI
To be added...

#Programming
All of these were set-up with an 8 MHz Resonator. This makes them compatible in Arduino with Arduino Pro or Pro mini.

##Programming in Arduino
You need to do the following steps once to set up the board:

1. Click on the 'Tools' menu: Click on the option 'Board:' and Select "Arduino Pro or Pro Mini"
2. Again in the Tools menu: Click on the option 'Processor:' and select "ATmega328 (3.3V, 8MHz)"
3. Again in the Tools menu: Click on the option 'Programmer:' and select "USBtinyISP"

Then to program just select "Upload Using Programmer". Depending on your version of Arduino this is in the 'Sketch' or in the 'File' menu.

#FabIsp

The FabIsp is a great kit that lets you make your own USB-ISP programmer from ATtiny. Thanks to the guys at MIT

Check out their documentation here:

1. [FabIsp](http://fab.cba.mit.edu/content/projects/fabisp/) - The first design this has best documentation for programming
2. [FabIsp Key](http://fab.cba.mit.edu/content/projects/fabispkey/index.html) - A sleep improvement on the design, making it smaller and using the PCB mill to create a USB plug

If you just want to use the FabIsp, you will need the USB-driver.

### Linux
In Linux you dont need to install any drivers for the FabIsp!

### Windows Driver
For the workshops we installed the driver on many machines and for all 64-Bit Windows 7 and newer, these fixed drivers worked:

The fix is by [MightyOhm](http://mightyohm.com/blog/2010/09/fixed-usbtinyisp-drivers-for-64-bit-windows-7/), here the website. What you need is the 
[usbtinyisp_libusb-win32_1.2.1.0](http://mightyohm.com/blog/wp-content/uploads/2010/09/usbtinyisp_libusb-win32_1.2.1.0.zip)

Just download the zip file, unzip ip, plug in FabIsp and point the driver installation at the folder.

On Windows 8+ you need to do a trick to be able to install the driver, as it can't verify the driver origin:
1. Hold down the Shift key + Press restart. Keep holding down Shift until it takes you to a special menu
2. This menu looks different but what your looking for is 'Advanced Options' and then something like 'Restart options'
3. Click this and it will Restart. After restarting it will offer you a menu
4. select option 7) Disable driver signature verification .. or something like that. 


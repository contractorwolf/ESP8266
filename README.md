ESP8266
=======
This is code to run on an Arduino Micro used to communicate with the ESP8266 Wifi board using the serial debugging console.  The Arduino Micro has 2 UART connections, one using the USB for communicating with a computer and the other (in this case) is connected to the TX/RX pins on the ESP8266.  The ESP8266 is also powered using the 3.3v and GND pins on the Arduino Micro.

To use, start the sketch and open the Serial Monitor in the Arduino IDE (after setting the wifi network name and password in the code).  To test that the ESP8266 is running correctly just put "AT" into the Serial Monitor and hit Send (make sure Carriage Return is set in the Seial Monitor).  If it has the pins sent up correctly you should see an "OK". 

The Arduino code is waiting for a serial command that is either a URL (such as "www.signalvehicle.com", note the lack of "http") or an AT command (such as "AT+CIFSR" which will show the IP address if it connected to a Wifi network).  The commands will always begin with "AT...", if it doesnt see AT as the firt 2 characters it will assume that the input is a URL.  The URL can also contain a full path, such as "www.signalvehicle.com/index.asp" (again without the "http://").  If a valid URL is given, the module will output the HTML from the requested file to the debug window.

I am still working of the HTTPS (secure) request, but as of now this will only work on HTTP GET requests.  The same code should work on any Arduinos that have more than one UART, such as the MEGA boards.  My full writeup on how I have the hardware connected (with images and video) is located here:
http://contractorwolf.com/esp8266-wifi-arduino-micro/

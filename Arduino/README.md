To get the self-balancing bot up and running you'll first need to copy the contents of **libraries/** to your **Arduino/libraries/** folder on your system.

Upload **ember/ember.ino** to the Nano. If you're using a 3xAA battery pack then make sure to comment out 

**#define USE_LITHIUM_BATT**

in the code and set the VSel jumpers to 5V. Otherwise set them to 7.4V.  
<br>

Open up the arduino serial monitor and set the baud rate to 38400. With the motors and batteries disconnected, insert the usb cable and hold the pcb upright and you should see the pitch values being output to the serial monitor.

You can then comment out **Serial.println(CFilteredlAngleY)** once this test is completed.  
<br>

Now got to **changebaudrate/** and follow the instructions there.

Install the BTCommander app on your phone and follow the instructions at [http://www.klikrobotics.com/Controllers2.html](http://www.klikrobotics.com/Controllers2.html) to set it up (except use P instead of KPS, and I instead of KP on the labels). If you switch on the bot and connect to it via bluetooth then you should see some values for P, I and Trim appear in the app.  
<br>

Finally, follow the rest of the instructions in **deadbands/** first and then **ember/** to get the bot up and running!


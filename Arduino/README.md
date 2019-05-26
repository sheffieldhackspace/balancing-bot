To get the self-balancing bot up and running you'll first need to copy the contents of **libraries** to your **Arduino/libraries/** folder on your system.

#

If you're using a 3xAA battery pack then make sure to comment out 

```
#define USE_LITHIUM_BATT
```

in the code and set the VSel jumpers to 5V. Otherwise set them to 7.4V.

#

Upload **ember/ember.ino** to the Nano. Open up the arduino serial monitor and set the baud rate to 38400. With the motors and batteries disconnected, insert the usb cable and hold the pcb upright and you should see the pitch values being output to the serial monitor.

You can then comment out 

```
Serial.println(CFilteredlAngleY)
```

once this test is completed.  

#

Now go to **changebaudrate** and follow the instructions there.

Install the Joystick BT Commander app on your phone and follow the instructions at

[http://www.klikrobotics.com/Controllers2.html](http://www.klikrobotics.com/Controllers2.html)

to configure it. For the labels, use P instead of KPS, and I instead of KP. If you switch on the bot and connect to it via bluetooth then you should see some values for P, I and Trim appear in the app.  

#

The next step is to follow the rest of the instructions in the **deadbands** directory first and then in **ember** to get the robot up and running!

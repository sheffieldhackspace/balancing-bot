This is where the main code for the self-balancing bot is located. The file **ember.ino** is the one you want to upload.

If the bot rushes forwards or backwards then you can alter the **Trim** value using the joystick BT commander app to get it to stand still. You can change the value of **gtrim** in the code so that you don't always have to do this.

The balancing is controlled by a PID loop. The 'Proportional' parameter is given by the values **gyroKp** and **KP** (which should be set the same), whereas the 'Integral' value is given by **gyroKi** and **KI** (also should be the same). You can tune these values using the BT commander app and, as before, the values can be hardcoded so they don't have to be setup again.

If you want to print anything out to the serial monitor then make sure you use something like

```
#ifndef USE_HARDWARE_SERIAL
	Serial.println(CFilteredlAngleY);
#endif
```

which ensures that there's no interference with data being sent to the HC-05 when using hardware serial instead of software serial.

And if you do want to use hardware serial to communicate with the HC-05 bluetooth module, uncomment out 

```
//#define USE_HARDWARE_SERIAL
```
before uploading, and then switch the SerialSel jumpers to the HW setting. You'll need to remove the jumpers every time you want to upload code again.

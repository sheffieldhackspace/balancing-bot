First upload **changebaudrate.ino** and then remove the usb cable and make sure the power is turned off on the robot.

Hold down the little button on the HC-05 bluetooth module and plug the cable back in again. Wait a few seconds until the LED starts flashing slowly and release.

Open up the serial monitor and set the baud rate to 9600. Some instructions should appear. Type

**AT+UART=38400,0,0**

into the serial monitor and hit enter. It should respond with "OK".

The baud rate on the HC-05 should be set to the right value now!


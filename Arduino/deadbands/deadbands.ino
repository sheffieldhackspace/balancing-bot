/**************************************************************************
 *
 *    Code to determine deadband parameters for self-balancing robot
 *    v1.0
 *
 *    May 2019
 *
 *
 *
 *    (set SerialSel jumpers to "SS" before uploading this code)
 *
 *
 *
 **************************************************************************/



#include <TaskScheduler.h>
#include <Motor.h>
#include <Wire.h>
#include "Combination_Filter.h"


 
const int m1ndb = 14, m1pdb = 15, m2ndb = 18, m2pdb = 19; /*
    These are the key parameters that we're tying to optimize here
    Try values 25,25,25,25 and work downwards from there
    If using 3xAA batteries try values 30,30,30,30 and note that plugging in the usb cable will increase the voltage giving slightly inaccurate results
    The point is to find the values at which each motor barely starts to move
    Flip the self-balancing bot onto its back to reverse the motors and find deadband values for the opposite direction */



bool startFlag = false;

float g = 9.81, pi = 3.1416, h = 0.08;
float dh, th, phi, v, vxy, vx, vy, vz, norm, vxs, vys, angout;
float accX, accY, accZ;

float filter_weighting = 0.003; // may need to increase this to 0.005 or 0.006 if motors aren't damped


/////////////////////          Setup Motors             /////////////////////////

const int m2stby = 6, m2ain1 = 4, m2ain2 = 5, m2pwmpin = 3,  mpsfactor = 257;
Motor m1 = Motor(m2ain1, m2ain2, m2stby, m2pwmpin, m1ndb, m1pdb, mpsfactor);

const int m1stby = 6, m1ain1 = 8, m1ain2 = 7,  m1pwmpin = 9;
Motor m2 = Motor(m1ain1, m1ain2, m1stby, m1pwmpin, m2ndb, m2pdb, mpsfactor);

float lambdaM1n = (255 - m1ndb) / 321.0, lambdaM2n = (255 - m2ndb) / 321.0, lambdaM1p = (255 - m1pdb) / 321.0, lambdaM2p = (255 - m2pdb) / 321.0;


///////////////////   Setup Gyro with Combination Filter   /////////////////////

CFilter CFilterY; // Create the CFilter instances

double gyroX, gyroY, gyroZ;
int16_t tempRaw;
double  gyroYangle; // Angle calculate using the gyro only
double CFilteredlAngleY; // Calculated angle using a CFilter
double pitch, roll, gyroYrate, gyroangle;
uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data
double gyroxoffset, gyroyoffset;


///////////////////         Setup Scheduled Tasks         /////////////////////

void CFilterReadCallBack();             // Filtered Angle Readback
void motorControl();                 // Motor control loop

Task tCFilterRead(2, TASK_FOREVER, &CFilterReadCallBack);
Task tGyroPID(4, TASK_FOREVER, &motorControl);

Scheduler runner;

void CFilterReadCallBack() {
  gyroread();

}


///////////////////         Motor Control Loop         /////////////////////

void motorControl() {

  if (!startFlag) // motors run from 100ms until 850ms after boot for some reason (prob a Scheduler/Task issue)
  {
    if (millis() > 850)
      startFlag = true;
  }

  if (CFilteredlAngleY > 45)
  {
    digitalWrite(m1ain1, LOW);
    digitalWrite(m1ain2, HIGH);

    digitalWrite(m2ain1, LOW);
    digitalWrite(m2ain2, HIGH);

    analogWrite(m1pwmpin, m2ndb);
    analogWrite(m2pwmpin, m1ndb); 
    
  }
  else if (CFilteredlAngleY < -45)
  {
    digitalWrite(m1ain1, HIGH);
    digitalWrite(m1ain2, LOW);

    digitalWrite(m2ain1, HIGH);
    digitalWrite(m2ain2, LOW);

    analogWrite(m1pwmpin, m2pdb);
    analogWrite(m2pwmpin, m1pdb);
    
  }
  else
  {
    analogWrite(m1pwmpin, 0);
    analogWrite(m2pwmpin, 0);
    
  }
  
}

void setup () {
  Wire.begin();

  ////// Scale up PWM frequency to avoid annoying high pitch motor noise ///////

  int Eraser = 7; // this is 111 in binary and is used as an eraser  TCCRnB where n
  int Prescaler = 1;// this could be a number in [1 , 6]. In this case, 3 corresponds in binary to 011.
  TCCR1B &= ~Eraser; // this operation (AND plus NOT),  set the three bits in TCCR3B to 0
  TCCR1B |= Prescaler;//this operation (OR), replaces the last three bits in TCCR2B with our new value 011


  /////////////////////     Setup i2c commuication for Gyro       //////////////

  TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz
  i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
  i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
  i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
  i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
  while (i2cWrite(0x19, i2cData, 4, false)); // Write to all four registers at once
  while (i2cWrite(0x6B, 0x01, true)); // PLL with X axis gyroscope reference and disable sleep mode
  while (i2cRead(0x75, i2cData, 1));
  if (i2cData[0] != 0x68) { // Read "WHO_AM_I" register
    //Serial.print(F("Error reading sensor"));
    while (1);
  }
  delay(100); // Wait for sensor to stabilize


  /////////////////         Start Scheduled Tasks         /////////////////////

  runner.init();

  runner.addTask(tCFilterRead);
  runner.addTask(tGyroPID);  // Add Stability PID control

  tGyroPID.enable();
  tCFilterRead.enable();


}

void loop () {

  runner.execute();

}



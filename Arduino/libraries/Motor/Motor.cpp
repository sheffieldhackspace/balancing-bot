/*
 *   Motor.cpp - Library for the TB6612FNG Motor Driver.
 *     Created by Gareth Nisbet, September 2016.
 *       Released into the public domain.
 *       */

#include "Arduino.h"
#include "Motor.h"
Motor::Motor(int ain1, int ain2, int stby, int pwmpin, float ndb, float pdb, float mps_scalefactor){
	_ain1 = ain1;
    	_ain2 = ain2;
    	_stby = stby;
    	_pwmpin = pwmpin;
	_mps_scalefactor = mps_scalefactor;
	_ndb = ndb;
	_pdb = pdb;
	pinMode(_ain1, OUTPUT);
	pinMode(_ain2, OUTPUT);
	pinMode(_stby, OUTPUT);
	pinMode(_pwmpin, _pwmpin);
 	digitalWrite(_stby, HIGH);
}
void Motor::speed(float speed)
	{
	_speed = speed;
	if (_speed < 0)
		{
		digitalWrite(_ain1, HIGH);
		digitalWrite(_ain2, LOW);
		_intspeed = _speed*_mps_scalefactor-_ndb;
        
        	if (_intspeed < -255){
			_intspeed = -255;
		}

		analogWrite(_pwmpin, -1*(_intspeed));
		
#ifndef USE_HARDWARE_SERIAL 
    		Serial.println(_intspeed);
#endif    

	}
	else 
	{
		digitalWrite(_ain1, LOW);
		digitalWrite(_ain2, HIGH);
        	_intspeed = _speed*_mps_scalefactor+_pdb;
                
		if (_intspeed > 255)
		{
			_intspeed = 255;
		}
		analogWrite(_pwmpin, _intspeed);
		
#ifndef USE_HARDWARE_SERIAL 
    		Serial.println(_intspeed);
#endif  
        
    	}
	

}


/*
 *   Motor.h - Library for the TB6612FNG Motor Driver.
 *     Created by Gareth Nisbet, September 2016.
 *       Released into the public domain.
 *       */
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
		 public:
			Motor(int ain1, int ain2, int stby, int pwmpin, float ndb, float pdb, float mps_scalefactor);
		 	void speed(float speed);
		 private:
			int _ain1, _ain2, _stby, _pwmpin;
			float _speed, _ndb, _pdb, _mps_scalefactor;
			int _intspeed;
};

#endif

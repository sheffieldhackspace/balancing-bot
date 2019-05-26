#include <Motor.h>
// Setup Motors
const int m1stby = 6, m1ain1 = 8, m1ain2 = 7, m1pwmpin = 10, m1ndb = 0 , m1pdd = 0, mpsfactor = 1275;
Motor m1 = Motor(m1ain1, m1ain2, m1stby, m1pwmpin, m1ldb, m1ud, mpsfactor);

const int m2stby = 6, m2ain1 = 4, m2ain2 = 5, m2ndb = 0 , m2pdd = 0, m2pwmpin = 9;
Motor m2 = Motor(m2ain1, m2ain2, m2stby, m2pwmpin, m2ndb, m2pdb, mpsfactor);


void setup() {
  int Eraser = 7; // this is 111 in binary and is used as an eraser  TCCRnB where n 
  int Prescaler = 1;// this could be a number in [1 , 6]. In this case, 3 corresponds in binary to 011.   
  TCCR1B &= ~Eraser; // this operation (AND plus NOT),  set the three bits in TCCR3B to 0
  TCCR1B |= Prescaler;//this operation (OR), replaces the last three bits in TCCR2B with our new value 011
Serial.begin(115200);

}

void loop() {
//  m1.speed(0.3);
//  m2.speed(-0.3);
//  delay(2000);
  
  m1.speed(-0.2);
  m2.speed(0.2);
 // delay(2000);
  // put your main code here, to run repeatedly:

}

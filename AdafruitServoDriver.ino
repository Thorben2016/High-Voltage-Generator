//Extension Board

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

byte pins[] = {0, 1, 2, 3, 4, 5, 6, 7};

//----------------------------------------------------------
//setup
//Extension board
  pwm.begin();
  pwm.setPWMFreq(1600);

//-----------------------------------------------------------
//loop
//output manipulation over Adafruit extension board

int   nb = voltageoutR;
    int   i = 7;

    while (i >= 0) {
      if ((nb >> i) & 1) {
        state = HIGH;
        pwm.setPin(i, 0, state);

      } else {
        state = LOW;
        pwm.setPin(i, 0, state);
      }
      --i;
    }

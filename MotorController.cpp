#include "interfaces.h"
#include "Arduino.h"
class MotorController : public IMotorController {

  public:
    MotorController(int pin1Input, int pin2Input, int enablePinInput){
      pin1 = pin1Input;
      pin2 = pin2Input;
      enablePin = enablePinInput;
      speed = 0;

      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      analogWrite(enablePin, speed);
    }

    int getSpeed() {
      return speed;
    }

    int setSpeed(int speedInput){
      int oldSpeed = speed;
      speed = speedInput;
      return oldSpeed;
    }

    private:
      int pin1;
      int pin2;
      int enablePin;
      int speed;
};
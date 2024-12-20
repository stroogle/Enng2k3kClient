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

      if(speedInput < 0) {
        speed = speedInput * -1;
      }

      if(speed == 0) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        analogWrite(enablePin, speed);
      } else if (speedInput < 0) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        analogWrite(enablePin, speed);
      } else {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        analogWrite(enablePin, speed);
      }

      return oldSpeed;
    }

    private:
      int pin1;
      int pin2;
      int enablePin;
      int speed;
};
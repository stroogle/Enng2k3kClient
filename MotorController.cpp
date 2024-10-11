#include "interfaces.h"

class MotorController : public IMotorController {
    MotorController(){}

    int getSpeed() {
      return -1;
    }

    int setSpeed(int speed){
      return -1;
    }
};
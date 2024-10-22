#include "interfaces.h"
#include "Arduino.h"
#include "Servo.h"

class DoorController : public IDoor {
  public:
    DoorController(int pin){
      servo.attach(pin);
    }

    void open() {
      servo.write(90);
    }

    void close() {
      servo.write(0);
    }

    private:
      Servo servo;
};
#include "Arduino.h"

class PhotoReceptor {

  public:
    PhotoReceptor(int pin){
      receptor_pin = pin;
      pinMode(receptor_pin, INPUT_PULLUP);
    };

    bool triggered() {
      digitalRead(receptor_pin) == LOW;
    }

  private:
    int receptor_pin;

};
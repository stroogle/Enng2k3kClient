#include "Arduino.h"
#include "interfaces.h"

class PhotoReceptor : public IPhotoReceptor {

  public:
    PhotoReceptor(int pin){
      receptor_pin = pin;
      pinMode(receptor_pin, INPUT_PULLUP);
    };

    bool tripped() {
      return digitalRead(receptor_pin) == LOW;
    }

  private:
    int receptor_pin;

};
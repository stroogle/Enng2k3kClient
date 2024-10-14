#include "Arduino.h"
#include "interfaces.h"

class LEDController : public ILED {
  public:
    LEDController(int pin1, int pin2, int pin3){
      redPin = pin1;
      greenPin = pin2;
      bluePin = pin3;
      pinMode(redPin,  OUTPUT);              
      pinMode(greenPin, OUTPUT);
      pinMode(bluePin, OUTPUT);
    }

    void displayStatus(Statuses status) {
      switch (status) {
        case Statuses::CONNECTING:
          break;
        case Statuses::DISCONNECTED:
          break;
        default:
          break;
      }
    }

    void setsColour(int red, int green, int blue) {
      analogWrite(redPin, red);
      analogWrite(greenPin,  green);
      analogWrite(bluePin, blue);

    }

  private:
    int redPin;
    int greenPin;
    int bluePin;

};
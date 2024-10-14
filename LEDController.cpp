#include "Arduino.h"
#include "interfaces.h"

class LEDController : public ILED {
  public:
    LEDController(int ledPin){
      pin = ledPin;
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

  private:
    int pin;

};
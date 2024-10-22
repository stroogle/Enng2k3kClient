#include "Arduino.h"
#include "interfaces.h"

class LEDController : public ILED {
  public:
    LEDController(int ledPin1, int ledPin2, int ledPin3){
      pin1 = ledPin1;
      pin2 = ledPin2;
      pin3 = ledPin3;
    }

    void useLED(int num){
      if(num==1){ // Connected
        digitalWrite(pin1, HIGH);  // FLASH GREEN
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);

      } else if(num==2) {  // Slow

        digitalWrite(pin1, HIGH);  //YELLOW
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);

      } else if(num==3) {  // Go

        digitalWrite(pin1, LOW);  //GREEN
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        
      } else if(num==4) {  // Reverse

        digitalWrite(pin1, HIGH);  //FLASH YELLOW
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);

      } else if(num==5) {  // Stopped

        digitalWrite(pin1, HIGH);  //RED
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        
      } else if(num==6) {  // Disconnected

        digitalWrite(pin1, HIGH);  //FLASH RED
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);

      }

    }

  private:
    int pin;

};
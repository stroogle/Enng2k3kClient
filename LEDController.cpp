#include "Arduino.h"
#include "interfaces.h"

class LEDController : public ILED {
  public:
    LEDController(int ledPin1, int ledPin2, int ledPin3){
      pin1 = ledPin1;
      pin2 = ledPin2;
      pin3 = ledPin3;
      prev_flash = millis();
      flash_interval = 0;
      mode = 1;
      off = false;
    }

    void useLED(int num){
      mode = num;
    }

    void setFlashRate(int n) {
      flash_interval = n;
    }

    void run() {
      if(flash_interval > 0) {
        runFlash();
      } else {
        runMode();
      }
    }

    

  private:
    int pin1;
    int pin2;
    int pin3;
    int flash_interval = 0;
    long prev_flash;
    int mode;
    bool off;

    void runFlash(){
      if(millis() - flash_interval >= prev_flash) {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
      } else {
        runMode();
        prev_flash = millis();
      }
    }

    void runMode(){
      if(mode==1){ // Connected
        digitalWrite(pin1, HIGH);  // FLASH GREEN
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);

      } else if(mode==2) {  // Slow

        digitalWrite(pin1, HIGH);  //YELLOW
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);

      } else if(mode==3) {  // Go

        digitalWrite(pin1, LOW);  //GREEN
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        
      } else if(mode==4) {  // Reverse

        digitalWrite(pin1, HIGH);  //FLASH YELLOW
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);

      } else if(mode==5) {  // Stopped

        digitalWrite(pin1, HIGH);  //RED
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);

      } else if(mode==6) {  // Disconnected

        digitalWrite(pin1, HIGH);  //FLASH RED
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
      }
    }
};
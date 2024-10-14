#include "Arduino.h"
#include "interfaces.h"

class Carriage : public ICarriage {
  
    private:
        char* status;
        int slowSpeed = 90;
        int fastSpeed = 180;
        IMotorController* motor;
        IDoor* door;
        ILED* led;
        IDistanceSensor* frontSensor;
        IDistanceSensor* backSensor;

    public:
        Carriage(
          IMotorController* motorInput,
          IDoor* doorInput,
          ILED* ledInput,
          IDistanceSensor* frontSensorInput,
          IDistanceSensor* backSensorInput
        ){
          motor = motorInput;
          door = doorInput;
          led = ledInput;
          frontSensor = frontSensorInput;
          backSensor = backSensorInput;
        }
        
        int setSpeed(int speed) {
            return -1;
        }

        int getSpeed() {
            return -1;
        }
        
        char* getStatus() {
            return status;
        }

        void setStatus(char* newStatus) {
            status = newStatus;
        };

        void wait() {}
        
        void stop() {
          motor->setSpeed(0);
        }
    
        void go() {
          motor->setSpeed(fastSpeed);
        }
        
        void run() {}

        void closeDoor() {
          door->close();
        }

        void openDoor() {
          door->open();
        }

        void slow() {
          motor->setSpeed(slowSpeed);
        }

        void displayStatus(){}

        bool shouldStop() {
          return (frontSensor->isTooClose() || backSensor->isTooClose());
        }
};
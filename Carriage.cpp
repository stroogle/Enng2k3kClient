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
        ISocketClient* socket;

    public:
        Carriage(
          IMotorController* motorInput,
          IDoor* doorInput,
          ILED* ledInput,
          IDistanceSensor* frontSensorInput,
          IDistanceSensor* backSensorInput,
          ISocketClient* socketInput
        ){
          motor = motorInput;
          door = doorInput;
          led = ledInput;
          frontSensor = frontSensorInput;
          backSensor = backSensorInput;
          socket = socketInput;
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

        void setStatus(Actions stat) {
            switch(stat) {
              case Actions::STOPC:
                status = "STOPC";
                break;
              case Actions::STOPO:
                status = "STOPO";
                break;
              case Actions::FSLOWC:
                status = "STOPC";
                break;
              case Actions::FFASTC:
                status = "STOPC";
                break;
              case Actions::RSLOWC:
                status = "STOPC";
                break;
              case Actions::DISCONNECT:
                status = "STOPC";
                break;
              default:
                status = "STOPC";
            }
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

        void reverse() {
          motor->setSpeed(0-slowSpeed);
        }



        void stopc() {

        }

        void stopo() {

        }

        void fslowc() {

        }

        void ffastc() {

        }

        void rslowc() {

        }

        void strq() {

        }

        void disconnect() {

        }
};
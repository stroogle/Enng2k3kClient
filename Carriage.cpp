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
        IPhotoReceptor* photoReceptor;

    public:
        Carriage(
          IMotorController* motorInput,
          IDoor* doorInput,
          ILED* ledInput,
          IDistanceSensor* frontSensorInput,
          IDistanceSensor* backSensorInput,
          ISocketClient* socketInput,
          IPhotoReceptor* photoInput
        ){
          motor = motorInput;
          door = doorInput;
          led = ledInput;
          frontSensor = frontSensorInput;
          backSensor = backSensorInput;
          socket = socketInput;
          photoReceptor = photoInput;
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
          stop();
          closeDoor();
          led->setFlashRate(0);
          led->useLED(5);
          socket->sendStatus("STOPC");
        }

        void stopo() {
          stop();
          openDoor();
          led->setFlashRate(0);
          led->useLED(5);
          socket->sendStatus("STOPO");
        }

        void fslowc() {
          slow();
          led->setFlashRate(0);
          led->useLED(2);
          while(!photoReceptor->tripped()){
            // led->run();
          }
          stop();
          socket->sendStatus("STOPC");
        }

        void ffastc() {
          closeDoor();
          led->setFlashRate(0);
          led->useLED(3);
          go();
          socket->sendStatus("FFASTC");
        }

        void rslowc() {
          reverse();
          led->setFlashRate(500);
          led->useLED(4);
          while(!photoReceptor->tripped()){
            // led->run();
          }
          stop();
          socket->sendStatus("STOPC");
        }

        void strq() {
          socket->sendStatus(getStatus());
        }

        void disconnect() {
          socket->sendStatus("OFLN");
          led->setFlashRate(500);
          led->useLED(6);
        }
};
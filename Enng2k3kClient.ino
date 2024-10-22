#include <Arduino.h>
#include "WiFi.h"
#include "interfaces.h"
#include "./CommsChannel.cpp"
#include "./MotorController.cpp"
#include "./SocketClient.cpp"
#include "./PhotoReceptor.cpp"
#include "./Carriage.cpp"
#include "./UltraSonicSensor.cpp"
#include "./DoorController.cpp"
#include "./LEDController.cpp"

/* CONFIGURATION */

char* WIFI_NAME = "ENGG2K3K";
char* WIFI_PASSWORD = "";
char* SOCKET_SERVER_ADDRESS = "";
int SOCKET_SERVER_PORT = 1234;

int MOTOR_PIN = 19;
int LED_PIN = 17;
int PHOTO_RECEPTOR_PIN = 14; // TELL MOTIONS TO CHANGE THIS PIN

int FRONT_SENSOR_PIN_1 = 26;
int FRONT_SENSOR_PIN_2 = 27;

int BACK_SENSOR_PIN_1 = 32;
int BACK_SENSOR_PIN_2 = 33;

bool ARE_THE_MOTOR_PINS_BACKWARD = false;

/* END CONFIGURATION */


/* MVP */

IMotorController* motor;
IDoor* door;
ILED* led;
IDistanceSensor* frontSensor;
IDistanceSensor* backSensor;

// Motor A
int motor1Pin1 = 27; // High / Low
int motor1Pin2 = 26; // Low / High <-- direction
// int motor1Pin3 = //PWM 0-255
int enable1Pin = 14; 

// Setting PWM properties
int freq = 30000;
int pwmChannel = 0;
int resolution = 8;
int dutyCycle = 200;
IWifiComm* comms;
ISocketClient* socket;

// Photoreceptor
IPhotoReceptor* photoReceptor;

// Carriage
ICarriage* bladeRunner;

void setup() {

    pinMode(LED_PIN, OUTPUT);

    comms = new CommsChannel(WIFI_NAME, WIFI_PASSWORD);
    comms->connect();

    socket = new SocketClient(SOCKET_SERVER_ADDRESS, SOCKET_SERVER_PORT);

    if (ARE_THE_MOTOR_PINS_BACKWARD) {
      int temp = motor1Pin1;
      motor1Pin1 = motor1Pin2;
      motor1Pin2 = temp;
    }

    motor = new MotorController(motor1Pin1, motor1Pin2, enable1Pin);

    door = new DoorController();

    photoReceptor = new PhotoReceptor(PHOTO_RECEPTOR_PIN);

    frontSensor = new UltraSonicSensor(FRONT_SENSOR_PIN_1, FRONT_SENSOR_PIN_2);
    backSensor = new UltraSonicSensor(BACK_SENSOR_PIN_1, BACK_SENSOR_PIN_2);

    led = new LEDController(17, 18, 19);

    bladeRunner = new Carriage(motor, door, led, frontSensor, backSensor, socket, photoReceptor);
}

void loop() {

    /*
    * If Wifi is not connect, try reconnect again and then restart loop.
    */
    if(WiFi.status() != WL_CONNECTED) {
      led->setFlashRate(500);
      led->useLED(1);
      led->run();
      comms->connect();
      return;
    }

    /*
    * If socker connection is unavailable, the loop should try connect and restart.
    */
    if(!socket->available()) {
      socket->connect(SOCKET_SERVER_ADDRESS, SOCKET_SERVER_PORT);
      return;
    }

    /*
    * Capture the next instruction
    */
    Actions nextAction = socket->getAction();

    /*
    * Overwrite instruction if direct situation says to stop
    */
    if(bladeRunner->shouldStop()) {
      nextAction = Actions::STOP;
    }

    /*
    * Execute the next instruction
    */
    switch(nextAction) {
      case Actions::NONE:
        break;
      case Actions::STOPC:
        // bladeRunner->stop();
        // bladeRunner->closeDoor();
        // socket->sendStatus("STOPC");
        bladeRunner->stopc();
        break;
      case Actions::STOPO:
        // bladeRunner->stop();
        // bladeRunner->openDoor();
        // socket->sendStatus("STOPO");
        bladeRunner->stopo();
        break;
      case Actions::FSLOWC:
        // bladeRunner->closeDoor();
        // bladeRunner->slow();
        // socket->sendStatus("STOPC");
        bladeRunner->fslowc();
        break;
      case Actions::FFASTC:
        // bladeRunner->closeDoor();
        // bladeRunner->go();
        // socket->sendStatus("FFASTC");
        bladeRunner->ffastc();
        break;
      case Actions::RSLOWC:
        // bladeRunner->closeDoor();
        // bladeRunner->reverse();
        // socket->sendStatus("STOPC");
        bladeRunner->rslowc();
        break;
      case Actions::DISCONNECT:
        // socket->sendStatus("OFLN");
        bladeRunner->disconnect();
        break;
      case Actions::STRQ:
        // socket->sendStatus(bladeRunner->getStatus());
        bladeRunner->strq();
        break;
      case Actions::STOP:
        bladeRunner->stop();
        // socket->sendStatus("STOPC");
        break;
      default:
        break;
    }

    // /*
    // * When it is time for a status update, send one.
    // */
    // if(socket->readyForHeartBeat()) {
    //   socket->sendStatus(bladeRunner->getStatus());
    // }

    /*
    * Using the RBG light, display the current status.
    */
    led->run();
}

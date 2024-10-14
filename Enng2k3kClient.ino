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

/* CONFIGURATION */

const char* WIFI_NAME = "ENGG2K3K";
const char* WIFI_PASSWORD = "";
const char* SOCKET_SERVER_ADDRESS = "";
const int SOCKET_SERVER_PORT = 1234;

const int MOTOR_PIN = 19;
const int LED_PIN = 17;
const int PHOTO_RECEPTOR_PIN = 9;

const int FRONT_SENSOR_PIN_1 = 26;
const int FRONT_SENSOR_PIN_2 = 27;

const int BACK_SENSOR_PIN_1 = 32;
const int BACK_SENSOR_PIN_2 = 33;

const bool ARE_THE_MOTOR_PINS_BACKWARD = false;

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
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
IWifiComm* comms;
ISocketClient* socket;

// Photoreceptor
PhotoReceptor* photoReceptor;

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

    bladeRunner = new Carriage(motor, door, led, frontSensor, backSensor);
}

void loop() {

    /*
    * If Wifi is not connect, try reconnect again and then restart loop.
    */
    if(WiFi.status() != WL_CONNECTED) {
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
      case Actions::DOOR_CLOSE:
        bladeRunner->closeDoor();
        break;
      case Actions::DOOR_OPEN:
        bladeRunner->openDoor();
        break;
      case Actions::GO:
        bladeRunner->go();
        break;
      case Actions::SLOW:
        bladeRunner->slow();
        break;
      case Actions::STOP:
        bladeRunner->stop();
      default:
        break;
    }

    /*
    * When it is time for a status update, send one.
    */
    if(socket->readyForHeartBeat()) {
      socket->sendStatus(bladeRunner->getStatus());
    }

    /*
    * Using the RBG light, display the current status.
    */
    bladeRunner->displayStatus();
}

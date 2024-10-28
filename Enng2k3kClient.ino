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
char* SOCKET_SERVER_ADDRESS = "10.20.30.174";
int SOCKET_SERVER_PORT = 2006;

int MOTOR_PIN = 19; // DOOR

int LEDPIN1 = 21;
int LEDPIN2 = 22;
int LEDPIN3 = 23;

// Motor A
int motor1Pin1 = 13; // High / Low.   // ISSUE - CHANGE
int motor1Pin2 = 18; // Low / High <-- direction
// int motor1Pin3 = //PWM 0-255
int enable1Pin = 4;          // ISSUE - CHANGE

int FRONT_SENSOR_PIN_1 = 26;
int FRONT_SENSOR_PIN_2 = 27;

int BACK_SENSOR_PIN_1 = 32;
int BACK_SENSOR_PIN_2 = 33;

int PHOTO_RECEPTOR_PIN = 34; 

bool ARE_THE_MOTOR_PINS_BACKWARD = false;

/* END CONFIGURATION */


/* MVP */

IMotorController* motor;
IDoor* door;
ILED* led;
IDistanceSensor* frontSensor;
IDistanceSensor* backSensor;



// Setting PWM properties
int freq = 30000;
int pwmChannel = 0;
int resolution = 8;
int dutyCycle = 200;
IWifiComm* comms;
ISocketClient* socket;
WiFiClient client;

// Photoreceptor
IPhotoReceptor* photoReceptor;

// Carriage
ICarriage* bladeRunner;

void setup() {
    Serial.begin(115200);
    Serial.println("Beginning setup...");
    // pinMode(LED_PIN, OUTPUT)
    // Serial.println("Sets LED Pin");

    comms = new CommsChannel(WIFI_NAME, WIFI_PASSWORD);
    comms->connect();
    Serial.println("Connecting to the WiFi complete...");

    socket = new SocketClient(SOCKET_SERVER_ADDRESS, SOCKET_SERVER_PORT, client);
    Serial.println("Socket client created...");

    if (ARE_THE_MOTOR_PINS_BACKWARD) {
      int temp = motor1Pin1;
      motor1Pin1 = motor1Pin2;
      motor1Pin2 = temp;
      Serial.println("Motors pins swapped...");

    }

    motor = new MotorController(motor1Pin1, motor1Pin2, enable1Pin);
    Serial.println("motor initiated...");

    door = new DoorController(MOTOR_PIN);
    Serial.println("Door initiated...");

    photoReceptor = new PhotoReceptor(PHOTO_RECEPTOR_PIN);
    Serial.println("PhotoReceptor initiated...");

    frontSensor = new UltraSonicSensor(FRONT_SENSOR_PIN_1, FRONT_SENSOR_PIN_2);
    Serial.println("Front sensor setup...");
    backSensor = new UltraSonicSensor(BACK_SENSOR_PIN_1, BACK_SENSOR_PIN_2);
    Serial.println("Back sensor setup...");

    led = new LEDController(LEDPIN1, LEDPIN2, LEDPIN3);
    Serial.println("LED setup...");

    bladeRunner = new Carriage(motor, door, led, frontSensor, backSensor, socket, photoReceptor);
    Serial.println("Carriage setup...");

    // Setup new thread;
    xTaskCreatePinnedToCore (
      led_loop,     // Function to implement the task
      "led_loop",   // Name of the task
      400,      // Stack size in bytes
      NULL,      // Task input parameter
      0,         // Priority of the task
      NULL,      // Task handle.
      0          // Core where the task should run
    );
    Serial.println("LED thread bagins...");

}

void loop() {

    /*
    * If Wifi is not connect, try reconnect again and then restart loop.
    */
    if(WiFi.status() != WL_CONNECTED) {
      led->setFlashRate(500);
      led->useLED(1);
      // led->run();
      comms->connect();
      Serial.println("NOT CONENCTED");
      return;
    }

    /*
    * If socker connection is unavailable, the loop should try connect and restart.
    */
    if(!socket->available()) {
      socket->connect(SOCKET_SERVER_ADDRESS, SOCKET_SERVER_PORT);
      Serial.println("NOT SOCKETED");
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
    // led->run();
}

void led_loop(void *pvParameters) {
  while(1) {
    led->run();
  }
}
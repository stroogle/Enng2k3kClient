#include <Arduino.h>
#include "interfaces.h"
#include "./CommsChannel.cpp"
#include "./JobQueue.cpp"
#include "./MotorController.cpp"
/* ESP32 WiFi Scanning example */
#include "WiFi.h"

/* CONFIGURATION */

const char* WIFI_NAME = "ENGG2K3K";
const char* WIFI_PASSWORD = "";
const char* SOCKET_SERVER_ADDRESS = "";
const int SOCKET_SERVER_PORT = 1234;

const int MOTOR_PIN = 19;
const int LED_PIN = 17;

/* END CONFIGURATION */


/* MVP */

IMotorController* motor;
ILED* led;

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
CommsChannel* comms;
IJobQueue* jobs_for_client;
IJobQueue* jobs_for_server;



void setup() {
    // pinMode(MOTOR_PIN, OUTPUT);
    // motor = new MotorControl(MOTOR_PIN);
    // motor->setSpeed(40);
    // delay(3000);
    // motor->setSpeed(0);

    pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

    pinMode(LED_PIN, OUTPUT);

    jobs_for_client = new JobQueue();
    jobs_for_server = new JobQueue();

    comms = new CommsChannel(
    WIFI_NAME,
    WIFI_PASSWORD,
    SOCKET_SERVER_ADDRESS,
    SOCKET_SERVER_PORT,
    jobs_for_server,
    jobs_for_client
    );

    comms->connect();

}

void loop() {

    if(WiFi.status() == WL_CONNECTED) {
      digitalWrite(LED_PIN, HIGH);

      delay(1000);

      digitalWrite(LED_PIN, LOW);

      delay(1000);
    }

    // motor->setSpeed(90);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);

    delay(3000);

    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    analogWrite(enable1Pin, 200);

    delay(3000);

    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);

}

/* END MVP*/

// TaskHandle_t OtherThread;
// 
// CommsChannel* comms;
// IJobQueue* jobs_for_client;
// IJobQueue* jobs_for_server;
// IMotorController* motor;
// 
// void communication_task( void * parameter) {
// 
//   comms->connect();
// 
//   for(;;) {
    // Serial.println("Other Thread!");
    // delay(100);
//   }
// }
// 
// void setup() {
//   Serial.begin(115200);
//   Serial.println("Initializing WiFi...");
//   WiFi.mode(WIFI_STA);
//   Serial.println("Setup done!");
// 
    // jobs_for_client = new JobQueue();
    // jobs_for_server = new JobQueue();
    // motor = new MotorControl(MOTOR_PIN);
// 
//   comms = new CommsChannel(
    // WIFI_NAME,
    // WIFI_PASSWORD,
    // SOCKET_SERVER_ADDRESS,
    // SOCKET_SERVER_PORT,
    // jobs_for_server,
    // jobs_for_client
//   );
// 
// 
//   xTaskCreatePinnedToCore(
    //   communication_task, /* Function to implement the task */
    //   "Task1", /* Name of the task */
    //   10000,  /* Stack size in words */
    //   NULL,  /* Task input parameter */
    //   0,  /* Priority of the task */
    //   &OtherThread,  /* Task handle. */
    //   0); /* Core where the task should run */
// }
// 
// void loop() {
//   Serial.println("Scanning...");
// 
//   WiFi.scanNetworks will return the number of networks found
//   int n = WiFi.scanNetworks();
//   Serial.println("Scan done!");
//   if (n == 0) {
    // Serial.println("No networks found.");
//   } else {
    // Serial.println();
    // Serial.print(n);
    // Serial.println(" networks found");
    // for (int i = 0; i < n; ++i) {
    //   Print SSID and RSSI for each network found
    //   Serial.print(i + 1);
    //   Serial.print(": ");
    //   Serial.print(WiFi.SSID(i));
    //   Serial.print(" (");
    //   Serial.print(WiFi.RSSI(i));
    //   Serial.print(")");
    //   Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
    //   delay(10);
    // }
//   }
//   Serial.println("");
// 
//   Wait a bit before scanning again
//   delay(5000);
// }
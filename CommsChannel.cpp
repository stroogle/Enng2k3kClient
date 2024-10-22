#include "WiFi.h"
#include "ArduinoJson.h"
#include "interfaces.h"

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional

class CommsChannel : public IWifiComm {
public:
    // Constructor
    CommsChannel(
        char* ssid,
        char* password
        )
        : ssid(ssid),
        password(password),
        lastResponseTime(0) {}

    // Methods
    void connect() {
        initConnection();
        if (client.connect(server, port)) {  // need Replace with actual server IP and port
            Serial.println("Connected to CCP");
        } else {
            Serial.println("Connection to CCP failed");
        }
    }

    void reconnect() {
        if (hasLostConnection()) {
            disconnect();
            connect();
        }
    }

    bool hasLostConnection() {
        if (client.connected()) {
            unsigned long currentMillis = millis();
            if (currentMillis - lastResponseTime > timeout) {
                return true;
            }
        }
        return false;
    }

    void disconnect() {
        client.stop();
        Serial.println("Disconnected from CCP");
    }

    // void sendMsg(char* message) {
    //     if (client.connected()) {
    //         client.println(message);
    //     }
    // }

    // void receiveMsg() {
    //     if (client.available()) {
    //         byte buffer[10];
    //         client.readBytes(buffer, sizeof(buffer));
    //         jobs_for_client->addJob((char*)buffer);
    //         free(buffer);
    //     }
    // }

private:
    char* ssid;
    char* password;
    WiFiClient client;
    unsigned long lastResponseTime;
    unsigned long timeout = 500; // 500 milliseconds
    char* server;
    int port;

    void initConnection() {
        WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");
    }
};
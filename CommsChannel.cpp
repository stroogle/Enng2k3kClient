#include <WiFi.h>
#include <ArduinoJson.h>
#include "interfaces.h"

class CommsChannel {
public:
    // Constructor
    CommsChannel(
        const char* ssid,
        const char* password,
        const char* server,
        const int port,
        IJobQueue* jobs_for_server,
        IJobQueue* jobs_for_client
        )
        : ssid(ssid),
        password(password),
        lastResponseTime(0),
        server(server),
        port(port),
        jobs_for_server(jobs_for_server),
        jobs_for_client(jobs_for_client) {}

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

    void sendMsg(char* message) {
        if (client.connected()) {
            client.println(message);
        }
    }

    void receiveMsg() {
        if (client.available()) {
            byte buffer[10];
            client.readBytes(buffer, sizeof(buffer));
            jobs_for_client->addJob((char*)buffer);
            free(buffer);
        }
    }

private:
    const char* ssid;
    const char* password;
    WiFiClient client;
    unsigned long lastResponseTime;
    const unsigned long timeout = 500; // 500 milliseconds
    const char* server;
    const int port;
    IJobQueue* jobs_for_server;
    IJobQueue* jobs_for_client;

    void initConnection() {
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");
    }
};
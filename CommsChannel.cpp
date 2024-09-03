#include <WiFi.h>
#include <ArduinoJson.h>

class CommsChannel {
public:
    // Constructor
    CommsChannel(const char* ssid, const char* password)
        : ssid(ssid), password(password), lastResponseTime(0) {}

    // Methods
    void connect() {
        initConnection();
        if (client.connect("SERVER_IP", SERVER_PORT)) {  // need Replace with actual server IP and port
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

    void sendMsg(const JsonDocument& json) {
        if (client.connected()) {
            serializeJson(json, client);
            client.println();  // Ensure proper transmission
        }
    }

    void receiveMsg(JsonDocument& json) {
        if (client.available()) {
            String message = client.readStringUntil('\n');
            deserializeJson(json, message);
            lastResponseTime = millis();
        }
    }

private:
    const char* ssid;
    const char* password;
    WiFiClient client;
    unsigned long lastResponseTime;
    const unsigned long timeout = 500; // 500 milliseconds

    void initConnection() {
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");
    }
};
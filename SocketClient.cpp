#include <WiFi.h>
#include "interfaces.h"
#include <Arduino.h>
class SocketClient : public ISocketClient {

  public:
    SocketClient(char* host, int port, WiFiClient c){
      client = c;
      connect(host, port);
      lastBeat = millis();
    }

    void connect(char* host, int port) {
      Serial.println("1");
      client.connect(host, port);
      Serial.println("2");
      delay(100);
      sendStatus("HELO");
    }
  
    int getMessage() {
      return client.read();
    }

    void sendStatus(char* stat){
      client.println(stat);
      lastBeat = millis();
    }

    Actions getAction() {
      int message = getMessage();
      switch(message) {
        case 1:
          return STOPC;
          break;
        case 2:
          return STOPO;
          break;
        case 3:
          return FSLOWC;
          break;
        case 4:
          return FFASTC;
        case 5:
          return RSLOWC;
        case 6:
          return DISCONNECT;
        case 7:
          return STRQ;
        default:
          return NONE;
          break;
      }
    }

    bool available() {
      return client.available();
    }

    bool readyForHeartBeat() {
      return (millis() - lastBeat) >= 2000;
    };

  private:
    WiFiClient client;
    int lastBeat;
  
};
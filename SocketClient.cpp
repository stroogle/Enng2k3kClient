#include <WiFi.h>
#include "interfaces.h"
class SocketClient : public ISocketClient {

  public:
    SocketClient(char* host, int port){
      connect(host, port);
    }

    void connect(char* host, int port) {
      client.connect(host, port);
    }
  
    int getMessage() {
      return client.read();
    }

    void sendStatus(char* stat){
      client.println(stat);
    };

    Actions getAction() {
      int message = getMessage();
      switch(message) {
        case 1:
          return GO;
          break;
        case 2:
          return STOP;
          break;
        case 3:
          return DOOR_OPEN;
          break;
        case 4:
          return DOOR_CLOSE;
        case 5:
          return SLOW;
        default:
          return NONE;
          break;
      }
    }

    bool available() {
      return client.available();
    }

    bool readyForHeartBeat() {
      return false;
    };

  private:
    WiFiClient client;
  
};
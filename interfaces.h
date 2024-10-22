#ifndef interfaces
#define interfaces

enum Actions {
  NONE,
  STOPC,
  STOPO,
  FSLOWC,
  FFASTC,
  RSLOWC,
  DISCONNECT,
  STRQ,
  STOP
};

class ICarriage {
  public:
    virtual ~ICarriage(){}

    /**
      @return Statuses, the current status of the carriage.
    */
    virtual char* getStatus() = 0;

    /**
      @param newStatus - The new status of the carriage.
    */
    virtual void setStatus(Actions stat) = 0;

    /**
      Stops the carriage from going no matter what.
    */
    virtual void stop() = 0;

    /**
      Releases the carriage from its stop hold.
    */
    virtual void go() = 0;

    /**
     The main run function for the carriage.
    */
    virtual void run() = 0;

    virtual void closeDoor() = 0;

    virtual void openDoor() = 0;

    virtual void slow() = 0;

    virtual void displayStatus() = 0;

    virtual bool shouldStop() = 0;

    virtual void reverse() = 0;

    virtual void stopc() = 0;

    virtual void stopo() = 0;

    virtual void fslowc() = 0;

    virtual void ffastc() = 0;

    virtual void rslowc() = 0;

    virtual void strq() = 0;

    virtual void disconnect() = 0;
};

enum Statuses {
  CONNECTING,
  DISCONNECTED
};

class ILED {
  public:
    virtual ~ILED(){}

    virtual void useLED(int num) = 0;

    virtual void setFlashRate(int n) = 0;

    virtual void run() = 0;
};

class IDoor {
  public:
    virtual ~IDoor(){}

    /**
     Opens the door completely.
    */
    virtual void open() = 0;

    /**
     Closes the door completely.
    */
    virtual void close() = 0;

};

class IMotorController {
  public:
    virtual ~IMotorController(){}

    /**
      @return int, the speed the motor is going.
    */
    virtual int getSpeed() = 0;

    /**
      @param speed - the new speed for the motor to go.
      @return int, the speed the motor was going previously.
    */
    virtual int setSpeed(int speed) = 0;
};

class ISocketClient {
  public:
    virtual ~ISocketClient(){}

    virtual void connect(char* host, int port) = 0;
  
    virtual int getMessage() = 0;

    virtual void sendStatus(char* stat) = 0;

    virtual Actions getAction() = 0;

    virtual bool available() = 0;

    virtual bool readyForHeartBeat() = 0;
};

class IDistanceSensor {

  public:
    virtual ~IDistanceSensor(){}

    virtual bool isTooClose() = 0;

};

class IWifiComm {
  public:
    virtual ~IWifiComm(){}

    virtual void connect() = 0;
};

class IPhotoReceptor {
  public:
    virtual ~IPhotoReceptor(){}

    virtual bool tripped() = 0;
};

#endif

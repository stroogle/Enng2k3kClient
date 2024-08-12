#ifndef interfaces
#define interfaces

class ICommsChannel {
  public:
    virtual ~ICommsChannel(){}

    /**
     Connect to the socket server.
    */
    virtual void connect() = 0;

    /**
     Connect to the socket server again
    */
    virtual void reconnect() = 0;

    /**
     @return bool, true if the CommsChannel has lost connection, false otherwise.
    */
    virtual bool hasLostConnection() = 0;

    /**
     Ends the session with the socket server.
    */
    virtual void disconnect() = 0;

    /**
     reads the latest command sent from the socket server.
     @return string, the latest command received.
    */
    virtual char* readMessage() = 0;

    /**
     emits a message to the server socket.
     @param message - the information to be sent to the server.
    */
    virtual void sendMessage(char* message) = 0;
};

enum Statuses {
  OK,
  UNKNOWN,
  CANNOT_CONNECT,
  STARTING_UP,
  CONNECTING
};

class ICarriage {
  public:
    virtual ~ICarriage(){}
    
    /**
     Tells the carriage that is must go to the next block.
    */
    virtual void goToNextBlock() = 0;

    /**
     Sets the speed of the carriage.
     @param speed - the new speed to set the carriage to.
     @return int, the speed the carriage was previously going.
    */
    virtual int setSpeed(int speed) = 0;

    /**
     @return int, the current speed that the cariage is going.
    */
    virtual int getSpeed() = 0;

    /**
      @return Statuses, the current status of the carriage.
    */
    virtual Statuses getStatus() = 0;

    /**
      @param newStatus - The new status of the carriage.
      @return Statases, the old status of the carriage.
    */
    virtual Statuses setStatuses(Statuses newStatus) = 0;

    /**
      Prevents the carriage from moving no matter what.
    */
    virtual void wait() = 0;

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
};

class ILED {
  public:
    virtual ~ILED(){}

    /**
      @param status - The status for the LEDs to display.
    */
    virtual void displayStatus(Statuses status) = 0;
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

    /**
     Sets the door to be open partially.
     @param degree - How far the door should be open.
    */
    virtual void setOpenDegree(int degree) = 0;
};

enum TrafficLightColour {
  GREEN,
  RED
};

class ITrafficLightSensor {
  public:
    virtual ~ITrafficLightSensor(){}

    virtual bool isGreen() = 0;

    virtual bool isRed() = 0;

    virtual TrafficLightColour getColour() = 0;
};

// WE HAVEN'T BEEN TOLD WHAT THE IDs ARE YET.
class IBlockSensor {
  public:
    virtual ~IBlockSensor(){}

    /**
      @return String, the ID of the latest block sensed.
    */
    virtual char* getCurrentBlock() = 0;
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

#endif
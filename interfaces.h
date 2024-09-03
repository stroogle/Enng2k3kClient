#ifndef interfaces
#define interfaces

class JobQueue {
  public:
    virtual ~IJobQueue() {}

    /**
    * Removes the first message in the queue.
    * @returns the first message
    */
    virtual char* popMessage() = 0;

    /**
    * Given a job string, adds it the queue.
    */
    virtual void addJob(char* job) = 0;

    /**
    * @returns true if the job queue is not empty, false otherwise.
    */
    virtual bool isJobAvailable() = 0;
}

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
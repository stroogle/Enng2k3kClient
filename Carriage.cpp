#include "Arduino.h"
#include "interfaces.h"

class Carriage : public ICarriage {
    public:
        Carriage(){}
        
        int setSpeed(int speed) {
            return -1;
        }

        int getSpeed() {
            return -1;
        }
        
        Statuses getStatus() {
            return UNKNOWN;
        }

        Statuses setStatuses(Statuses newStatus) {
            return UNKNOWN;
        }

        void wait() {}
        
        void stop() {}
    
        void go() {}
        
        void run() {}
};
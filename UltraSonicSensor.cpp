#include "interfaces.h"
#include "Arduino.h"

// Ultrasonic PINs


class UltraSonicSensor : public IDistanceSensor {
  private:
    int sTrigPin;
    int sEchoPin;
    const float safeDistCM = 20.0;
    const float soundSpeed = 0.034; // cm per microsecond
    float sDist = 0;

  public:
    UltraSonicSensor(int trigPin, int echoPin){
      sTrigPin = trigPin;
      sEchoPin = echoPin;
      pinMode(sTrigPin, OUTPUT);
      pinMode(sEchoPin, INPUT);
      digitalWrite(sTrigPin, LOW);
    };

    float getSensorDistance() {
      digitalWrite(sTrigPin, LOW);
      delayMicroseconds(2); // ensure clear signal
      
      digitalWrite(sTrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(sTrigPin, LOW);
      
      // timeout after 23ms - roughly 400cm
      long duration = pulseIn(sEchoPin, HIGH, 23000);
      
      // Calculate distance
      float distance = (duration * soundSpeed) / 2;
      
      return distance;
    }

    void readSensor() {
      sDist = getSensorDistance();
      delay(5); // Small delay between sensor readings to avoid interference
      
      // Serial.print("Sensor Distance: " + sDist + " cm");
    }

    bool isObstacleDetected() {
      if (sDist > 0 && sDist < safeDistCM) {
        return true;
      }
      return false;
    }

    bool isTooClose() {
      return isObstacleDetected();
    }

};
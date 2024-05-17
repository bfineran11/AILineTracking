#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

class MotorControl {
    private:

        /*
            int speed
                - controls the base speed of the robot
                - one of the wheels will be +/- motorAdjust
            
            float multiplier
                - for soft turns, one of the wheels
                  slows down by the amount of pixels the robot 
                  is off the screen * the multipler (to adjust
                  the strength of the turn)
            
            int motorAdjustment
                - don't have the correct pins to implement PID
                  so instead, get the motors as close as we
                  can and counter steer to hope for the best
                 (basically just the P in PID)
        */
        int speed = 0;
        float multiplier = 0;
        int motorAdjustment = 0;

        /*
        
            dirA,B -> pin to send direction the motors will spin
            written to as HIGH or LOW

            pwmA/B -> pin to send power at which the motors spin

            setting default to my pins
        
        */
        int dirA = 12;
        int dirB = 13;

        int pwmA = 3;
        int pwmB = 11;


    public:

        MotorControl(int speed, float multiplier, int motorAdjustment, 
            int dirA, int dirB, int pwmA, int pwmB) {
                
            this->speed = speed;
            this->multiplier = multiplier;
            this->motorAdjustment = motorAdjustment;

            this->dirA = dirA;
            this->dirB = dirB;
            this->pwmA = pwmA;
            this->pwmB = pwmB;

            // Write motors to go forward 
            // opposite because motors are mounted opposite of each other
            digitalWrite(dirA, LOW);
            digitalWrite(dirB, HIGH);
        }

        // no arg
        MotorControl() {
            // some base numbers, works for my robot, might not for yours
            speed = 45;
            multiplier = 4;
            motorAdjustment = 10;

            // Write motors to go forward 
            // opposite because motors are mounted opposite of each other
            digitalWrite(dirA, LOW);
            digitalWrite(dirB, HIGH);
        }

        // turns robot right
        void turnRight(int diff) {
//            analogWrite(pwmA, speed-(diff*multiplier));
            analogWrite(pwmA, speed-20);
            analogWrite(pwmB, speed);
        }

        // turns robot left
        void turnLeft(int diff) {
            analogWrite(pwmA, speed);
//            analogWrite(pwmB, speed-(diff*multiplier));
            analogWrite(pwmB, speed-20);
        }

        // moves robot forward
        void forward() {
            analogWrite(pwmA, speed - motorAdjustment);
            analogWrite(pwmB, speed);
        }

        // stops robot
        void stop() {
            // sets both motors to 0
            analogWrite(pwmA, 0);
            analogWrite(pwmB, 0);         
        }

        void lookAround() {
          digitalWrite(dirA, HIGH);
          digitalWrite(dirB, HIGH);
          analogWrite(pwmA, 35);
          analogWrite(pwmB, 35);
        }


        /*
        
            ACCESSOR AND MUTATORS
        
        */

       int getSpeed() {
            return speed;
       }

       int getMultiplier() {
            return multiplier;
       }

       int getMotorAdjustment() {
            return motorAdjustment;
       }

       void setSpeed(int speedSet) {
        speed = speedSet;
       }

       void setMultiplier(int multiplierSet) {
        multiplier = multiplierSet;
       }

       void setMotorAdjustment(int motorAdjustmentSet) {
        motorAdjustment = motorAdjustmentSet;
       }

};

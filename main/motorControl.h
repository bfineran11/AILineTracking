#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// LOOK AROUND, WHEN THERE IS NO TRACKABLE LINE
void lookAround(int speed);

// set motors to move forward
void moveForward(int speed);

// soft turn right, operates more like a car
void turnRight(int speedDecrease);

// stops robot and turns right 90 degrees
void hardTurnRight();

// soft turn left, operates more like a car
void turnLeft(int speedDecrease);

// stops robot and turns left -90 degrees
void hardTurnLeft();

// stops robot
void stop();
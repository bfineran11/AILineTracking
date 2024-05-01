#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

/*

This software is intended to be run on a HUSKYLENS camera
therefore all screen resolutions are hardcoded, to
that of the physical unit

*/

int SCREEN_WIDTH = 320;
int SCREEN_HEIGHT = 240;

// +/- center of screen that the line can go before 
// the robot changes direction
int line_threshold = 15;

/* 
  returns direction robot need to move in order to get back 
  on cource with the line

  SET MULTIPLIER FROM RETURN -> MOTOR

  directionToMove(HUSYLENSResult result)

  takes a HUSKYLENSResult object
 */
int directionToMove(HUSKYLENSResult result) {

    if (result.command == COMMAND_RETURN_BLOCK){

        // if obj is left of center
        if (x < (160 - threshold)) { 
            Serial.println("left");
            return x-160;
        }

        // if obj is right of center
        if (x > (160 + threshold)) {
            Serial.println("right");
            return x-160;
        }

        // line is in center
        if (x < (160+threshold) && x > (160-threshold)) {
            // move forward
            return 0;
        }

    }

}

// what to do when there is no trackable line
// STOP, LOOK AROUND
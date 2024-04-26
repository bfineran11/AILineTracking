/*
- HUSKYLENS SCREEN RESOLUTION 320x240
*/

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
String directionToMove(HUSKYLENSResult result);
void turnRobot(String direction);

int threshold = 15; // +/- x pixels from center allowed before robot changes direction

int dirA = 12;
int dirB = 13;

int pwmA = 3;
int pwmB = 11;


void setup() {
    // begin on i2c
    Serial.begin(115200);
    Wire.begin();

    pinMode(dirA, OUTPUT);
    pinMode(dirB, OUTPUT);
    analogWrite(pwmA, 180);
    analogWrite(pwmB, 180);

    // Serial print until HUSYLENS is connected to i2c
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }

}

void loop() {

    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!")); // Huskylens not connected
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!")); // no objects learned
    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!")); // nothing detected
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            turnRobot(result);
        }    
    }

}

/* 
  returns direction robot need to move in order to get back 
  on cource with the line

  directionToMove(HUSYLENSResult result)

  takes a HUSKYLENSResult object

  //TODO: MAKE FUNCTION RETURN NUM OF DEGRESS TO MOVE L OR R
 */
String directionToMove(HUSKYLENSResult result) {
    if (result.command == COMMAND_RETURN_BLOCK){
        int x = result.xCenter; // center of obj

        // if obj is left of center
        if (x < (160 - threshold)) { 
            Serial.println("left");
            return "left";
        }
        // if obj is right of center
        if (x > (160 + threshold)) {
            Serial.println("right");
            return "right";
        }
        if (x < (160+threshold) && x > (160-threshold)) {
//          digitalWrite(pwmA, HIGH);
//          digitalWrite(pwmB, LOW);
        }
  } else {
    return "ldldl";
  }
}

void turnRobot(HUSKYLENSResult result) {
  if (directionToMove(result) == "left") {
    analogWrite(pwmA, 180);
    analogWrite(pwmB, 180);
  } else if (directionToMove(result) == "right") {
    
  } else {
    // forget about it
  }

}

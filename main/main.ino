/*
- HUSKYLENS SCREEN RESOLUTION 320x240
*/

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
void directionToMove(HUSKYLENSResult result);
void turnRobot(float degrees);

int threshold = 15; // +/- x pixels from center allowed before robot changes direction

int dirA = 12;
int dirB = 13;

int pwmA = 3;
int pwmB = 11;


void setup() {
    // begin on i2c
    Serial.begin(115200);
    Wire.begin();

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
            directionToMove(result);
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
void directionToMove(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
      int x = result.xCenter;
       if( x < 160 - threshold){ 
        Serial.println("left");
       }
       if(x > 160 + threshold) {
        Serial.println("right");
       }
       
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}


/*
 turns robot n amount of degress in any direction 

 takes a float, degress, for how many degress from center to turn

 10.00 would 10 degrees to the right and -10.00 would be 10 degress to the left
*/
void turnRobot(float degrees) {

}
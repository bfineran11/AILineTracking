/*
- HUSKYLENS SCREEN RESOLUTION 320x240
*/

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "motorControl.h"
#include "visionControl.h"

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL

// dir is motor ON, OFF
// controlled by digitalWrite(pin, HIGH/LOW)
int dirA = 12;
int dirB = 13;

// pwm is motor power
// cotrolled by analogWrite(pin, int)
int pwmA = 3;
int pwmB = 11;


void setup() {
    // begin on i2c
    Serial.begin(115200);
    Wire.begin();

    pinMode(dirA, OUTPUT);
    pinMode(dirB, OUTPUT);

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

            // should print int, +/-
            Serial.println(directionToMove(result));
        }    
    }

}



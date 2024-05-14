#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "motorControl.cpp"
#include "visionControl.cpp"


void setup() {
    // beginning i2c communication with Huskylens
    Serial.begin(115200);
    Wire.begin();


    // checking to see if it is connected
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void loop() {
    if (!huskylens.request()){
        Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    } 
    else if(!huskylens.isLearned()) {
        Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    }
    else if(!huskylens.available()) {
        Serial.println(F("No block or arrow appears on the screen!"));
    }
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            MotorControl mc(60, 4, 10, 12, 13, 3, 11);
            VisionControl vc(15);
            if (vc.findDirectionToTurn(result) == "left") {
                mc.turnLeft();
            } else if (vc.findDirectionToTurn == "right") {
                mc.turnRight();
            } else  {
                mc.forward();
            }
        }    
    }
}

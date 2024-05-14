#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "motorControl.cpp"
#include "visionControl.cpp"

HUSKYLENS huskylens;

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
            MotorControl mc = MotorControl(45, 6, 10, 12, 13, 3, 11);
            VisionControl vc = VisionControl(15);

            int turnN = vc.findDirectionToSmoothTurn(result);
            
            if (turnN < 160) {
                mc.turnLeft(turnN);
            } else if (turnN > 160) {
                mc.turnRight(turnN);
            } else  {
                mc.forward();
            }
        }    
    }
}

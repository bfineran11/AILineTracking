#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <string>

class VisionControl {
    private:

        // huskylens obj
        // HUSKYLENS green line >> SDA; blue line >> SCL
        HUSKYLENS huskylens;

        // +/- x pixels from center allowed before robot changes direction
        int threshold = 0; 

    public:

        VisionControl(int threshold) {
            this->threshold = threshold;
        }

        VisionControl() {
            threshold = 15;
        }

        int findDirectionToSmoothTurn(HUSKYLENSResult result) {
            if (result.command == COMMAND_RETURN_BLOCK) {
                int x = result.xCenter;

                if( x < 160 - threshold){ 
                    return abs(160-x);
                    Serial.println("left");
                }
                if(x > 160 + threshold) {
                    return abs(160-x);
                    Serial.println("right");
                }
                else {
                    return 0;
                }
            }
        }

        String findDirectionToTurn(HUSKYLENSResult result) {
            if (result.command == COMMAND_RETURN_BLOCK){
                int x = result.xCenter;

                if( x < 160 - threshold){ 
                    Serial.println("left");
                    return "left";
                }
                if(x > 160 + threshold) {
                    Serial.println("right");
                    return "right";
                }
                else {
                    Serial.println("forward");
                    return "forward"
                }
            }
        }

}
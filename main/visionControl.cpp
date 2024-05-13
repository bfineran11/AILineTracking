#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

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

        
}
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL

int threshold = 15; // +/- x pixels from center allowed before robot changes direction

int dirA = 12;
int dirB = 13;

int speed = 60;
int pwmA = 3;
int pwmB = 11;


void stop(){
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
  
}
void forward(int t){
  analogWrite(pwmA, speed -10);
  analogWrite(pwmB, speed);
  digitalWrite(dirA, LOW);
  digitalWrite(dirB, HIGH);
}

void turnLeft(int t){
  analogWrite(pwmA, speed);
  analogWrite(pwmB, speed-(t*5));
  digitalWrite(dirA, LOW);
  digitalWrite(dirB, HIGH);
//  delay(t);
}

void turnRight(int t){
  analogWrite(pwmA, speed-(t*5));
  analogWrite(pwmB, speed);
  digitalWrite(dirA, LOW);
  digitalWrite(dirB, HIGH);
//  delay(t);
}


void setup() {
    Serial.begin(115200);
    Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void loop() {
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
//            printResult(result);
            printResultInt(result);
              
        }    
    }
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
      int x = result.xCenter;
        //Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
       if( x < 160 - threshold){ 
        turnLeft(100);
        Serial.println("left");
       }
       if(x > 160 + threshold) {
        Serial.println("right");
        turnRight(100);
       }
       else {
        forward(50);
       }

    }
    else if (result.command == COMMAND_RETURN_ARROW){
      int x1 = result.xOrigin;
      int y1 = result.yOrigin;
      int x2 = result.xTarget;
      int y2 = result.yTarget;
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    if (y1 > y2){
      Serial.println("forward");
      forward(50);
    }
    
    }
    else{ 
        Serial.println("Object unknown!");
    }
}

void printResultInt(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    int x = result.xCenter;

   if( x < 160 - threshold){ 
    turnLeft(abs(160-x));
    Serial.println("left");
   }
   if(x > 160 + threshold) {
    Serial.println("right");
    turnRight(abs(160-x));
   }
   else {
    forward(50);
   }
  }
}

#include<Wire.h>
#include <SPI.h>                      
#include "RF24.h"                     

int msg[1];

RF24 radio(9,10);                   
                                      
const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.




int pinkie = 0; 
int finger = 0; 
int thumb = 0; 

int ringfing=0;
int middlefing=0;

int pinkie_Data = A1;
int finger_Data = A2;
int thumb_Data = A3;
int ringfing_Data=A4;
int middlefing_Data=A5;

//const int MPU_addr = 0x68;
const int MPU2 = 0x69, MPU1 = 0x68;

//First MPU6050
int16_t AcX1, AcY1, AcZ1, Tmp1, GyX1, GyY1, GyZ1;
int minVal = 265;
int maxVal = 402;
double x;
double y;
double z;

//Second MPU6050
int16_t AcX2, AcY2, AcZ2, Tmp2, GyX2, GyY2, GyZ2;
int minVal2 = 265;
int maxVal2 = 402;
double x2;
double y2;
double z2;


int thumb_high = 500;
int thumb_low = 300;
int finger_high = 500;
int finger_low = 300;
int pinkie_high = 500;
int pinkie_low = 300;



bool bool_caliberate = false;

int response_time = 100;

void setup() {
  pinMode(3, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true); Wire.begin();
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);
  Wire.write(0); 
  Wire.endTransmission(true);
  Serial.begin(4800);
  delay(1000);
  radio.begin();                      
  radio.openWritingPipe(pipe);        
}

void loop() {
  
  
  debug_flex(); 
  //Serial.println("test");


  
  GetMpuValue1(MPU1);
  delay(10);


    
  GetMpuValue2(MPU2);
  //Serial.println("");
  delay(10);

}
//------------------------------------------------------------------------------------
// --------------------------------------MPU1--------------------------
void GetMpuValue1(const int MPU) {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers

  AcX1 = Wire.read() << 8 | Wire.read(); 
  AcY1 = Wire.read() << 8 |  Wire.read(); 
  AcZ1 = Wire.read() << 8 | Wire.read();

  Tmp1 = Wire.read() << 8 | Wire.read();

  int xAng = map(AcX1, minVal, maxVal, -90, 90);
  int yAng = map(AcY1, minVal, maxVal, -90, 90);
  int zAng = map(AcZ1, minVal, maxVal, -90, 90);

  GyX1 = Wire.read() << 8 | Wire.read(); 
  GyY1 = Wire.read() << 8 | Wire.read(); 
  GyZ1 = Wire.read() << 8 | Wire.read(); 

  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI) + 4; 
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  //-- Comment to Debug
  //  Serial.print("AngleX= ");
  //  Serial.print(x);
  //  Serial.print("\t");
  //
  //  Serial.print("AngleY= ");
  //  Serial.print(y);
  //  Serial.print("\t");
  //
  //  Serial.print("AngleZ= ");
  //  Serial.print(z);
  //  Serial.print("\t");
  //  Serial.println("-----------------------------------------");


  //  Serial.print("AcX = ");
  //  Serial.print(AcX1);
  //  Serial.print(" | AcY = ");
  //  Serial.print(AcY1);
  //  Serial.print(" | AcZ = ");
  //  Serial.print(AcZ1);
  //  Serial.print(" | GyX = ");
  //  Serial.print(GyX1);
  //  Serial.print(" | GyY = ");
  //  Serial.print(GyY1);
  //  Serial.print(" | GyZ = ");
  //  Serial.println(GyZ1);

}

//-----------------------------------------------------------------------------------------
//------------------------------------------------MPU 2-------------------------------------

void GetMpuValue2(const int MPU) {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); 
  AcX2 = Wire.read() << 8 | Wire.read(); 
  AcY2 = Wire.read() << 8 |  Wire.read();
  AcZ2 = Wire.read() << 8 | Wire.read(); 

  Tmp2 = Wire.read() << 8 | Wire.read(); 

  int xAng2 = map(AcX2, minVal2, maxVal2, -90, 90);
  int yAng2 = map(AcY2, minVal2, maxVal2, -90, 90);
  int zAng2 = map(AcZ2, minVal2, maxVal2, -90, 90);

  GyX2 = Wire.read() << 8 | Wire.read(); 
  GyY2 = Wire.read() << 8 | Wire.read(); 
  GyZ2 = Wire.read() << 8 | Wire.read(); 

  x2 = RAD_TO_DEG * (atan2(-yAng2, -zAng2) + PI) + 4; 
  y2 = RAD_TO_DEG * (atan2(-xAng2, -zAng2) + PI);
  z2 = RAD_TO_DEG * (atan2(-yAng2, -xAng2) + PI);

  //-- Comment to Debug
  //    Serial.print("AcX = ");
  //    Serial.print(AcX2);
  //    Serial.print(" | AcY = ");
  //    Serial.print(AcY2);
  //    Serial.print(" | AcZ = ");
  //    Serial.print(AcZ2);
  //    Serial.print(" | GyX = ");
  //    Serial.print(GyX2);
  //    Serial.print(" | GyY = ");
  //    Serial.print(GyY2);
  //    Serial.print(" | GyZ = ");
  //    Serial.println(GyZ2);
  //
  //    Serial.print("AngleX2= ");
  //    Serial.print(x2);
  //    Serial.print("\t");
  //
  //    Serial.print("AngleY2= ");
  //    Serial.print(y2);
  //    Serial.print("\t");
  //
  //    Serial.print("AngleZ2= ");
  //    Serial.print(z2);
  //    Serial.print("\t");
  //  Serial.println("-----------------------------------------");

}


//-----------------------------------------------------------------------------------
//--------------------------------------Flex debug-----------------------------

void debug_flex() {
  //Sends value as a serial monitor to port
  //thumb (Claw open / close)
  Serial.print("Thumb: ");
  Serial.print(thumb);
  Serial.print("\t");
  //  //thumb Params
  Serial.print("thumb High: ");
  Serial.print(thumb_high);
  Serial.print("\t");
  Serial.print("T Low: ");
  Serial.print(thumb_low);
  Serial.print("\t");

  //finger (Claw Further)
  Serial.print("finger: ");
  Serial.print(finger);
  Serial.print("\t");

  //  finger Params
  Serial.print("finger High: ");
  Serial.print(finger_high);
  Serial.print("\t");
  Serial.print("finger Low: ");
  Serial.print(finger_low);
  Serial.print("\t");

  //Pinkie (Claw Further)
  Serial.print("Pinkie: ");
  Serial.print(pinkie);
  Serial.print("\t");

  //  //Pinkie Params
  Serial.print("Pinkie High: ");
  Serial.print(pinkie_high);
  Serial.print("\t");
  Serial.print("Pinkie Low: ");
  Serial.print(pinkie_low);
  Serial.print("\t");
  Serial.println();
}

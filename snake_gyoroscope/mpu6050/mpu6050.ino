#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    

int potX=20;
int potY=21;

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  pinMode(potX,INPUT);
  pinMode(potY,INPUT);
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Z axis data
  data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  delay(200);
  //Serial.print("Axis X = ");
  //Serial.print(data.X);
  //Serial.print("  ");
  //Serial.print("Axis Y = ");
  //Serial.print(data.Y);
  //Serial.print("  ");
  //Serial.print("Axis Z  = ");
  //Serial.println(data.Z);
// x - 126, y - 130or 135, z - 250
// x-122, y - 135, z - 245
  if (data.X>=180 & data.Y<= 196 & data.Z>=210)
     Serial.println('u');
  else if(data.X>=122 & data.Y <= 100 & data.Z<=245)
     Serial.println('r');
  else if (data.X<=122 & data.Y<= 135 & data.Z <=245)
     Serial.println('d');
  else if (data.X<=180 & data.Y>= 196 & data.Z <=227)
      Serial.println('l');
  //else if (data.X>=126 & data.Y<= 100 & data.Z <=250)
      //Serial.println('r'); 
  //else if (data.X==0 & data.Y== 0 & data.Z ==0)
      //Serial.print('q');  
  delay(20);  
}

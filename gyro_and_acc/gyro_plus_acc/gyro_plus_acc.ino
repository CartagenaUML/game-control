#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"   

// I2C addresses and register addresses for MPU6050
//const int MPU6050 = 0x68; // I2C address, A0 pulled LOW
const int PWR_MGMT_1 = 0x6B; // Register address Power Management 1
const int ACCEL_XOUT_HIGH_BYTE = 0x3B; // Register address for x acceleration high byte
const int ACCEL_XOUT_LOW_BYTE = 0x3C; // Register address for x acceleration low byte
const int ACCEL_YOUT_HIGH_BYTE = 0x3D; // Register address for y acceleration high byte
const int ACCEL_YOUT_LOW_BYTE = 0x3E; // Register address for y acceleration low byte
const int ACCEL_ZOUT_HIGH_BYTE = 0x3F; // Register address for z acceleration high byte
const int ACCEL_ZOUT_LOW_BYTE = 0x40; // Register address for z acceleration low byte

// joystick
const int potX=A0;
const int potY=A1;

// gyroscope
const int intp1=20;
const int intp2=21;

// other variables
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};
MyData data;

// threshold for shaking
const int shakeThreshold = 10000;

// global variables for MPU-6050
float accX, accY, accZ;
volatile bool dataInterrupt = false;
int totalAcc;

// Pinouts for assignemnt
const int BUZZ = 4;
const int INTERRUPT_MPU = 2;

// LED statusj
int led_status = HIGH;
int incomingByte = 0;

// joystick values
int xVal=0;//initially x value of joystick 0
int yVal=0;//initially y value of joystick 0

void setup() {
// initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize pins for gyro
  pinMode(intp1,INPUT);
  pinMode(intp2,INPUT);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Initialize digital pin 2 as output
  pinMode(BUZZ, OUTPUT);

  digitalWrite(BUZZ, LOW); // turn buzzer off
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
  led_status = LOW;

  digitalWrite(INTERRUPT_MPU, INPUT);
  //attachInterrupt(digitalPinToInterrupt(INTERRUPT_MPU), mpuDataReady, RISING);
  // initialize I2C communication
  Wire.begin();
  //Wire.beginTransmission(MPU6050);
  Wire.write(PWR_MGMT_1); // Talk to power managemnt of MPU6050
  Wire.write(0x80); // do a device reset and all internal register go to default values
  Wire.endTransmission(true); // I2C Stop
}

void food_eat(){
if (Serial.available() > 0) {// read from the Serial port:
  incomingByte = Serial.read();   // read the incoming byte:
  Serial.print(incomingByte);
  digitalWrite(BUZZ,HIGH);
  delay(100);
  digitalWrite(BUZZ,LOW);
  // Serial.print('food eaten');
  }
}

void loop() {
  // TODO: 
  // I2C code here
  // accelerometer data
  //Wire.beginTransmission(MPU6050);
  //Wire.write(ACCEL_XOUT_HIGH_BYTE);
  // restart I2C, do not stop
  //Wire.endTransmission(false);
  // read from register 0x3B to register 0x40 for x, y and z acceleration
  // default range +-2g
  //Wire.requestFrom(MPU6050, 6, true);
  //accX = (Wire.read() << 8| Wire.read()) / 16384.0;
  //accY = (Wire.read() << 8| Wire.read()) / 16384.0;
  //accZ = (Wire.read() << 8| Wire.read()) / 16384.0;

 
  //if (accX < 0) {
  //  accX = accX * -1;
  //}
  //if (accY < 0) {
  //  accY = accY * -1;
  //}
  //if (accZ < 0) {
  //  accZ = accZ * -1;
  //}

  //totalAcc = accX + accY + accZ;
  //if (totalAcc >= 3) {
  //  Serial.print("q");
  //}

  // joystick code below
  xVal=map(analogRead(potX) +8,0,1023,-5,+5);//mapping x axis valus from vx pin of joystick low to -5 and high to +5 for easier reading
yVal=map(analogRead(potY)-8,0,1023,-5,+5);//mapping y axis valus from vy pin of joystick low to -5 and high to +5 for easier reading

if (xVal==0 & yVal== 0){//if x axis value of joystick &  y axis value of joystick is 0
   Serial.print('s');
   // write s
}
if (xVal>= 0 & yVal== -5) {
   Serial.print('u');
   food_eat();
}
if (xVal==0 & yVal>=4){
    Serial.print('d');
    food_eat();
}
if (xVal==-5 & yVal<=5){
    Serial.print('l'); 
    food_eat();
}
if (xVal>=5 & yVal<=5){
    Serial.print('r');
    food_eat();
}

   // gyroscope code below
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
  if (data.X>=180 & data.Y<= 196 & data.Z>=210){
     Serial.println('u');
     food_eat();
  }
  else if(data.X>=122 & data.Y <= 100 & data.Z<=245){
     Serial.println('r');
     food_eat();
  }
  else if (data.X<=122 & data.Y<= 135 & data.Z <=245){
     Serial.println('d');
     food_eat();
  }
  else if (data.X<=180 & data.Y>= 196 & data.Z <=227){
      Serial.println('l');
      food_eat();
  }
  //else if (isShaking()){
  //    Serial.println('q');
  //} 
  delay(10);

  /*// read from the Serial port:
  if (Serial.available() > 0) {

    // read the incoming byte:
    incomingByte = Serial.read();

    // flip LED to indicate serial read
    led_status = (led_status == HIGH)? LOW : HIGH;
    digitalWrite(LED_BUILTIN, led_status);

    // B for Buzz
    if (incomingByte == 'B') { 
      digitalWrite(BUZZ, HIGH);
    }
    // U for Unbuzz
    else if (incomingByte == 'U') {
      digitalWrite(BUZZ, LOW);
    }
    }*/
}

  // write to serial port
  // this can go after I2C read and after joystick read

bool isShaking() {
  static int16_t prev_ax = 0, prev_ay = 0, prev_az = 0;
  int16_t delta_ax = ax - prev_ax;
  int16_t delta_ay = ay - prev_ay;
  int16_t delta_az = az - prev_az;

  // Calculate total acceleration change
  //int16_t delta = delta_ax * delta_ax + delta_ay * delta_ay + delta_az * delta_az;
  int16_t delta = delta_ax + delta_ay + delta_az;

  // Update previous values
  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;

  // Check if acceleration change exceeds threshold
  return delta < shakeThreshold;
}


void mpuDataReady() {
  dataInterrupt = true;
}

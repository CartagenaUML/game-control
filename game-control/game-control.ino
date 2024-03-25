// game-control.ino
// Authors:
// Prathiba
// Cheryl
// Salvador
// TODO:
// Control Up, Down, Left, Right movement of snake in snake.py with joystick and MPU6050 Gyro (gyro and joystick do not have to work at the same time)
// Turn apple in snake.py golden when shaking detected with MPU6050 accelerometer, increase points by x2 when apple is consumed
// Receive a signal from snake.py when apple eaten so that Arduino can momentarily buzz an active buzzer

// Some accelerometer and gyro ideas taken from 
// https://howtomechatronics.com/tutorials/arduino/arduino-and-mpu6050-accelerometer-and-gyroscope-tutorial/
// Author is Dejan

#include "Wire.h"

// I2C addresses and register addresses for MPU6050
const int MPU6050 = 0x68; // I2C address, A0 pulled LOW
const int PWR_MGMT_1 = 0x6B; // Register address Power Management 1
const int ACCEL_XOUT_HIGH_BYTE = 0x3B; // Register address for x acceleration high byte
const int ACCEL_XOUT_LOW_BYTE = 0x3C; // Register address for x acceleration low byte
const int ACCEL_YOUT_HIGH_BYTE = 0x3D; // Register address for y acceleration high byte
const int ACCEL_YOUT_LOW_BYTE = 0x3E; // Register address for y acceleration low byte
const int ACCEL_ZOUT_HIGH_BYTE = 0x3F; // Register address for z acceleration high byte
const int ACCEL_ZOUT_LOW_BYTE = 0x40; // Register address for z acceleration low byte
const int GYRO_XOUT_HIGH_BYTE = 0x43; // Register address for x direction gyroscope high byte

// joystick potentioemters
const int potX=A0;
const int potY=A1;

// global variables for MPU-6050
float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
volatile bool dataInterrupt = false;
int totalAcc;

// Pinouts for assignemnt
const int BUZZ = 4;
const int INTERRUPT_MPU = 2;

// LED status
int led_status = HIGH;
int incomingByte = 0;

// joystick values
int xVal=0;//initially x value of joystick 0
int yVal=0;//initially y value of joystick 0

void setup() {
// initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
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
  Wire.beginTransmission(MPU6050);
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
  Wire.beginTransmission(MPU6050);
  Wire.write(ACCEL_XOUT_HIGH_BYTE);
  // restart I2C, do not stop
  Wire.endTransmission(false);
  // read from register 0x3B to register 0x40 for x, y and z acceleration
  // default range +-2g
  Wire.requestFrom(MPU6050, 6, true);
  accX = (Wire.read() << 8| Wire.read()) / 16384.0;
  accY = (Wire.read() << 8| Wire.read()) / 16384.0;
  accZ = (Wire.read() << 8| Wire.read()) / 16384.0;

  Wire.beginTransmission(MPU6050);
  Wire.write(GYRO_XOUT_HIGH_BYTE);
  // restart I2C, do not stop
  Wire.endTransmission(false);
  // read from register 0x43 to register 0x48 for x, y and z gyroscope
  // default range +-131 LSB/degree/s
  Wire.requestFrom(MPU6050, 6, true);
  gyroX = (Wire.read() << 8| Wire.read()) / 131.0;
  gyroY = (Wire.read() << 8| Wire.read()) / 131.0;
  gyroZ = (Wire.read() << 8| Wire.read()) / 131.0;
  /*
  Serial.print("Axis X = ");
  Serial.print(gyroX);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(gyroY);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(gyroZ);
  */
  if (accX < 0) {
    accX = accX * -1;
  }
  if (accY < 0) {
    accY = accY * -1;
  }
  if (accZ < 0) {
    accZ = accZ * -1;
  }

  totalAcc = accX + accY + accZ;
  if (totalAcc >= 2) {
    Serial.println("q");
  }

  xVal=map(analogRead(potX) +8,0,1023,-5,+5);//mapping x axis valus from vx pin of joystick low to -5 and high to +5 for easier reading
  yVal=map(analogRead(potY)-8,0,1023,-5,+5);//mapping y axis valus from vy pin of joystick low to -5 and high to +5 for easier reading

  if ((xVal>= 0 & yVal== -5) | gyroY < -100) {
    Serial.println('u');
    food_eat();
  }
  if ((xVal==0 & yVal>=4) | gyroY > 100){
      Serial.println('d');
      food_eat();
  }
  if ((xVal==-5 & yVal<=5) | gyroX > 100){
      Serial.println('l'); 
      food_eat();
  }
  if ((xVal>=5 & yVal<=5) | gyroX < -100){
      Serial.println('r');
      food_eat();
  }

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


void mpuDataReady() {
  dataInterrupt = true;
}

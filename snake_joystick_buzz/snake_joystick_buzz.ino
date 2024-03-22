int potX=A0;
int potY=A1;
//int potZ=2;
//int buzz=9;
//int incomingByte = 0;
int buzzer = 4;//the pin of the active buzzer
int buzzer_status =LOW;//initially set buzz low
int incomingByte=0;//initially set incoming byte 0
int xVal=0;//initially x value of joystick 0
int yVal=0;//initially y value of joystick 0

 
void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
pinMode(potX,INPUT);//setting Vx pin of joystick as input
pinMode(potY,INPUT);//setting Vy pin of joystick as input
pinMode(buzzer,OUTPUT);//setting buzzer pin as output
}
void food_eat(){
if (Serial.available() > 0) {// read from the Serial port:
  incomingByte = Serial.read();   // read the incoming byte:
  Serial.print(incomingByte);
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  Serial.print('food eaten');
  }
}
void loop() {
  // put your main code here, to run repeatedly:
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
//delay(20);  
}
}






 
 
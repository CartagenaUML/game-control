int potX=A0;
int potY=A1;
//int potZ=2;
//int buzz=9;
//int incomingByte = 0;
 
int xVal=0;
int yVal=0;
//int zVal=0;
 
void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
pinMode(potX,INPUT);
pinMode(potY,INPUT);
//pinMode(buzz,OUTPUT);
//digitalWrite(buzz,HIGH);
//buzz =LOW;
//pinMode(potZ,INPUT);
//digitalWrite(potZ,HIGH);

}
 
void loop() {
  // put your main code here, to run repeatedly:
xVal=map(analogRead(potX) +8,0,1023,-5,+5);
yVal=map(analogRead(potY)-8,0,1023,-5,+5);
//Serial.println(xVal);
//Serial.println(yVal);
//delay(40);
//zVal=digitalRead(potZ);
if (xVal==0 & yVal== 0)
   Serial.println('s');
else if (xVal>= 0 & yVal== -5)
   Serial.println('u');
else if (xVal==0 & yVal>=4)
    Serial.println('d');
else if (xVal==-5 & yVal<=5)
    Serial.println('l'); 
else if (xVal>=5 & yVal<=5)
    Serial.println('r');  
delay(20);  
//delay(20);
 //if (Serial.available() > 0) {
    // read the incoming byte:
    //incomingByte = Serial.read();
   //Serial.println(incomingByte);
    
    //if(incomingByte == 'E') {
      // sound buzzer
    
      //digitalWrite(buzz, HIGH);
    }
  

 // 
  //Serial.println("Hello");

//}



//Serial.println(zVal);



 
 
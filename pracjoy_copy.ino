int potX=A0;
int potY=A1;
//int potZ=2;
int dl=100;
 
int xVal=0;
int yVal=0;
//int zVal=0;
 
void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
pinMode(potX,INPUT);
pinMode(potY,INPUT);
//pinMode(potZ,INPUT);
//digitalWrite(potZ,HIGH);
delay(dl);
}
 
void loop() {
  // put your main code here, to run repeatedly:
xVal=analogRead(potX);
yVal=analogRead(potY);
//zVal=digitalRead(potZ);
Serial.print(xVal);
Serial.print(',');
Serial.println(yVal);

delay(40);
//Serial.println(zVal);


}
 
 
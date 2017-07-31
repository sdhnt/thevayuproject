
#include <Servo.h>
Servo fin;
int finpos=90;
int motorspeed=0;
void setup(){
  //start serial connection
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(11, INPUT );
  pinMode(12, INPUT); 
   pinMode(9, INPUT);
  pinMode(10, INPUT); 
  pinMode(6,OUTPUT);
  fin.attach(8);
  Serial.begin(9600);

}

void loop(){
  
  if(finpos>=180)
  {finpos=180;}
  else if (finpos<=0)
  {finpos=0;}
  fin.write(finpos);
 
  int UP = digitalRead(12);//white
  int Down=digitalRead(11);//blue
  int Right=digitalRead(9);//green
  int Left=digitalRead(10);//yellow
  Serial.print(UP);
  Serial.print(Down);
  Serial.print(Left);
  Serial.println(Right);

  
  if(UP==1)
  { finpos+=5;}//Rt
  else if(Down==1)
  {finpos-=5;}//Lt
  if(Left==1)//up
  {analogWrite(6, 250 );} 
  else
  {analogWrite(6, 0);}//down
  delay(100);
      
  
  }





#include <Servo.h>
Servo fin;
int finpos=90;
int motorspeed=0;
void setup(){
  //start serial connection
  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(11, INPUT);
  pinMode(12, INPUT); 
   pinMode(9, INPUT);
  pinMode(10, INPUT); 
  fin.attach(6);
  fin.write(90);
  //Serial.begin(9600);

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
  int code=UP*1000+Down*100+Left*10+Right;
  //Serial.print(code);
 
  if(code==11) //if UP
  { analogWrite(6, 250 ); } 
  else if(code==1)//Down
  {  analogWrite(6, 0);    }

  else if(code==1001)//right
  {     finpos+=5;  }
  else if(code==101)//left
  {  finpos-=5;  }

  delay(100);   
  }





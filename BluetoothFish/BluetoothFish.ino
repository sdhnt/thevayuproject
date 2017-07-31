#include <SoftwareSerial.h>
#include<Servo.h>
SoftwareSerial portIN(10, 11); //TX, RX
SoftwareSerial portO(8,9);
int pos=90;
int ledpin=13;
int BluetoothData; 
Servo fin;
void setup() {
 
  portIN.begin(9600);
  portO.begin(9600);
  fin.attach(6);
  pinMode(ledpin,OUTPUT);
  fin.write(pos);
  portO.listen();
  portO.println("OUTPUT BLUETOOTH"); Serial.println();
}

void loop() {
 portIN.listen();
if (portIN.available()){  
BluetoothData=portIN.read();
portO.listen();
   if(BluetoothData=='1'){ 
   pos=pos+10;fin.write(pos); portO.println("LOL");
 //  portO.println("Servo left! ");
//Serial.println();
   }

   
  if (BluetoothData=='0'){
    pos=90;fin.write(pos);
  // portO.println("Servo centered! ");
//Serial.println();
  }

  if (BluetoothData=='2'){
    pos= pos-10;fin.write(pos);
//   portO.println("Servo right! ");
//Serial.println();
  }
}
else
{
  fin.write(pos);
}
delay(100);
}


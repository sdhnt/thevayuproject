#define encoder0PinA 2

#define pwmPin 9
int RCsignal;

const int enablePin = 4;                  //AMP enable pin

volatile unsigned long encoder0Pos = 0;   //Count plus  
unsigned long t = 0;                      //Time recording
const float pi =3.14;
float currentSpeed = 0.0;                            //Rotation speed
float requireSpeed = 2*pi;                        //set speed(rad/s)
float error = 0.0;                        //difference between current velocity and set velocity
int pwmOutput = 0;                           //generate PWM signal
float Kp = 1;                                //PID parameters
float Ki = 0.5;
float Kd = 0.5;
long lastCount = 0;                       //
long count = 0;                           //Times of counts for calculating speed

void setup() {
  Serial.begin(9600);                     //Communicate with computer
  pinMode(encoder0PinA, INPUT);           //encouder input pin 
  //pinMode(enablePin, OUTPUT);             //Output pin for AMP
  pinMode(pwmPin, OUTPUT);                //generate pwm signal
  //digitalWrite(enablePin, HIGH);          //Enable 1Y,2Y on AMP
  attachInterrupt(0, doEncoderA, CHANGE); //Interrupt when status change
  pinMode(7, INPUT);
// encoder pin on interrupt 1 (pin 3)
}

void loop(){
  RCsignal = digitalRead(7);
  Serial.println(RCsignal);
  
  if(RCsignal ==1 && (requireSpeed)<=30)
  {
    requireSpeed = requireSpeed+0.5;
  }
  else if(RCsignal ==0 && requireSpeed>0)
  {
    requireSpeed =requireSpeed-0.5;
  }

if(millis() - t >= 50){                   //Calculate speed every 20ms
  t = millis();
  getSpeed();                              //get motor speed
  pwmOutput = updatePid(pwmOutput, requireSpeed, currentSpeed);  // get pwm output
  analogWrite(pwmPin, pwmOutput);
  Serial.print(requireSpeed);
  //Serial.print(" ");
  //Serial.println(currentSpeed);
  //Serial.print(" ");
  //Serial.println(t);
  }
}

void getSpeed(){                       
  count = encoder0Pos - lastCount;
  lastCount = encoder0Pos;
  currentSpeed = count*2*pi/1000.0/0.05/21;  //Unit: rad/s. 4.4 for small motor, 21 for big motor
}

int updatePid(int outputValue, float targetValue, float currentValue){
  float pidTerm = 0;
  float integral = 0;
  float derivative = 0;
  int error = 0;
  static int lastError = 0;
  error = targetValue - currentValue;
  derivative = (error - lastError)/0.1;
  integral = integral + error*0.1;
  pidTerm = (Kp*error) + (Ki*integral) + (Kd*derivative);
  lastError = error;
  return constrain(outputValue + int(pidTerm), 0, 255);
}

void doEncoderA(){
  encoder0Pos++;
  }

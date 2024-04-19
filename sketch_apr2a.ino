
#include <AFMotor.h>
#include <Servo.h>
#define speed 110
#define Trig A0
#define Echo A1
#define spoint 90
#define MAX_SPEED 190 // sets speed of DC  motors

int speedSet = 0;
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
Servo servo;
AF_DCMotor M3(3);
AF_DCMotor M4(4);
char command;
 
void setup() {
  Serial.begin(9600);  
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(10);
  start();
  M3.setSpeed(speed);
  M4.setSpeed(speed);
 
}
 
void loop() 
{
    distance = ultrasonic();
    if (distance <= 15) 
    {
      Stop();
      backward();
      delay(250);
      Stop();
      L = leftsee();
      servo.write(spoint);
      delay(800);
      R = rightsee();
      servo.write(spoint);
      if (L < R) 
      {
        turnleft();
        delay(270);
        Stop();
        delay(200);
      } 
      else if (L > R) 
      {
        turnright();
        delay(270);
        Stop();
        delay(200);
      }
    } 
    else 
    {

      if(Serial.available() > 0)
      { 
        command = Serial.read(); 
        Stop();      
        switch(command)
        {
          case 'F':  
            forward();
            break;
          case 'B':  
            backward();
            break;
          case 'L':  
            turnleft();
            break;
          case 'R':
            turnright();
            break;
          case 'S':
            Stop();
            break;          
        }
      }
    }
}
void forward()
{
    M3.setSpeed(speed);
    M3.run(FORWARD); 
    M4.setSpeed(speed);
    M4.run(FORWARD);   
}

void backward()
{
  M3.setSpeed(speed); 
  M3.run(BACKWARD); 
  M4.setSpeed(speed); 
  M4.run(BACKWARD);
}

void turnleft()
{
  M3.setSpeed(speed); 
  M3.run(BACKWARD);  
  M4.setSpeed(speed); 
  M4.run(FORWARD);  
}

void turnright()
{
  M3.setSpeed(speed);
  M3.run(FORWARD); 
  M4.setSpeed(speed); 
  M4.run(BACKWARD); 
} 

void Stop()
{
  
  M3.setSpeed(0); 
  M3.run(RELEASE); 
  M4.setSpeed(0); 
  M4.run(RELEASE); 
}
int leftsee() {
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return Left;
}
 
int rightsee() {
  servo.write(150);
  delay(800);
  Right = ultrasonic();
  return Right;
}
 
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t*0.034/2; //time convert distance
  return cm;
}
void start() {
  delay(3000);
  for (int a = 0; a < 4; a++) {
    servo.write(spoint);
    delay(50);
    servo.write(40);
    delay(50);
    servo.write(90);
    delay(50);
    servo.write(spoint);
  }
}
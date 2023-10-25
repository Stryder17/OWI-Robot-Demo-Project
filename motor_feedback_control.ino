#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create an instance of Adafruit Motor Shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Define analog pins for potentiometer
#define pot1 A8
#define pot2 A10
#define pot3 A12
#define pot4 A15
#define pot5 A15

// Pins for Gripper control
int in1 = 25;
int in2 = 24;
int en1 = 45;
int pwm = 225;

void setup() {
  Serial.begin(9600);

  AFMS.begin();

  delay(2000);
  Serial.println("-----------------------------------------");

  // Home position
  motor4_gotoPosition(5);      // Gripper open
  delay(500);

  motor3_gotoPosition(20);      // Motor3 up
  delay(500);

  motor2_gotoPosition(-20);     // Motor 2 up
  delay(500);

  motor1_gotoPosition(20);     // Pickup zone
  delay(500);

  motor2_gotoPosition(-40);     // Motor 2 down
  delay(500);

  motor3_gotoPosition(68);      // Motor3 down
  delay(500);

  gripperClose();      // Gripper close
  gripperClose();
  gripperClose();
  delay(500);
}

void loop() {
  /*
  motor4_gotoPosition(5);      // Gripper open
  delay(1500);

  motor4_gotoPosition(13);      // Gripper close
  delay(500);
*/
  motor3_gotoPosition(20);      // Motor3 up
  delay(500);

  motor2_gotoPosition(-20);     // Motor 2 up
  delay(500);

  motor1_gotoPosition(-20);     // Drop-off zone
  delay(500);
  
  motor2_gotoPosition(-40);     // Motor 2 down
  delay(500);

  motor3_gotoPosition(68);      // Motor3 down
  delay(500);

  motor4_gotoPosition(5);      // Gripper open
  delay(500);
  delay(4000);                  // Trace point on the paper sheet

  motor4_gotoPosition(14);      // Gripper close
  delay(500);

  motor3_gotoPosition(20);      // Motor3 up
  delay(500);

  motor2_gotoPosition(-20);     // Motor 2 up
  delay(500);

  motor1_gotoPosition(20);     // Pickup zone
  delay(500);

  motor2_gotoPosition(-40);     // Motor 2 down
  delay(500);

  motor3_gotoPosition(65);      // Motor3 down
  delay(500);

  //motor4_gotoPosition(8);      // Gripper open
  //delay(1500);
  
}

//------------------------------------------------------------------//
// Functions
void motor1_gotoPosition(int setpoint){
Adafruit_DCMotor *motor = AFMS.getMotor(1);
motor->setSpeed(75);

  int analogValue = analogRead(pot1);
  int angle = map(analogValue, 0, 1023, -135, 135);   // Mapping to angle
  Serial.print("M1_Angle: ");
  Serial.println(angle);

  while(abs(setpoint-angle)>1){
    if(setpoint-angle>0){
      motor->run(FORWARD);
    }
    else if(setpoint-angle<0){
      motor->run(BACKWARD);
    }
    analogValue = analogRead(pot1);
    angle = map(analogValue, 0, 1023, -135, 135);
  }
  motor->run(RELEASE);
  return;
}

void motor2_gotoPosition(int setpoint){
  Adafruit_DCMotor *motor = AFMS.getMotor(2);
  motor->setSpeed(75);

  int analogValue = analogRead(pot2);
  int angle = map(analogValue, 0, 1023, 135, -135);   // Mapping to angle
  Serial.print("M2_Angle: ");
  Serial.println(angle);

  while(abs(setpoint-angle)>1){
    if(setpoint-angle>0){
      motor->run(FORWARD);
    }
    else if(setpoint-angle<0){
      motor->run(BACKWARD);
    }
    analogValue = analogRead(pot2);
    angle = map(analogValue, 0, 1023, 135, -135);
  }
  motor->run(RELEASE);
  return;
}

void motor3_gotoPosition(int setpoint){
  Adafruit_DCMotor *motor = AFMS.getMotor(3);
  motor->setSpeed(75);

  int analogValue = analogRead(pot3);
  int angle = map(analogValue, 0, 1023, -135, 135);   // Mapping to angle
  Serial.print("M3_Angle: ");
  Serial.println(angle);

  while(abs(setpoint-angle)>1){
    if(setpoint-angle>0){
      motor->run(BACKWARD);
    }
    else if(setpoint-angle<0){
      motor->run(FORWARD);
    }
    analogValue = analogRead(pot3);
    angle = map(analogValue, 0, 1023, -135, 135);
  }
  motor->run(RELEASE);
  return;
}

void motor4_gotoPosition(int setpoint){
  Adafruit_DCMotor *motor = AFMS.getMotor(4);
  motor->setSpeed(65);

  int analogValue = analogRead(pot4);
  int angle = map(analogValue, 0, 1023, -135, 135);   // Mapping to angle
  Serial.print("M4_Angle: ");
  Serial.println(angle);

  while(abs(setpoint-angle)>2){
    if(setpoint-angle>0){
      motor->run(FORWARD);
    }
    else if(setpoint-angle<0){
      motor->run(BACKWARD);
    }
    analogValue = analogRead(pot4);
    angle = map(analogValue, 0, 1023, -135, 135);
  }
  motor->run(RELEASE);
  return;
}

void gripper_gotoPosition(int setpoint){
  Adafruit_DCMotor *motor = AFMS.getMotor(2);
  motor->setSpeed(50);

  int analogValue = analogRead(pot5);
  int angle = map(analogValue, 0, 1023, -135, 135);   // Mapping to angle
  Serial.print("Gripper_Angle: ");
  Serial.println(angle);

  while(abs(setpoint-angle)>2){
    if(setpoint-angle>0){
      gripperClose();
    }
    else if(setpoint-angle<0){
      gripperOpen();
    }
    analogValue = analogRead(pot5);
    angle = map(analogValue, 0, 1023, -135, 135);
  }
  motor->run(RELEASE);
  return;
}
/*
void gripperOpen(){
  // Set direction forward and supply power to Motor
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(en1, pwm);
  delay(300);
  analogWrite(en1, 0);       // Turn off power
}

void gripperClose(){
  // Set direction forward and supply power to Motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(en1, pwm);
  delay(300);
  analogWrite(en1, 0);       // Turn off power
}
*/

void gripperOpen(){
  Adafruit_DCMotor *motor = AFMS.getMotor(4);
  motor->setSpeed(50);
  motor->run(FORWARD);
  delay(300);
  motor->run(RELEASE);
  return;
}

void gripperClose(){
Adafruit_DCMotor *motor = AFMS.getMotor(4);
  motor->setSpeed(50);
  motor->run(FORWARD);
  delay(550);
  motor->run(RELEASE);
  return;
}
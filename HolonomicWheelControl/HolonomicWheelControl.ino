//include "HolonomicWheel.h"

//HolonomicWheel w1;
//HolonomicWheel w2;
//HolonomicWheel w3;
//HolonomicWheel w4;

byte X_PIN = A0;
byte Y_PIN = A1;
int deadzone = 50;

byte frontSpeed_PIN = 11;
byte frontDirLeft_PIN = 13;
byte frontDirRight_PIN = 6;

byte leftSpeed_PIN = 9;
byte leftDirForwards_PIN = 12;
byte leftDirReverse_PIN = 10;

byte rightSpeed_PIN = 3;
byte rightDirForwards_PIN = 2;
byte rightDirReverse_PIN = 4;

byte rearSpeed_PIN = 5;
byte rearDirLeft_PIN = 7;
byte rearDirRight_PIN = 8;

void setup() {

  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  // Left
  pinMode(leftSpeed_PIN, OUTPUT); // PWM
  pinMode(leftDirForwards_PIN, OUTPUT); // Forwards
  pinMode(leftDirReverse_PIN, OUTPUT); // Reverse

  // Right
  pinMode(rightSpeed_PIN, OUTPUT); // PWM
  pinMode(rightDirForwards_PIN, OUTPUT); // Forwards
  pinMode(rightDirReverse_PIN, OUTPUT); // Reverse

  // Front
  pinMode(frontSpeed_PIN, OUTPUT); // PWM
  pinMode(frontDirLeft_PIN, OUTPUT); // Left
  pinMode(frontDirRight_PIN, OUTPUT); // Right

  // Back
  pinMode(rearSpeed_PIN, OUTPUT); // PWM
  pinMode(rearDirLeft_PIN, OUTPUT); // Left
  pinMode(rearDirRight_PIN, OUTPUT); // Right
  
  Serial.begin(115200);

}

void loop() {

  // control the left and right motors with the forwards and backwards
  int pwm_x_value = pulseIn(X_PIN, HIGH);
  int adjusted_x_value = pwm_x_value - 1500;
  int x_speed = map(abs(adjusted_x_value), 0, 500, 0, 255);

  if (abs(adjusted_x_value) < deadzone) {
     x_speed = 0;
  }

  

  // Left and right
  int pwm_y_value = pulseIn(Y_PIN, HIGH);
  int adjusted_y_value = pwm_y_value - 1500;  
  int y_speed = map(abs(adjusted_y_value), 0, 500, 0, 255);

  if (abs(adjusted_y_value) < deadzone) {
     y_speed = 0;
  }

  analogWrite(leftSpeed_PIN, x_speed);
  analogWrite(rightSpeed_PIN, x_speed);
  
  analogWrite(frontSpeed_PIN, y_speed);
  analogWrite(rearSpeed_PIN, y_speed);





  // Forwards and backwards
  if (adjusted_x_value > (0+deadzone)) {
    digitalWrite(leftDirForwards_PIN, LOW);
    digitalWrite(leftDirReverse_PIN, HIGH);
    digitalWrite(rightDirForwards_PIN, LOW);
    digitalWrite(rightDirReverse_PIN, HIGH);
 
  } else if (adjusted_x_value < (0-deadzone)) {
    digitalWrite(leftDirForwards_PIN, HIGH);
    digitalWrite(leftDirReverse_PIN, LOW);
    digitalWrite(rightDirForwards_PIN, HIGH);
    digitalWrite(rightDirReverse_PIN, LOW);
    
  } else {
    digitalWrite(leftDirForwards_PIN, LOW);
    digitalWrite(leftDirReverse_PIN, LOW);
    digitalWrite(rightDirForwards_PIN, LOW);
    digitalWrite(rightDirReverse_PIN, LOW);
  }




  // Left and right
  if (adjusted_y_value > (0+deadzone)) {
    digitalWrite(frontDirLeft_PIN, LOW);
    digitalWrite(frontDirRight_PIN, HIGH);
    digitalWrite(rearDirLeft_PIN, LOW);
    digitalWrite(rearDirRight_PIN, HIGH);
 
  } else if (adjusted_y_value < (0-deadzone)) {
    digitalWrite(frontDirLeft_PIN, HIGH);
    digitalWrite(frontDirRight_PIN, LOW);
    digitalWrite(rearDirLeft_PIN, HIGH);
    digitalWrite(rearDirRight_PIN, LOW);
    
  } else {
    digitalWrite(frontDirLeft_PIN, LOW);
    digitalWrite(frontDirRight_PIN, LOW);
    digitalWrite(rearDirLeft_PIN, LOW);
    digitalWrite(rearDirRight_PIN, LOW);
  }



  Serial.println();


}

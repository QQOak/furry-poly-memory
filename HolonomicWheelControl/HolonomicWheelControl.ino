#include "PwmMovementController.h"




byte X_PIN = A1;
byte Y_PIN = A0;
byte R_PIN = A2;
int deadzone = 75;

PwmMovementController mc(X_PIN, Y_PIN, R_PIN, deadzone);

byte frontSpeed_PIN = 11;
byte frontClockwise_PIN = 6;
byte frontAnticlockwise_PIN = 13;

byte rightSpeed_PIN = 3;
byte rightClockwise_PIN = 4;
byte rightAnticlockwise_PIN = 2;

byte rearSpeed_PIN = 5;
byte rearClockwise_PIN = 7;
byte rearAnticlockwise_PIN = 8;

byte leftSpeed_PIN = 9;
byte leftClockwise_PIN = 12;
byte leftAnticlockwise_PIN = 10;




void setup() {

  Serial.begin(115200);
  


  // Front
  pinMode(frontSpeed_PIN, OUTPUT); // PWM
  pinMode(frontClockwise_PIN, OUTPUT); // Left
  pinMode(frontAnticlockwise_PIN, OUTPUT); // Right

  // Right
  pinMode(rightSpeed_PIN, OUTPUT); // PWM
  pinMode(rightClockwise_PIN, OUTPUT); // Forwards
  pinMode(rightAnticlockwise_PIN, OUTPUT); // Reverse

  // Back
  pinMode(rearSpeed_PIN, OUTPUT); // PWM
  pinMode(rearClockwise_PIN, OUTPUT); // Left
  pinMode(rearAnticlockwise_PIN, OUTPUT); // Right

  // Left
  pinMode(leftSpeed_PIN, OUTPUT); // PWM
  pinMode(leftClockwise_PIN, OUTPUT); // Forwards
  pinMode(leftAnticlockwise_PIN, OUTPUT); // Reverse  
  
}

void loop() {

  Movement m = mc.GetMovement();

  int pwm_r_value = m.r;

  int frontSpeed = m.x;
  int rearSpeed = m.x;
  int rightSpeed = m.y;
  int leftSpeed = m.y;
  int rotationSpeed = m.r;

  // Make rotational Adjustments
  frontSpeed += rotationSpeed;
  rightSpeed -= rotationSpeed;
  rearSpeed = 0-(rearSpeed - rotationSpeed);
  leftSpeed = 0-(leftSpeed + rotationSpeed);

  

  // Perform the movement
  // ====================
  setWheelSpeed(frontSpeed, frontSpeed_PIN, frontClockwise_PIN, frontAnticlockwise_PIN);
  setWheelSpeed(rearSpeed, rearSpeed_PIN, rearClockwise_PIN, rearAnticlockwise_PIN);
  setWheelSpeed(rightSpeed, rightSpeed_PIN, rightClockwise_PIN, rightAnticlockwise_PIN);
  setWheelSpeed(leftSpeed, leftSpeed_PIN, leftClockwise_PIN, leftAnticlockwise_PIN);



  Serial.println();


}

void setWheelSpeed(int pwmSpeed, byte pwmPin, byte forwardsPin, byte reversePin) {
  digitalWrite(forwardsPin, (pwmSpeed > 0));
  digitalWrite(reversePin, (pwmSpeed < 0));
  analogWrite(pwmPin, abs(pwmSpeed));  
}

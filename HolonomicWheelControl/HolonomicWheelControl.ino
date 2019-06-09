#include "MovementController.h"

MovementController mv;


byte X_PIN = A1;
byte Y_PIN = A0;
byte R_PIN = A2;
int deadzone = 75;

int frontSpeed = 0;
byte frontSpeed_PIN = 11;
byte frontClockwise_PIN = 6;
byte frontAnticlockwise_PIN = 13;

int rightSpeed = 0;
byte rightSpeed_PIN = 3;
byte rightClockwise_PIN = 4;
byte rightAnticlockwise_PIN = 2;

int rearSpeed = 0;
byte rearSpeed_PIN = 5;
byte rearClockwise_PIN = 7;
byte rearAnticlockwise_PIN = 8;

int leftSpeed = 0;
byte leftSpeed_PIN = 9;
byte leftClockwise_PIN = 12;
byte leftAnticlockwise_PIN = 10;




void setup() {

  Serial.begin(115200);
  
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT); 
  pinMode(R_PIN, INPUT);

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

  int pwm_x_value = pulseIn(X_PIN, HIGH);
  int pwm_y_value = pulseIn(Y_PIN, HIGH);
  int pwm_r_value = pulseIn(R_PIN, HIGH);


  // Calculate Sideways movement
  // ===========================
  int adjusted_x_value = pwm_x_value - 1500;
  int x_speed = 0;
  frontSpeed = 0;
  rearSpeed = 0;

  if ((abs(adjusted_x_value) > deadzone)) {

    x_speed =  map(adjusted_x_value, 0, 500, 0, 255);
    frontSpeed = x_speed;
    rearSpeed = x_speed;

    if((x_speed > 255) || (x_speed < -255)) {
      frontSpeed = 0;
      rearSpeed = 0;
    }

  }
  

  
  // Calculate Forwards and backwards
  // ================================
  int adjusted_y_value = pwm_y_value - 1500;
  int y_speed = 0;
  rightSpeed = 0;
  leftSpeed = 0;
   
  if ((abs(adjusted_y_value) > deadzone)) {

    y_speed =  map(adjusted_y_value, 0, 500, 0, 255);
    rightSpeed = y_speed;
    leftSpeed = y_speed;

    if((y_speed > 255) || (y_speed < -255)) {
      rightSpeed = 0;
      leftSpeed = 0;
    }

  }


  // Adjust for rotation
  // ===================
  int adjusted_r_value = pwm_r_value - 1500;
  int r_speed = 0;
  
  if ((abs(adjusted_r_value) > deadzone)) {
    r_speed =  map(adjusted_r_value, 0, 500, 0, 255);
    if((r_speed > 255) || (r_speed < -255)) {
      r_speed = 0;
    }
  }

  Serial.print("R: ");
  Serial.print(r_speed);
  Serial.print(": X: ");
  Serial.print(x_speed);
  Serial.print(": Y: ");
  Serial.println(y_speed);
 
  frontSpeed += r_speed;
  rightSpeed -= r_speed;
  rearSpeed -= r_speed;
  leftSpeed += r_speed;

  

  // Perform the movement
  // ====================
  setWheelSpeed(frontSpeed, frontSpeed_PIN, frontClockwise_PIN, frontAnticlockwise_PIN);
  setWheelSpeed(0-rearSpeed, rearSpeed_PIN, rearClockwise_PIN, rearAnticlockwise_PIN);
  setWheelSpeed(rightSpeed, rightSpeed_PIN, rightClockwise_PIN, rightAnticlockwise_PIN);
  setWheelSpeed(0-leftSpeed, leftSpeed_PIN, leftClockwise_PIN, leftAnticlockwise_PIN);



  Serial.println();


}

void setWheelSpeed(int pwmSpeed, byte pwmPin, byte forwardsPin, byte reversePin) {
  digitalWrite(forwardsPin, (pwmSpeed > 0));
  digitalWrite(reversePin, (pwmSpeed < 0));
  analogWrite(pwmPin, abs(pwmSpeed));  
}

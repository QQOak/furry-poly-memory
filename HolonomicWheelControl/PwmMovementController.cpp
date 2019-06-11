#include "PwmMovementController.h"

PwmMovementController::PwmMovementController(byte xPin, byte yPin, byte rPin, int deadzone)
  :X_PIN(xPin), Y_PIN(yPin), R_PIN(rPin), DEADZONE(deadzone)
{
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT); 
  pinMode(R_PIN, INPUT);
}


Movement PwmMovementController::GetMovement()
{

  Serial.println("Got from PWM movement controller");
  
  int pwm_x_value = pulseIn(X_PIN, HIGH);
  int pwm_y_value = pulseIn(Y_PIN, HIGH);
  int pwm_r_value = pulseIn(R_PIN, HIGH);

  // x
  int x_speed = 0;
  int adjusted_x_value = pwm_x_value - 1500;

  if ((abs(adjusted_x_value) > DEADZONE)) {
    x_speed =  map(adjusted_x_value, 0, 500, 0, 255);
    if((x_speed > 255) || (x_speed < -255)) {
      x_speed = 0;
    }
  }

  // y
  int y_speed = 0;
  int adjusted_y_value = pwm_y_value - 1500;

  if ((abs(adjusted_y_value) > DEADZONE)) {
    y_speed =  map(adjusted_y_value, 0, 500, 0, 255);
    if((y_speed > 255) || (y_speed < -255)) {
      y_speed = 0;
    }
  }

  // r
  int r_speed = 0;
  int adjusted_r_value = pwm_r_value - 1500;
  
  if ((abs(adjusted_r_value) > DEADZONE)) {
    r_speed =  map(adjusted_r_value, 0, 500, 0, 255);
    if((r_speed > 255) || (r_speed < -255)) {
      r_speed = 0;
    }
  }

  return Movement(x_speed, y_speed, r_speed);
}

#ifndef PWMMovementController_h
#define PWMMovementController_h

#include <Arduino.h>
#ifndef Movement_h
  #define Movement_h
  #include "Movement.h"
  #include "MovementController.h"
#endif

#ifndef MovementController_h
  #define MovementController_h
  #include "MovementController.h"
#endif

class PwmMovementController : public MovementController
{
  
  public:
    PwmMovementController(byte xPin, byte yPin, byte rPin, int Deadzone);
    Movement GetMovement();
    
  private:
    byte X_PIN;
    byte Y_PIN;
    byte R_PIN;
    int DEADZONE = 0;
    
};

#endif      

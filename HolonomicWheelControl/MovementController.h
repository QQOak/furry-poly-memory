#ifndef MovementController_h
#define MovementController_h

#include <Arduino.h>
#ifndef Movement_h
#define Movement_h
  #include "Movement.h"
#endif

class MovementController
{
  
  public:
    virtual Movement GetMovement();
    
  private:
  
};

#endif

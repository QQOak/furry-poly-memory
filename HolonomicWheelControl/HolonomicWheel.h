#ifndef HolonomicWheel_h
#define HolonomicWheel_h

class HolonomicWheel
{

  public:

    HolonomicWheel();
    HolonomicWheel(const int angle);
    
    

    Move(const int x, const int y, const int r);

  private:
    int _angle;
};

#endif

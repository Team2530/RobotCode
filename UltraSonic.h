#ifndef UltraSonic_H
#define UltraSonic_H

#include "WPILib.h"

class UltraSonic
{
public:
	UltraSonic () {}
    // UPDATE: We totally needed this constructor
    //UltraSonic(uint32_t port);
    virtual float GetDistanceIN() = 0; // inches
    enum { N = 4 };
    
    
};

#endif  //Ultrasonic

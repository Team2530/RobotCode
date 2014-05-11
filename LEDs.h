#include "WPILib.h"

#ifndef _LED_H
#define _LED_H
class LEDs {
	DigitalOutput *dig2;  //Not sure if input or output
	DigitalOutput *dig3;
	DigitalOutput *dig4;
	DigitalOutput *dig5;
	DigitalOutput *dig6;
	
public:
	LEDs();
	void Disabled();
	void AutoDriving();
	void TeleDriving();
	void Fire();
	void SoftFire();
	void HumanLoad();
	
};

#endif

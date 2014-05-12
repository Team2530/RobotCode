#include "WPILib.h"

#ifndef _LED_H
#define _LED_H
class LEDs {
	bool load;
	DigitalOutput *dig2;  //Not sure if input or output
	DigitalOutput *dig3;
	DigitalOutput *dig4;
	DigitalOutput *dig5;
	DigitalOutput *dig6;
	
public:
	LEDs();
	void Disabled();
	bool GetLoading();
	void SetLoading(bool loading);
	void AutoDriving();
	void TeleDriving();
	void ArmUp();
	void ArmDown();
	void Fire();
	void SoftFire();
	void HumanLoad();
	
};

#endif

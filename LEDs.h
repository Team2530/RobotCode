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
	void TeleDriving(bool loading);
	void ArmUp(bool loading);
	void ArmDown(bool loading);
	void Fire(bool loading);
	void SoftFire(bool loading);
	void HumanLoad();
	
};

#endif

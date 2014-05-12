#include "WPILib.h"
#include "LEDs.h"
#ifndef _PNEUMATICS_H
#define _PNEUMATICS_H
class Pneumatics {
	LEDs *robotLEDs;
	DoubleSolenoid *shooterSolenoid1;  //middle cylinder
	DoubleSolenoid *shooterSolenoid2;
	DoubleSolenoid *shooterSolenoid3;
	Joystick *joystick;  //xbox controller

public:
	void Shooter();
	Pneumatics();
	void FireShooter();
	void RetractCylinder();
	void FireMiddleCylinder();
};
#endif

#include "WPILib.h"
#include "LEDs.h"

#ifndef _ARM_H
#define _ARM_H
class Arm {
	Jaguar *raiseArm;  //Motors to control motion of the arm
	Joystick *xboxController;
	Joystick *joystick;
	LEDs *robotLEDs;
	bool automatic;  //controls automatic mode
public:
	Arm();
	void RaiseArm(float value);
	void LowerArm(float value);
	void OperateArm();
	void AutoArm();
	void StopArm();
};
#endif

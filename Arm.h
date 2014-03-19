#include "WPILib.h"
#ifndef _ARM_H
#define _ARM_H
class Arm {
	Jaguar *raiseArm;  //Motors to control motion of the arm
	Joystick *xboxController;
	Joystick *joystick;
	bool automatic;  //controls automatic mode
public:
	Arm();
	void RaiseArm();
	void LowerArm();
	void OperateArm();
	void AutoArm();
	void StopArm();
};
#endif

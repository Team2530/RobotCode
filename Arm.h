#include "WPILib.h"
class Arm {
	Jaguar *raiseArm;  //Motors to control motion of the arm
	Joystick *xboxController;
	Joystick *joystick;
	DigitalInput *top_limit_switch;
	DigitalInput *bottom_limit_switch;
public:
	Arm();
	void RaiseArm();
	void LowerArm();
	void OperateArm();
};

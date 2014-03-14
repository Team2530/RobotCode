#include "WPILib.h"
class Arm {
	Jaguar *raiseArm;  //Motors to control motion of the arm
	Joystick *xboxController;
	Joystick *joystick;
public:
	Arm();
	void RaiseArm();
	void LowerArm();
	void OperateArm();
};

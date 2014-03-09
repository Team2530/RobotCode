#include "WPILib.h"



class Arm {

	Jaguar *raiseArm;  //Motors to control motion of the arm

	Joystick *xboxController;

public:

	Arm();

	void RaiseArm();

	void LowerArm();

	void OperateArm();

};

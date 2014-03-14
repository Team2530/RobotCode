#include "Arm.h"
#include "WPILib.h"
Arm::Arm() {
	raiseArm = new Jaguar(9);  //Creat jag arm motor
	xboxController = new Joystick(2);
	joystick = new Joystick(1);
	bool auto = false;
}
void Arm::RaiseArm() {
		if ((xboxController->GetRawAxis(5) >= 0.5) || (joystick->GetRawAxis(6) >= 0.5))
			raiseArm->SetSpeed(1);
		else 
			raiseArm->SetSpeed(0);
}
void Arm::LowerArm() {
		if ((xboxController->GetRawAxis(5) <= -0.5) || (joystick->GetRawAxis(6) <= -0.5))
			raiseArm->SetSpeed(-1);
		else
			raiseArm->SetSpeed(0);
}
//For automatically lowering and raising the arm all the way to the top/bottom on the press of a button

void Arm::AutoArm() {
	
	if (xboxController->GetRawButton(3))
		raiseArm->SetSpeed(1);
		auto = true;
	if (xboxController->GetRawButton(4))
		raiseArm->SetSpeed(-1);
		auto = true;
	else auto = false;
}
}

void Arm::OperateArm() {
	AutoArm();
	if ((xboxController->GetRawAxis(5) >= 0.5) || (joystick->GetRawAxis(6) >= 0.5))
		RaiseArm();
	else if ((xboxController->GetRawAxis(5) <= -0.5) || (joystick->GetRawAxis(6) <= -0.5))
		LowerArm();
	else if (!auto)
		raiseArm->SetSpeed(0);
}


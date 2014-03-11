#include "Arm.h"
#include "WPILib.h"
Arm::Arm() {

	top_limit_switch = new DigitalInput(1);
	bottom_limit_switch = new DigitalInput(2);
	
	raiseArm = new Jaguar(9);  //Creat jag arm motor
	xboxController = new Joystick(2);
	joystick = new Joystick(1);
}
void Arm::RaiseArm() {

	if (top_limit_switch->Get())
	{
		raiseArm->SetSpeed(0);
	}
	else
	{
		raiseArm->SetSpeed(1);
	}
}
void Arm::LowerArm() {
	
	if (bottom_limit_switch->Get())
	{
		raiseArm->SetSpeed(0);
	}
	else
	{
		raiseArm->SetSpeed(-1);
	}
}
void Arm::OperateArm() {
	if (xboxController->GetRawAxis(3) <= -0.5) {
		LowerArm();
	}
	if (xboxController->GetRawAxis(3) >= 0.5 {
		RaiseArm();
	}
}


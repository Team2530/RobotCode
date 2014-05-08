#include "Arm.h"
#include "WPILib.h"
#include <Math.h>
Arm::Arm() {
	raiseArm = new Jaguar(9);  //Creat jag arm motor
	xboxController = new Joystick(2);
	joystick = new Joystick(1);
	automatic = false;
}
void Arm::RaiseArm(float value) {
	automatic = false;
	raiseArm->SetSpeed(value);
}
void Arm::LowerArm(float value) {
	automatic = false;
	raiseArm->SetSpeed(-value);
}
//Automatically lowers and raises the arm all the way to the top/bottom on the press of a button
void Arm::AutoArm() {

	if (xboxController->GetRawButton(3)) {
		raiseArm->SetSpeed(1);
		automatic = true;
	}
	else if (xboxController->GetRawButton(4)) {
		raiseArm->SetSpeed(-1);
		automatic = true;
	}
}

//Controls motion of arm
void Arm::OperateArm() {
	AutoArm();
	//Controlled by right analog stick
	if (xboxController->GetRawAxis(5) >= 0.2 || xboxController->GetRawAxis(5) <= -0.2) {  //Absolute value of controller stick
		RaiseArm(xboxController->GetRawAxis(5));
	}
	
	//Controlled by hat switch on top of joystick
	else if (joystick->GetRawAxis(6) > 0.0)
		RaiseArm(0.9);
	else if (joystick->GetRawAxis(6) < -0.0)
		LowerArm(0.9);
	else if (!automatic)
		StopArm();
}

void Arm::StopArm() {
	raiseArm->SetSpeed(0);
}


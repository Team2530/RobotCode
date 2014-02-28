#include "WPILib.h"
#include "Pneumatics.h"

void Pneumatics::FireShooter(){
	shooterSolenoid1->Set(DoubleSolenoid::kForward);
	//shooterSolenoid2->Set(DoubleSolenoid.kForward);
	//shooterSolenoid3->Set(DoubleSolenoid::kForward);
	SmartDashboard::PutString("Button 6", "PRESSED ");
}

void Pneumatics::RetractCylinder(){
	shooterSolenoid1->Set(DoubleSolenoid::kReverse);
	//shooterSolenoid2->Set(DoubleSolenoid::kOff);
	//shooterSolenoid3->Set(DoubleSolenoid::kOff);
	SmartDashboard::PutString("Button 6", "NOT PRESSED");
}
void Pneumatics::Shooter(){


	if (joystick->GetRawButton(6)){
		FireShooter();
	}
	else{
		RetractCylinder();
		}
}
Pneumatics::Pneumatics (){
	shooterSolenoid1 = new DoubleSolenoid (2, 1);
	joystick = new Joystick(1);
}

#include "WPILib.h"
#include "Pneumatics.h"

void Pneumatics::FireShooter(){
	shooterSolenoid1->Set(DoubleSolenoid::kReverse);
	shooterSolenoid2->Set(DoubleSolenoid::kReverse);
	shooterSolenoid3->Set(DoubleSolenoid::kReverse);
}

void Pneumatics::RetractCylinder(){
	shooterSolenoid1->Set(DoubleSolenoid::kForward);
	shooterSolenoid2->Set(DoubleSolenoid::kForward);
	shooterSolenoid3->Set(DoubleSolenoid::kForward);
	

}
void Pneumatics::Shooter(){


	if (joystick->GetRawButton(5)){
		FireShooter();
	}

	if (joystick->GetRawButton(6)){
		FireMiddleCylinder();
	}
	else {
		RetractCylinder();
	}
}
void Pneumatics::FireMiddleCylinder(){
		shooterSolenoid1->Set(DoubleSolenoid::kReverse);
	}

Pneumatics::Pneumatics (){
	shooterSolenoid1 = new DoubleSolenoid (1, 2);
	shooterSolenoid2 = new DoubleSolenoid (3, 4);
	shooterSolenoid3 = new DoubleSolenoid (5, 6);
	joystick = new Joystick(2);
}

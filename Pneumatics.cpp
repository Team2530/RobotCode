#include "WPILib.h"
#include "Pneumatics.h"

//Shoot full -- shoots all 3 cylinders
void Pneumatics::FireShooter(){
	shooterSolenoid1->Set(DoubleSolenoid::kReverse);
	shooterSolenoid2->Set(DoubleSolenoid::kReverse);
	shooterSolenoid3->Set(DoubleSolenoid::kReverse);
}

//Pass shoot -- shoots only middle cylinder
void Pneumatics::FireMiddleCylinder(){
		shooterSolenoid1->Set(DoubleSolenoid::kReverse);
	}
//Retracts all the cylinders
void Pneumatics::RetractCylinder(){
	shooterSolenoid1->Set(DoubleSolenoid::kForward);
	shooterSolenoid2->Set(DoubleSolenoid::kForward);
	shooterSolenoid3->Set(DoubleSolenoid::kForward);
	

}
//Operat the shooter mechanism
void Pneumatics::Shooter(){
	if (joystick->GetRawAxis(3) <= -0.1) {
		FireShooter();
	}
	else if (joystick->GetRawAxis(3) >= 0.1) {
		FireMiddleCylinder();
	}
	else {
		RetractCylinder();
	}
}

Pneumatics::Pneumatics (){
	shooterSolenoid1 = new DoubleSolenoid (1, 6); //MIDDLE solenoid
	shooterSolenoid2 = new DoubleSolenoid (2, 5);
	shooterSolenoid3 = new DoubleSolenoid (3, 4);
	joystick = new Joystick(2);  //xbox controller
}

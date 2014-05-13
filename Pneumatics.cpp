#include "WPILib.h"
#include "Pneumatics.h"

//Shoot full -- shoots all 3 cylinders
void Pneumatics::FireShooter(){
	robotLEDs->Fire();
	shooterSolenoid1->Set(DoubleSolenoid::kReverse);
	shooterSolenoid2->Set(DoubleSolenoid::kReverse);
	shooterSolenoid3->Set(DoubleSolenoid::kReverse);
}

//Pass shoot -- shoots only middle cylinder
void Pneumatics::FireMiddleCylinder(){
	robotLEDs->SoftFire();
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

Pneumatics::Pneumatics (LEDs *myLEDs){
	shooterSolenoid1 = new DoubleSolenoid (7, 1); //MIDDLE solenoid
	shooterSolenoid2 = new DoubleSolenoid (2, 6);
	shooterSolenoid3 = new DoubleSolenoid (3, 4);
	joystick = new Joystick(2);  //xbox controller
	robotLEDs = myLEDs;
}

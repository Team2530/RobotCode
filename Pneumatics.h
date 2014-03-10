#include "WPILib.h"
class Pneumatics {


	DoubleSolenoid *shooterSolenoid1;
	//DoubleSolenoid *shooterSolenoid2;
	//DoubleSolenoid *shooterSolenoid3;
	Joystick *joystick;

public:
	void Shooter();
	Pneumatics();
	void FireShooter();
	void RetractCylinder();
	void FireMiddleCylinder();

};

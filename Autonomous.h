#include "WPILib.h"
#include "MecanumDrive.h"
#include "Pneumatics.h"

class Autonomous {
	MecanumDrive *myDrive;
	Gyro *myGyro;
	Pneumatics *pneumatics;
	Arm *robotArm;
	float x;  //Loop iterator scaled down
	float angle;  //Variable for gyro output
		
public:
	Autonomous();
	void Autonomous::OneBall();
	void Autonomous::TwoBall();
	void Autonomous::NoBall();
	void Autonomous::Drive();
};

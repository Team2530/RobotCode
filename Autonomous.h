#include "WPILib.h"
#include "MecanumDrive.h"
#include "Pneumatics.h"
#include "KinectStick.h"
#include "Arm.h"


class AutonomousMode {
	MecanumDrive *myDrive;
	Gyro *myGyro;
	Pneumatics *pneumatics;
	Arm *robotArm;
	float x;  //Loop iterator scaled down
	float angle;  //Variable for gyro output
	Kinect *kinect;  //Kinect object
	KinectStick *leftArm; 
	KinectStick *rightArm;
		
public:
	AutonomousMode();
	void AutonomousMode::OneBall(bool isRight);
	void AutonomousMode::TwoBall();
	void AutonomousMode::Drive();
};

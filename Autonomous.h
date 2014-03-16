#include "WPILib.h"
#include "MecanumDrive.h"
#include "Pneumatics.h"
#include "KinectStick.h"


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
	void AutonomousMode::OneBall();
	void AutonomousMode::TwoBall();
	void AutonomousMode::NoBall();
	void AutonomousMode::Drive();
};

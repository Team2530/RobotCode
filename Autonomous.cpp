#include "WPILib.h"
#include "Autonomous.h"


void AutonomousMode::OneBall() {
		Drive();
		pneumatics->FireShooter();
		Wait(1);
		pneumatics->RetractCylinder();
}

void AutonomousMode::TwoBall() {
		robotArm->RaiseArm(0.9);
		Wait(.2);
		robotArm->LowerArm(0.9);
		Drive();
}
//Drive forward
void AutonomousMode::Drive() {
	myGyro->Reset();  //Reset gyro
	for (int i = 0; i <= 10; i++) {  //Spool up motors
		myGyro->GetAngle();
		x = i;
		x *= .1;
		myDrive->Drive_RobotOriented(x,0,0.02);
		Wait(.25); 
	}
	for (int i = 10; i >= 0; i--) {  //Spool down motors
		myGyro->GetAngle();
		x = i;
		x *= .1;
		myDrive->Drive_RobotOriented(x,0,0.02); 
		Wait(.02);
	}
}

AutonomousMode::AutonomousMode(MecanumDrive *drive, Gyro *gyro, Pneumatics *pneumatic, Arm *myArm) {
	myDrive = drive;
	myGyro = gyro;
	pneumatics = pneumatic;
	robotArm = myArm;
	leftArm = new KinectStick(1);
	rightArm = new KinectStick(2); 
}

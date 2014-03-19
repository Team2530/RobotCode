#include "WPILib.h"
#include "Autonomous.h"


void AutonomousMode::OneBall(bool isRight) {
	//Kinect code -- could be any of these 3 scenarios
#if 0
	if (rightArm->GetTrigger() || rightArm->GetTop()) {
		robotArm->RaiseArm();}

	if (rightArm->GetY() || rightArm->GetX()) {
		robotArm->RaiseArm();}

	if (rightArm->GetTwist() == 0){
		robotArm->RaiseArm();}
#endif
	if (isRight && rightArm->GetTrigger()) {  //Kinect stuff
		Drive();
		pneumatics->FireShooter();
		Wait(.1);
		pneumatics->RetractCylinder();
	}
	else if (isRight && !rightArm->GetTrigger()) {
		Drive();
		Wait(5.0);
		pneumatics->FireShooter();
		Wait(1);
		pneumatics->RetractCylinder();
	}
	else if (! isRight && rightArm->GetTrigger()){
		Drive();
		pneumatics->FireShooter();
		Wait(.1);
		pneumatics->RetractCylinder();
	}
	else {
		Drive();
		Wait(5.0);
		pneumatics->FireShooter();
		Wait(.1);
		pneumatics->RetractCylinder();
	}
}

void AutonomousMode::TwoBall() {
	if (true) { //Kinect stuff
		robotArm->RaiseArm();
		Wait(.2);
		robotArm->LowerArm();
		Drive();
	}
	else {
		Wait(5.0);
		robotArm->RaiseArm();
		Wait(.2);
		robotArm->LowerArm();
		Drive();
	}
}
//Drive forward
void AutonomousMode::Drive() {
	myGyro->Reset();  //Reset gyro
	for (int i = 0; i <= 10; i++) {  //Spool up motors
		myGyro->GetAngle();
		x = i;
		x *= .1;
		myDrive->Drive_FieldOriented(x,0,0,angle);
		Wait(.1);
	}
	for (int i = 10; i >= 0; i--) {  //Spool down motors
		myGyro->GetAngle();
		x = i;
		x *= .1;
		myDrive->Drive_FieldOriented(x,0,0,angle);
		Wait(.1);
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

#include "WPILib.h"
#include "Autonomous.h"

//Arm will probably be down
void Autonomous::NoBall() {
	Drive();
}

void Autonomous::OneBall() {
	if (true) { //Kinect stuff
		Drive();
		pneumatics->FireShooter();
		Wait(1);
		pneumatics->RetractCylinder();
	}
	else {
		Wait(5.0);
		Drive();
		pneumatics->FireShooter();
		Wait(1);
		pneumatics->RetractCylinder();
	}
}

void Autonomous::TwoBall() {
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

void Autonomous::Drive() {
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

Autonomous::Autonomous() {
	myDrive = new MecanumDrive();
	myGyro = new Gyro(1);
	pneumatics = new Pneumatics();
	robotArm = new Arm();
}

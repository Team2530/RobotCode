#include "KinectStick.h"

	Kinect *kinect;  //Kinect object
	KinectStick *leftArm; 
	KinectStick *rightArm;
		leftArm = new KinectStick (1); 
		rightArm = new KinectStick (2); 
		leftArm = new KinectStick(1);
		rightArm = new KinectStick(2); 

while (IsAutonomous()) {
			if (rightArm->GetTrigger() || rightArm->GetTop()) {
				robotArm->RaiseArm();}

			if (rightArm->GetY() || rightArm->GetX()) {
				robotArm->RaiseArm();}
			
			if (rightArm->GetTwist() == 0){
				robotArm->RaiseArm();}
			else {
				Wait(.05);}

#include "WPILib.h"
#include "MecanumDrive.h"

//Constructor
MecanumDrive::MecanumDrive() {

	//Makes Victor motors - IMPORTANT, OTHERWISE ROBOTDRIVE MAKES JAGUAR MOTORS
	vic4 = new Victor(4); 
	vic6 = new Victor(6);
	vic3 = new Victor(3);
	vic5 = new Victor(5);

	//Define joystick
	joystick = new Joystick(1);

	myRobot = new RobotDrive(vic5,vic3,vic6,vic4);  //FrontLeft, RearLeft, FrontRight, RearRight
	myRobot->SetExpiration(0.1);  //Update the motors at least every 100ms.

	//Invert motors 5 and 3
	myRobot->SetInvertedMotor(RobotDrive::kFrontLeftMotor,true);
	myRobot->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);

};

//Tell the robot to drive with given values
//Multiply values with 'throttle' which is power value, minimum being 20%
//'Down' position is 100% power, 'Up' position is 20% power on X3D joystick
void MecanumDrive::Drive_FieldOriented(float mag, float dir, float twist, float angle) {	
	dir -= angle;  //Drive with Gyro correction
	myRobot->MecanumDrive_Polar(mag,dir,twist);
};

void MecanumDrive::Drive_RobotOriented(float mag, float dir, float twist) {
	myRobot->MecanumDrive_Polar(mag,dir,twist);
};

void MecanumDrive::GetJoystickValues(float &magnitude, float &direction, float &twist, float &throttle) {
	//Get all the values that the joystick is sending
	magnitude = joystick->GetMagnitude(); 
	direction =  joystick->GetDirectionDegrees();
	twist = joystick->GetThrottle();  //These are reversed for some reason on the X3D Joystick
	throttle = joystick->GetTwist();  //Throttle<>Twist

	//Set Deadzones
	if (magnitude < 0.030) {
		magnitude = 0;
	}
	if (twist < 0.2 && twist > -0.2) {
		twist = 0;
	}

	//Perform maths to make range of throttle between .2 and 1 (rather than -1 and 1)
	throttle += 1;
	throttle *= 0.4;
	throttle += .2;
};

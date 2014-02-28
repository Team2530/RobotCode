#include "WPILib.h"
#include "EV4sonic.h"
#include "Pneumatics.h"
#include "MecanumDrive.h"
#include <math.h>
#include "CameraServo.h"

/*
 * This is the final code for Team 2530's robot, Humperdinck.
 * Contributors:
 * 
 * 
 */
class Team2530 : public SimpleRobot
{
	Joystick *joystick;  //Joystick for driver's use
	DriverStation *ds;	// driver station object
	UltraSonic *sonic;  //Sonic sensor
	Gyro *myGyro;  //Gyro
	Pneumatics *pneumatics;  //Shooter/claw pneumatics object
	Relay * m_relay;  //Compressor Relay
	CameraServo * camera_servo;  //Servo to move the camera
	MecanumDrive *myDrive;  //MecanumDrive object

	enum							// Driver Station jumpers to control program operation
	{ ARCADE_MODE = 1,				// Tank/Arcade jumper is on DS Input 1 (Jumper present is arcade)
		ENABLE_AUTONOMOUS = 2,		// Autonomous/Teleop jumper is on DS Input 2 (Jumper present is autonomous)
	} jumpers;	                            

public:
	//Constructor for this robot subclass.
	Team2530()
	{
		ds = DriverStation::GetInstance();  //Create driver's station

		joystick = new Joystick(1);  //Create driver joystick (first slot in DS)
		myGyro = new Gyro(1);  //Create Gyro on port 1
		sonic = new EV4Sonic(2);  //Create Sonic senor on port 2

		myDrive = new MecanumDrive();  //Create a MecanumDrive (from MecanumDrive.h)

		m_relay = new Relay (1, Relay::kForward);	//creates the compressor

		camera_servo = new CameraServo(10);
		pneumatics = new Pneumatics();

	}

	/**
	 * Drive left & right motors for 2 seconds, enabled by a jumper (jumper
	 * must be in for autonomous to operate).
	 */
	void Autonomous()
	{
		float x;
		float range;
		while (IsAutonomous()) {
			range = sonic->GetDistanceIN();
			while (range >= 180) {
				for (int i = 0; i <= 10; i++) {  //Spool up motors
					range = sonic->GetDistanceIN();
					x = i;
					x *= .1;
					myDrive->Drive_RobotOriented(x,0,0);
					Wait(.1);
				}
				for (int i = 10; i >= 0; i--) {  //Spool down motors
					range = sonic->GetDistanceIN();
					x = i;
					x *= .1;
					myDrive->Drive_RobotOriented(x,0,0);
					Wait(.1);
				}
			}
		}
	}

	/*
	 * Operates the Team 2530 robot Tele-Op mode
	 * Contains code for MecanumDrive, including joystick deadzones and power level control
	 */
	void OperatorControl()
	{
		//Engage the compressor
		m_relay->Set(Relay::kForward);
		
		myGyro->Reset();

		//Define all the variables that the joystick needs
		float magnitude;
		float direction;
		float twist;
		float throttle;

		//Angle of Gyro
		float angle;
		int anglei;  //User viewing
		//If robot is in field-oriented or robot-oriented
		bool isFieldOriented = true;  //Start out in field-oriented mode

		//Variables for calculating average values of sensors
		int dataSize = 10;
		float distance[dataSize];
		float avg;
		int avgi;  //User viewing
		int loopCount = 0;

		//Tele-Op Mode
		while (IsOperatorControl())
		{
			//ULTRASONIC things~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//loopCount resets the data size back to 0
			loopCount++;
			if(loopCount >= dataSize){
				loopCount = 0;}
			distance[loopCount] = sonic->GetDistanceIN();

			int i;
			// Calculates average of Sensors
			for (i = dataSize - 1; i >= 0; i--){ 
				distance[i] = sonic->GetDistanceIN();
			}
			avg = 0;
			for (int i = 0; i < dataSize; i++) {
				avg += distance[i];
			}
			// Returns the average distance 
			avg = avg / dataSize;

			//GYRO/FIELD-ORIENTED Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			angle = myGyro->GetAngle();  //Get the angle of the gyro

			if (joystick->GetRawButton(11)) {  //Disable Field Oriented
				isFieldOriented = false;
			}
			if (joystick->GetRawButton(12)) {  //Enable Field Oriented
				isFieldOriented = true;
			}
			if (joystick->GetRawButton(8)) {  //Reset the Gyro
				myGyro->Reset();
			}

			//DRIVE Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//Get joystick values
			myDrive->GetJoystickValues(magnitude, direction, twist, throttle);
			//Field Oriented Drive
			if (isFieldOriented) {
				myDrive->Drive_FieldOriented(throttle * magnitude, direction, throttle * twist, angle);
			}
			//Robot Oriented Drive
			else {
				myDrive->Drive_RobotOriented(throttle * magnitude, direction, throttle * twist);
			}

			//Make Gyro an integer for user viewing
			anglei = static_cast<int>(angle);
			avgi = static_cast<int>(avg);

			//Output all interesting values to the SmartDashboard
			SmartDashboard::PutNumber("Range:",avgi);
			SmartDashboard::PutNumber("Power Level",throttle);
			SmartDashboard::PutNumber("Gyro:",anglei);
			SmartDashboard::PutBoolean("Field Oriented:", isFieldOriented);

			//Engage the shooter mechanism
			pneumatics->Shooter();

			//Turns the camera			
			camera_servo->turnCamera()

		}
	}
};

START_ROBOT_CLASS(Team2530);

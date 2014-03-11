#include "WPILib.h"
#include "EV4sonic.h"
#include "Pneumatics.h"
#include "MecanumDrive.h"
#include <math.h>
#include "CameraServo.h"
#include "Arm.h"

/*
 * This is the final code for Team 2530's robot, Humperdinck.
 * Contributors: ADD YOUR NAME HERE
 * 	MENTOR: Tim Torzweski (Dad)
 *      Bridger Herman
 *      Alvin Faisal
 *      Peter Torzweski
 *      Isaac Gullickson
 *      
 * 
 * 
 */
class Team2530 : public SimpleRobot {
	Joystick *joystick;  //Joystick for driver's use
	DriverStation *ds;	// driver station object
	UltraSonic *sonic;  //Sonic sensor
	Gyro *myGyro;  //Gyro
	Pneumatics *pneumatics;  //Shooter/claw pneumatics object
	Compressor *m_compressor;  //Compressor Relay
	CameraServo * camera_servo;  //Servo to move the camera
	MecanumDrive *myDrive;  //MecanumDrive object
	Arm *robotArm;  //Arm object


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

		m_compressor = new Compressor (1, 1);	//creates the compressor

		camera_servo = new CameraServo(10);
		pneumatics = new Pneumatics();

		robotArm = new Arm();  //Arm for lifting the ball

	}

	/*
	 * Spool motors up and down, then fire the shooter. Hopefully don't run into driver stations at other end of field.
	 * ADD KINECT STUFF HERE
	 * as well as a 5 second wait for if kinct stuff is not true
	 */
	void Autonomous()
	{
		float x;  //Loop iterator scaled down
		float angle;  //Variable for gyro output
		myGyro->Reset();  //Reset gyro
		
		while (IsAutonomous()) {
			for (int i = 0; i <= 10; i++) {  //Spool up motors
				x = i;
				x *= .1;
				myDrive->Drive_FieldOriented(x,0,0,angle);
				Wait(.1);
			}
			for (int i = 10; i >= 0; i--) {  //Spool down motors
				x = i;
				x *= .1;
				myDrive->Drive_FieldOriented(x,0,0,angle);
				Wait(.1);
			}
		}
	}


	/*
	 * Operates the Team 2530 robot Tele-Op mode
	 * Contains: 
	 * MecanumDrive, including joystick deadzones, power level control, field oriented
	 * Compressor engage
	 * Pneumatics systems
	 * Camera servo
	 * Arm operation
	 */
	void OperatorControl() {
		//Engage the compressor
		//m_compressor->Start();

		//Reset the gyro
		myGyro->Reset();

		//Define all the variables that the joystick needs
		float magnitude;
		float direction;
		float twist;
		float throttle;

		//Angle of Gyro
		float angle;
		int anglei;  //User viewing for gyro readout
		//If robot is in field-oriented or robot-oriented
		bool isFieldOriented = true;  //Start out in field-oriented mode

		//Variables for calculating average values of sensors
		int dataSize = 10;
		float distance[dataSize];
		float avg;
		int avgi;  //User viewing for distance sensor
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

			if (joystick->GetRawButton(4)) {  //Disable Field Oriented
				isFieldOriented = false;
			}
			if (joystick->GetRawButton(6)) {  //Enable Field Oriented
				isFieldOriented = true;
			}
			if (joystick->GetRawButton(2)) {  //Reset the Gyro
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

			//Shooter actions
			pneumatics->Shooter();

			//Turns the camera			
			camera_servo->turnCamera();

			//Arm actions
			//robotArm->OperateArm();
		}
	}
};

START_ROBOT_CLASS(Team2530);

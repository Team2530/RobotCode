#include "WPILib.h"
#include "Pneumatics.h"
#include "MecanumDrive.h"
#include <math.h>
#include "Arm.h"
#include "KinectStick.h"
#include "Autonomous.h"
#include "LEDs.h"

/*
 * This is the final code for Team 2530's robot, Humperdinck.
 * Contributors: ADD YOUR NAME HERE
 * 	MENTOR: Tim Torzewski (Dad)
 *      Bridger Herman
 *      Alvin Faisal
 *      Peter Torzewski
 *      Isaac Gullickson
 *      
 * 
 * 
 */
class Team2530 : public SimpleRobot {
	Joystick *joystick;  //Joystick for driver's use
	Joystick *xboxController;  //Xbox Controller for Operator use
	DriverStation *ds;	// driver station object
	Gyro *myGyro;  //Gyro
	Pneumatics *pneumatics;  //Shooter/claw pneumatics object

	Compressor *m_compressor;  //Compressor Relay	
	
	MecanumDrive *myDrive;  //MecanumDrive object
	Arm *robotArm;  //Arm object
	AutonomousMode *autonomous;
	
	LEDs *robotLEDs;  //LED object

	enum							// Driver Station jumpers to control program operation
	{ ARCADE_MODE = 1,				// Tank/Arcade jumper is on DS Input 1 (Jumper present is arcade)
		ENABLE_AUTONOMOUS = 2,		// Autonomous/Teleop jumper is on DS Input 2 (Jumper present is autonomous)
	} jumpers;	                            

public:
	//Constructor for this robot subclass.
	Team2530() {
		
		ds = DriverStation::GetInstance();  //Create driver's station

		robotLEDs = new LEDs();		
		
		joystick = new Joystick(1);  //Create driver joystick (first slot in DS)
		xboxController = new Joystick(2);  //Xbox Controller on second slot in DS
		myGyro = new Gyro(1);  //Create Gyro on port 1 (Analog)

		myDrive = new MecanumDrive(robotLEDs);  //Create a MecanumDrive (from MecanumDrive.h)

		m_compressor = new Compressor (1, 1);	//creates the compressor  (Spike on Relay 1, Pressure Switch on Digital I/O 1)

		pneumatics = new Pneumatics(robotLEDs);  //Object for shooting arm pneumatics

		robotArm = new Arm(robotLEDs);  //Arm for lifting the ball
		autonomous = new AutonomousMode(myDrive, myGyro, pneumatics, robotArm);
		
	}

	/*
	 * Spool motors up and down, then fire the shooter. Hopefully don't run into driver stations at other end of field.
	 * ADD KINECT STUFF HERE
	 * as well as a 5 second wait for if kinect stuff is not true
	 */
	
	void Autonomous() {
		if (ds->GetDigitalIn(1)) {
			robotLEDs->AutoDriving();
			autonomous->OneBall();
			robotLEDs->Fire();
		}
		else if (ds->GetDigitalIn(2)) {
			robotLEDs->AutoDriving();
			autonomous->TwoBall();
			robotLEDs->Fire();
		}
		else {
			robotLEDs->AutoDriving();
			autonomous->OneBall();
			robotLEDs->Fire();
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
		//Engage the compressor -- needs relay on 1 and pressure switch on I/O port 1
		m_compressor->Start();

		//Reset the gyro
		myGyro->Reset();

		//Define all the variables that the joystick needs
		float magnitude;
		float direction;
		float twist;
		float throttle;

		//Angle of Gyro
		float angle;
		//User viewing for gyro readout
		int anglei;
		//If robot is in field-oriented or robot-oriented
		bool isFieldOriented = false;  //Start out in field-oriented mode
		
		//Tele-Op Mode
		while (IsOperatorControl()) {

			//GYRO/FIELD-ORIENTED Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			angle = myGyro->GetAngle();  //Get the angle of the gyro

			if (joystick->GetRawButton(4)) {  //Disable Field Oriented
				isFieldOriented = false;
			}
			else if (joystick->GetRawButton(6)) {  //Enable Field Oriented
				isFieldOriented = true;
			}
			else if (joystick->GetRawButton(2)) {  //Reset the Gyro
				myGyro->Reset();
			}
			
			//LEDs for Human Player
			if (xboxController->GetRawButton(6) && !robotLEDs->GetLoading()) {  //Right Bumper && isn't loading already
				robotLEDs->SetLoading(true);
				robotLEDs->HumanLoad();  //Set LEDs to White to indicate readiness for loading
			}
			else if (xboxController->GetRawButton(6) && robotLEDs->GetLoading()) {  //Right Bumper and is loading
				robotLEDs->SetLoading(false);
			}

			//DRIVE Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//Get joystick values
			myDrive->GetJoystickValues(magnitude, direction, twist, throttle);
			
			//Multiply by throttle for adjustable speed control
			//Field Oriented Drive -- use angle from gyro
			if (isFieldOriented) {
				myDrive->Drive_FieldOriented(throttle * magnitude, direction, throttle * twist, angle);
			}
			//Robot Oriented Drive
			else {
				myDrive->Drive_RobotOriented(throttle * magnitude, direction, throttle * twist);
			}
			//Make Gyro/Distance Sensor an integer for user viewing
			anglei = static_cast<int>(angle);

			//Shooter actions (includes full shoot and "pass" shoot)
			pneumatics->Shooter();

			//Arm actions (includes raise arm, lower arm, and automatic up/down)
			robotArm->OperateArm();
		}
	}
	void Disabled() {
		while (ds->IsDisabled()) {
			robotLEDs->Disabled();
		}
	}
};

START_ROBOT_CLASS(Team2530);

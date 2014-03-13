#include "WPILib.h"
#include "CameraServo.h"

//http://www.chiefdelphi.com/forums/showthread.php?t=89510
CameraServo::CameraServo (uint32_t channel){
	camera_servo = new Servo (7);
	joystick = new Joystick (1);
	xbox_controller = new Joystick (2);
	desiredAngle[0] = 0.0;
	desiredAngle[1] = 25.0;
	desiredAngle[2] = 75.0;
	upPushed = false;
	downPushed = false;
	currentAngle = 1;

}

void CameraServo::turnCamera() {
	bool up = upPushed;
	bool down = downPushed;

	upPushed = joystick->GetRawButton(5) || xbox_controller->GetRawButton(4);
	downPushed = joystick->GetRawButton(3) || xbox_controller->GetRawButton(3);

	//Angles camera up

	if (up == false && upPushed == true)

	{
		currentAngle ++;
		if (currentAngle >= angles)
			currentAngle = angles - 1;

	}

	//Angles camera down

	if (down == false && downPushed == true)
	{
		currentAngle --;
		if (currentAngle < 0)
			currentAngle = 0;
	}

	camera_servo->SetAngle(desiredAngle[currentAngle]);
}

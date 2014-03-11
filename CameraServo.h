#include "WPILib.h"
class CameraServo {
	Servo * camera_servo;
	Joystick * joystick;
	Joystick * xbox_controller;
	static const int angles = 3;
	float desiredAngle[angles];
	bool upPushed;
	bool downPushed;
	int currentAngle;
	
public:
	CameraServo(uint32_t channel);
	void turnCamera();
};

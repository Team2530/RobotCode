#include "WPILib.h"
#include "LEDs.h"
/* LED Driver program for Ishaan's digital LEDs
 * Documentation is in the programming folder on Google Drive
 */
LEDs::LEDs() {
	//Initialize DigitalIOs for LEDs
	dig2 = new DigitalOutput(2);
	dig3 = new DigitalOutput(3);
	dig4 = new DigitalOutput(4);
	dig5 = new DigitalOutput(5);
	dig6 = new DigitalOutput(6);
};
void LEDs::Disabled() {
//	[1,1,1,1,1] 
	dig2->Set(1);
	dig3->Set(1);
	dig4->Set(1);
	dig5->Set(1);
	dig6->Set(1);
};
void LEDs::AutoDriving() {
//	[0, 1, 1, 1, 1]
	dig2->Set(0);
	dig3->Set(1);
	dig4->Set(1);
	dig5->Set(1);
	dig6->Set(1);
};
void LEDs::TeleDriving() {
//	[0, 0, 1, 1, 1]
	dig2->Set(0);
	dig3->Set(0);
	dig4->Set(1);
	dig5->Set(1);
	dig6->Set(1);
};
void LEDs::ArmUp() {
//	[0, 0, 1, 1, 0]
	dig2->Set(0);
	dig3->Set(0);
	dig4->Set(1);
	dig5->Set(1);
	dig6->Set(0);
};
void LEDs::ArmDown() {
//	[0, 0, 1, 0, 1]
	dig2->Set(0);
	dig3->Set(0);
	dig4->Set(1);
	dig5->Set(0);
	dig6->Set(1	);
};
void LEDs::Fire() {
//	[0, 1, 0, 1, 1]
	dig2->Set(0);
	dig3->Set(1);
	dig4->Set(0);
	dig5->Set(1);
	dig6->Set(1);
};
void LEDs::SoftFire() {
//	[0, 0, 1, 0, 0]
	dig2->Set(0);
	dig3->Set(0);
	dig4->Set(1);
	dig5->Set(0);
	dig6->Set(0);
};
void LEDs::HumanLoad() {
//	[0, 0, 0, 1, 1]
	dig2->Set(0);
	dig3->Set(0);
	dig4->Set(0);
	dig5->Set(1);
	dig6->Set(1);
};

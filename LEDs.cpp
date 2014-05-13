#include "WPILib.h"
#include "LEDs.h"
/* LED Driver program for Ishaan's digital LEDs
 * Documentation is in the programming folder on Google Drive
 */
LEDs::LEDs() {
	//If robot is loading the ball from human player
	load = false;
	//Initialize DigitalIOs for LEDs
	dig2 = new DigitalOutput(2);
	dig3 = new DigitalOutput(3);
	dig4 = new DigitalOutput(4);
	dig5 = new DigitalOutput(5);
	dig6 = new DigitalOutput(6);
};

//Getter/setter for loading boolean
bool LEDs::GetLoading() {
	return load;
}
void LEDs::SetLoading(bool loading) {
	load = loading;
}

/*
 * Methods to set pins on LED control board from DigitalIO
 * If it's not inbounding from the Human Player, LEDs set to their respective colors
 * If it is loading, do nothing
 * Comment format: [state_P2, state_P3, state_P4, state_P5, state_P6]
 */
void LEDs::Disabled() {  //Color flashing
	//	[0, 0, 0, 0, 0] 
	dig2->Set(0);
	dig3->Set(0);
	dig4->Set(0);
	dig5->Set(0);
	dig6->Set(0);
};
void LEDs::AutoDriving() {  //Solid Yellow
	//	[1, 0, 0, 0, 0]
	dig2->Set(1);
	dig3->Set(0);
	dig4->Set(0);
	dig5->Set(0);
	dig6->Set(0);
};
void LEDs::TeleDriving() {  //Solid Green
	//	[1, 1, 0, 0, 0]
	if (!GetLoading()) {
		dig2->Set(1);
		dig3->Set(1);
		dig4->Set(0);
		dig5->Set(0);
		dig6->Set(0);
	}
};
void LEDs::ArmUp() {  //Rolling up
	//	[1, 1, 0, 0, 1]
	if (!GetLoading()) {
		dig2->Set(1);
		dig3->Set(1);
		dig4->Set(0);
		dig5->Set(0);
		dig6->Set(1);
	}
};
void LEDs::ArmDown() {  //Rolling down
	//	[1, 1, 0, 1, 0]
	if (!GetLoading()) {
		dig2->Set(1);
		dig3->Set(1);
		dig4->Set(0);
		dig5->Set(1);
		dig6->Set(0);
	}
};
void LEDs::Fire() {  //Magenta
	//	[1, 0, 1, 0, 0]
	if (!GetLoading()) {
		dig2->Set(1);
		dig3->Set(0);
		dig4->Set(1);
		dig5->Set(0);
		dig6->Set(0);
	}
};
void LEDs::SoftFire() {  //Orange
	//	[1, 1, 0, 1, 1]
	if (!GetLoading()) {
		dig2->Set(1);
		dig3->Set(1);
		dig4->Set(0);
		dig5->Set(1);
		dig6->Set(1);
	}
};
void LEDs::HumanLoad() {  //White
	//	[1, 1, 1, 0, 0]
	dig2->Set(1);
	dig3->Set(1);
	dig4->Set(1);
	dig5->Set(0);
	dig6->Set(0);
};

#include "EV4Sonic.h"

EV4Sonic::EV4Sonic(uint32_t port)
{
	_port = new AnalogChannel(port);
}

float EV4Sonic::GetDistanceIN()
{
	return _port->GetVoltage() * 1000.0 / 9.765625; // https://www.edmodo.com/post/203038755, from Ishaan
}


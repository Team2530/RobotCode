#ifndef _EV4_SONIC_H
#define _EV4_SONIC_H

#include "WPILib.h"
#include "UltraSonic.h"

// FIXME/TODO: we're just going to use a analog input?
class EV4Sonic : public UltraSonic
{
public:
	EV4Sonic(uint32_t port);
	virtual float GetDistanceIN();
private:
	AnalogChannel* _port;
};

#endif // _EV4_SONIC_H


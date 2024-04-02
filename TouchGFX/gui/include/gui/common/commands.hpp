#ifndef COMMANDS_HPP
#define COMMANDS_HPP

void calibrate_throttle(const float input);

//void (* const keypad_command[256])(const float input) =
//{
//	calibrate_throttle
//};

// To be stored in the microcontroller memory
const float keypad_command_value[256] =
{
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

static char const* const keypad_command_names[256] =
{
	"Calibrate\nThrottle\nSensor",
	"Set Throttle\nSensitivity",
	"Set Motor\nTransmit\nFrequency",
	"Set Regen\nBrake\nSensitivity",
	"Test\nThrottle\nSound",
	"Add User"
};

#endif

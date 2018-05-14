
#pragma once

#include <wiringPi.h>



class PinIO
{
public:
	PinIO();
	static bool initialize_pin_list();
	static bool check_pin_availability(int number);
	static bool pin_set_used(int number);
	static void pin_set_no_longer_used(int number);
	


private:
	static int i_;
	static bool occupied_pins_[28];
};

#include "PinIO.h"


PinIO::PinIO()
{
	initialize_pin_list();
}

bool PinIO::initialize_pin_list()
{
	for (int i = 0; i < 28; i++)
	{
		occupied_pins_[i] = false;
	}
	return true;
}

bool PinIO::check_pin_availability(int number)
{
	return occupied_pins_[number];
}

bool PinIO::pin_set_used(int number)
{

	if (check_pin_availability(number) == true)
	{
		std::cout << "Pin already in use!" << std::endl;
	}
	else
	{
		occupied_pins_[number] = true;
		return true;
	}
}

void PinIO::pin_set_no_longer_used(int number)
{
	occupied_pins_[number] = false;
}


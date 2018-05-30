#include "PinManager.h"

std::vector<int> PinManager::pins_{};

PinManager::PinManager()
{}

void PinManager::set_pin(int number)
{
	PinManager::pins_.push_back(number);
	std::cout << number << " is used now " << std::endl;
}

void PinManager::free_pin(int number)
{
	for (int i = 0; i < PinManager::pins_.size(); i++)
	{
		if (PinManager::pins_[i] == number)
		{
			std::cout << PinManager::pins_[i] << " is now free! " << std::endl;
			PinManager::pins_.erase(pins_.begin()+i);
		}
	}
}

void PinManager::get_pins_forgiven()
{
	for (int i = 0; i < PinManager::pins_.size(); i++)
	{
		std::cout << PinManager::pins_[i] << " is a forgiven pin " << std::endl;
	}
}

void PinManager::pin_state(int number)
{
	int forgiven = -1;
	for (int i = 0; i < PinManager::pins_.size(); i++)
	{
		if (number == PinManager::pins_[i])
		{
			std::cout << PinManager::pins_[i] << " is forgiven! " << std::endl;
			forgiven = 1;
		}
	}
	if (forgiven == -1)
	{
		std::cout << number << " is free! " << std::endl;

	}
}

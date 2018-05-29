#include "PinManager.h"

PinManager::PinManager()
{}

void PinManager::set_pin(int number)
{
	PinManager::pins_.push_back(number);
}

void PinManager::free_pin(int number)
{
	for (int i = 0; i < PinManager::pins_.size(); i++)
	{
		if (PinManager::pins_[i] == number)
		{
			PinManager::pins_.erase(pins_.begin()+i);
		}
	}
}

void PinManager::get_pins_forgiven()
{
	for (int i = 0; i < PinManager::pins_.size(); i++)
	{
		std::cout << PinManager::pins_[i] << "is forgiven" << std::endl;
	}
}

void PinManager::pin_state(int number)
{
	int forgiven = -1;
	for (int i = 0; i < PinManager::pins_.size(); i++)
	{
		if (number == PinManager::pins_[i])
		{
			std::cout << PinManager::pins_[i] << "is forgiven!" << std::endl;
			forgiven = 1;
		}
		if (forgiven == -1)
		{
			std::cout << number << "is free!" << std::endl;
		}
	}
}

#include "PinManager.h"

//wenn nicht passt, vor Pins PinManager:: !!!

void PinManager::set_pin(int number)
{
	pins_.push_back(number);
}

void PinManager::free_pin(int number)
{

	for (int position = 0; position < pins_.size(); position++)
	{
		if (pins_[position] == number)
		{
			pins_.erase(pins_.begin()+position);
		}
	}

}
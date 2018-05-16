#include "Digital_Input.h"

Digital_Input::Digital_Input(int number)
{
	number_ = number;
	pinMode(number_, INPUT);
}

int Digital_Input::get_number() const
{
	return number_;
}

int Digital_Input::read_input() const
{
	return digitalRead(number_);
};

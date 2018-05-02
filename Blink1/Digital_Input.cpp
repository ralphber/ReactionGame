#include "Digital_Input.h"

Digital_Input::Digital_Input(int number)
{
	pinMode(number_, INPUT);
	number_ = number;
}

int Digital_Input::get_number() const
{
	return number_;
}

int Digital_Input::read_input() const
{
	return digitalRead(number_);
};

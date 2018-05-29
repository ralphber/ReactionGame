#include "Digital_Output.h"

Digital_Output::Digital_Output(char number)
{
	number_ = number;
	pinMode(number, OUTPUT);
}

int Digital_Output::get_number() const
{
	return number_;
}

void Digital_Output::set_on_off(bool level)
{
	digitalWrite(number_, level);
}


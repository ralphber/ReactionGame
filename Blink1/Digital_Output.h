#pragma once

#include <wiringPi.h>

class Digital_Output
{
public:

	Digital_Output(char number);
	int get_number() const;
	void set_on_off(bool);

private:
	char number_;
};


#pragma once

#include "piproxy.h"

class Digital_Input
{
public:

	Digital_Input(int number);

	int get_number() const;
	int read_input() const;

private:
	int number_;
};

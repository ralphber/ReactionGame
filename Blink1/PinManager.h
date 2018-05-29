#pragma once

#include <stdlib.h>
#include <chrono>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>


class PinManager
{
	static std::vector<int> pins_;

public:

	PinManager();
	void set_pin(int number);
	void free_pin(int number);
	void get_pins_forgiven();
	void pin_state(int number);

	~PinManager() = default;

};

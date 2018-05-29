#pragma once

#include <vector>

class PinManager
{
	static std::vector<int> pins_;

public:

	void set_pin(int number);
	void free_pin(int number);

private:



};

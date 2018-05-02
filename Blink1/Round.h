#pragma once

#include <string>
#include <chrono>


class Round
{
	using duration = std::chrono::_V2::system_clock::duration;

public:

	Round(int roundnum);
	
	void set_winner(std::string);
	std::string get_winner() const;

private:
	int roundnum_; // MFA never used
	std::string winner_;
};
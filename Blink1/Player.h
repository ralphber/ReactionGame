#pragma once

#include <string>
#include <chrono>

class Player
{
	using duration = std::chrono::system_clock::duration;

public:

	Player(std::string name);

	std::string get_name() const;
	void add_win();
	int read_wins() const;
	void set_delta(duration);
	duration get_delta() const;
	void set_name(std::string name);

private:

	std::string name_;
	int numofwins_;
	duration delta_;
};


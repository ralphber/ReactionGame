#include "Player.h"

using duration = std::chrono::system_clock::duration;

Player::Player(std::string name) :
	name_{ name },
	numofwins_ {0}
{
}

std::string Player::get_name() const
{
	return name_;
}

void Player::add_win() 
{
	numofwins_++;
	return;
}

int Player::read_wins() const
{
	return numofwins_;
}

void Player::set_delta(duration delta)
{
	delta_ = delta;
	return;
}

duration Player::get_delta() const
{
	return delta_;
}

void Player::set_name(std::string name)
{
	name_ = name;
}



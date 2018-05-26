#include "Player.h"

using duration = std::chrono::system_clock::duration;
duration zero = std::chrono::system_clock::duration::zero();

Player::Player(std::string name) :
	name_{ name },
	numofwins_{ 0 },
	delta_{ zero }
{
}

std::string Player::get_name() const
{
	return name_;
}

void Player::add_win() 
{
	numofwins_++;
}

int Player::read_wins() const
{
	return numofwins_;
}

void Player::set_delta(duration delta)
{
	delta_ = delta;
}

duration Player::get_delta() const
{
	return delta_;
}

void Player::set_name(std::string name)
{
	name_ = name;
}



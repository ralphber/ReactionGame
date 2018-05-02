
#include "Round.h"

#include <iostream>

using duration = std::chrono::_V2::system_clock::duration;

Round::Round(int roundnum) :
	roundnum_{ roundnum },
	winner_{"Nobody"}
{
}

void Round::set_winner(std::string winner) 
{
	winner_ = winner;
	return ;
}

std::string Round::get_winner() const
{
	return winner_;
}


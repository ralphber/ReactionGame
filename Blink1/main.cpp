#include "piproxy.h"
#include <stdlib.h>
#include <chrono>	
#include <sstream>
#include <string>
#include <iostream>

#include "Digital_Output.h"
#include "Digital_Input.h"
#include "Player.h"
#include "Round.h"
#include "json.hpp"
#include <fstream>


// for convenience
using json = nlohmann::json;

using namespace std;

int led_player2 = 8;
int led_player1 = 7;
int state_led_pin = 9;
int button_inter_1 = 0;
int button_inter_2 = 2;

void on_button_1();
void Game_In_Progress(int numofrounds, Digital_Output &player1_led, Digital_Output &player2_led, Digital_Output &state_led);
void Print_Results();
void on_button_2();

//*******TIMETYPEDEF*******
typedef std::chrono::system_clock::duration time_type;
time_type time_now = std::chrono::system_clock::now().time_since_epoch();
time_type zero_time = std::chrono::system_clock::duration::zero();

string play_round(Player&, Player&, int);
Player player1("Max");
Player player2("Michael");



int main(void)
{
	std::ifstream i("pins.json");
	json j;
	i >> j;

	led_player2 = j["p2_led"].get<int>();
	led_player1 = j["p1_led"].get<int>();
	state_led_pin = j["state"].get<int>();
	button_inter_1 = j["p1_button"].get<int>();
	button_inter_2 = j["p2_button"].get<int>();

	
	wiringPiSetup();

	Digital_Output player1_led = Digital_Output(led_player1);
	Digital_Output player2_led = Digital_Output(led_player2);
	Digital_Output state_led = Digital_Output(state_led_pin);

	Digital_Input button1 = Digital_Input(button_inter_1);
	Digital_Input button2 = Digital_Input(button_inter_2);

	//*****EVERY LED OFF*****
	player1_led.set_on_off(LOW);
	player2_led.set_on_off(LOW);
	state_led.set_on_off(LOW);

	//*****ACTIVATE INTERRUPTS*****
	wiringPiISR(button_inter_1, INT_EDGE_RISING, &on_button_1);
	wiringPiISR(button_inter_2, INT_EDGE_RISING, &on_button_2);

	//*****************INPUT*****************

	//input before starting the game
	std::cout << "Hello! Enter nicknames of Player 1 and Player 2 as well as how many rounds to play:" << std::endl;
	std::cout << "--Player 1--   --Player 2--   --Number of rounds to play--" << std::endl;

	string input; // MFA move declarations closer to usage
	string name1, name2;
	int numofrounds = -1;

	while (numofrounds < 0)
	{
		getline(cin, input);
		stringstream in_str{ input };

		if (in_str >> name1 >> name2 >> numofrounds)
		{

			std::cout << "The contestants are: " << name1 << " vs. " << name2 << "! " << std::endl;
			std::cout << "They will be playing " << numofrounds << " rounds! " << std::endl;
			player1.set_name(name1);
			player2.set_name(name2);
		}
		else
		{
			std::cout << "This was not a valid input!" << std::endl;
		}
	}

	Game_In_Progress(numofrounds, player1_led, player2_led, state_led);
	Print_Results();

	getchar();
}

void Print_Results()
{

	if (player1.read_wins() > player2.read_wins())
	{
		std::cout << "The winner of the Game is: " << player1.get_name() << std::endl;
	}
	else
	{
		std::cout << "The winner of the Game is: " << player2.get_name() << std::endl;
	}

	std::cout << "Won Rounds:  \n" << player1.get_name() << ": " << player1.read_wins() << "\n" << player2.get_name() << ": " << player2.read_wins() << "\n" << std::endl;
}

void Game_In_Progress(int numofrounds, Digital_Output &player1_led, Digital_Output &player2_led, Digital_Output &state_led)
{
	//actual game in progress
	for (int i = 0; i < numofrounds; i++)
	{
		std::cout << "New Round begins!" << std::endl;
		time_now = zero_time;
		player1_led.set_on_off(LOW);
		player2_led.set_on_off(LOW);
		state_led.set_on_off(LOW);
		player1.set_delta(zero_time);
		player2.set_delta(zero_time);


		//***********STATUS UPDATE***********
		for (int i = 0; i < 5; i++)
		{
			state_led.set_on_off(HIGH);
			delay(200);
			state_led.set_on_off(LOW);
			delay(200);
		}

		int min_time = 5000;
		int time_till_end = 5000;
		int wait_time = (rand() % min_time + time_till_end); // is in the range 5s to 10s
		delay(wait_time);


		state_led.set_on_off(HIGH);	//START TO PRESS
		time_now = std::chrono::system_clock::now().time_since_epoch();	//nanoseconds
		string winner = play_round(player1, player2, i);

		if (winner == player1.get_name())
		{
			player1.add_win();
		}
		else if (winner == player2.get_name())
		{
			player2.add_win();
		}
		else
		{
			std::cout << "Nobody has won!" << std::endl;
		}
		//winnner
		cout << "The winner of this round is " << winner << "!" << endl;
		delay(2500);
	}
}


void on_button_1()
{
	digitalWrite(led_player1, HIGH);
	if (time_now == zero_time)
	{
		player1.set_delta(-std::chrono::system_clock::now().time_since_epoch());
	}
	else
	{
		time_type player_time1 = std::chrono::system_clock::now().time_since_epoch();
		time_type delta_1 = player_time1 - time_now;
		player1.set_delta(delta_1);
	}
}

void on_button_2()
{
	digitalWrite(led_player2, HIGH);
	if (time_now == zero_time)
	{
		player2.set_delta(-std::chrono::system_clock::now().time_since_epoch());
	}
	else
	{
		time_type player_time2 = std::chrono::system_clock::now().time_since_epoch();
		time_type delta_2 = player_time2 - time_now;
		player2.set_delta(delta_2);
	}
}

string play_round(Player &player1, Player &player2, int current_rnd)
{
	Round Round(current_rnd);

	delay(3000);


	if ((player1.get_delta() == zero_time) && (player2.get_delta() == zero_time))		//Nobody pressed
	{
		cout << "Guys, play!" << endl;
		Round.set_winner("nobody");
		return Round.get_winner();
	}
	else if ((player1.get_delta() == zero_time))		//Player1 not pressed
	{
		if (player2.get_delta() > zero_time)	 //Player2 pressed right, player 1 not pressed
		{
			Round.set_winner(player2.get_name());
		}
		if (player2.get_delta() < zero_time)		//Player2 pressed wrong
		{
			Round.set_winner(player1.get_name());
		}
	}
	else if ((player2.get_delta() == zero_time))		//Player2 not pressed
	{
		if (player1.get_delta() > zero_time)	//Player1 pressed right
		{
			Round.set_winner(player1.get_name());
		}
		if (player1.get_delta() < zero_time)		//Player1 pressed wrong
		{
			Round.set_winner(player2.get_name());
		}
	}
	else if(player1.get_delta() < zero_time)		//Player1 pressed wrong
	{
		if (player2.get_delta() < zero_time)	//Player2 pressed wrong
		{
			if (player1.get_delta() > player2.get_delta())	//Player1 pressed earlier as Player2
			{
				Round.set_winner(player2.get_name());
			}
			else
			{
				Round.set_winner(player1.get_name());
			}
		}
		if (player2.get_delta() > zero_time)		//Player2 pressed right
		{
			Round.set_winner(player2.get_name());
		}
	}
	else if (player1.get_delta() > zero_time)		//Player1 pressed right
	{
		if (player2.get_delta() < zero_time)	//Player2 pressed wrong
		{
			Round.set_winner(player1.get_name());
		}
		if (player2.get_delta() > zero_time)		//Player2 pressed right
		{
			if (player1.get_delta() < player2.get_delta())	//Player1 pressed earlier as Player2
			{
				Round.set_winner(player1.get_name());
			}
			else
			{
				Round.set_winner(player2.get_name());
			}
		}
	}

	return Round.get_winner();
}
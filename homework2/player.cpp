#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include "player.h"

Player::Player(const std::string& team_name, const std::string& player_name)
{
	m_num_goal = 0;
	m_num_assist = 0;
	m_num_penalty = 0;
	m_team_name = team_name;
	m_player_name = player_name;
}

void Player::add_goal()
{
	m_num_goal++;
}
void Player::add_assist()
{
	m_num_assist++;
}
void Player::add_penalty()
{
	m_num_penalty++;
}

int Player::get_goal() const
{
	return m_num_goal;
}
int Player::get_assist() const
{
	return m_num_assist;
}
int Player::get_penalty() const
{
	return m_num_penalty;
}
std::string Player::get_team_name() const
{
	return m_team_name;
}
std::string Player::get_name() const
{
	return m_player_name;
}
bool sort_player(const Player& player1, const Player& player2)
{
	int total1 = player1.get_goal()+player1.get_assist();
	int total2 = player2.get_goal()+player2.get_assist();
	if (total1 > total2)
	{
		return true;
	}
	else if (total1 < total2)
	{
		return false;
	}
	else
	{
		if (player1.get_penalty() < player2.get_penalty())
		{
			return true;
		}
		else if (player1.get_penalty() > player2.get_penalty())
		{
			return false;
		}
		else
		{
			return player1.get_name() < player2.get_name();
		}
	}
}

// bool sort_by_goal(const Player& player1, const Player& player2)
// {
// 	if (player1.get_goal() > player2.get_goal())
// 	{
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}

// }
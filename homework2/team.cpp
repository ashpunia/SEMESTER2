#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include "team.h"

Team::Team(const std::string& team_name)
{
	m_num_win = 0;
	m_num_loss = 0;
	m_num_tie = 0;
	m_num_goal = 0;
	m_num_penalty = 0;
	m_team_name = team_name;
}

std::string Team::get_name() const
{
	return m_team_name;
}

void Team::add_win()
{
	m_num_win++;
}
void Team::add_loss()
{
	m_num_loss++;
}
void Team::add_tie()
{
	m_num_tie++;
}
void Team::add_goal()
{
	m_num_goal++;
}
void Team::add_penalty()
{
	m_num_penalty++;
}

float Team::calc_win_percent() const
{
	float total_matches = m_num_win + m_num_loss + m_num_tie;
	return (float)(m_num_win + (0.5*m_num_tie))/total_matches;
}

int Team::get_win() const
{
	return m_num_win;
}
int Team::get_loss() const
{
	return m_num_loss;
}
int Team::get_tie() const
{
	return m_num_tie;
}
int Team::get_goal() const
{
	return m_num_goal;
}
int Team::get_penalty() const
{
	return m_num_penalty;
}

//true if team1 is before team2
bool sort_team(const Team& team1, const Team& team2)
{
	if (team1.calc_win_percent() > team2.calc_win_percent())
	{
		return true;
	}
	else if (team1.calc_win_percent() < team2.calc_win_percent())
	{
		return false;
	}
	else
	{
		if (team1.get_goal() > team2.get_goal())
		{
			return true;
		}
		else if (team1.get_goal() < team2.get_goal())
		{
			return false;
		}
		else
		{
			return team1.get_name() < team2.get_name();
		}
	}
}
bool sort_by_goal(const Team& team1, const Team& team2)
{
	if (team1.get_goal() > team2.get_goal())
	{
		return true;
	}
	else
	{
		return false;
	}
}

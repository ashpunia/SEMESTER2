#ifndef __team_h_
#define __team_h_

#include <iostream>
#include <vector>

class Team 
{
public: 
	//CONSTRUCTORS
	Team(const std::string& team_name);
	//ACCESSORS
	std::string get_name() const;
	int get_win() const;
	int get_loss() const;
	int get_tie() const;
	int get_goal() const;
	int get_penalty() const;

	//MODIFIERS
	void add_win();
	void add_loss();
	void add_tie();
	void add_goal();
	void add_penalty();
	float calc_win_percent() const;


private:
	
	int m_num_win;
	int m_num_loss;
	int m_num_tie;
	int m_num_goal;
	int m_num_penalty;
	std::string m_team_name;
};

bool sort_team(const Team& team1, const Team& team2);
bool sort_by_goal(const Team& team1, const Team& team2);
#endif
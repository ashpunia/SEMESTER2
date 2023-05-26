#ifndef __player_h_
#define __player_h_

#include <iostream>
#include <vector>

class Player
{
public:
	//CONSTRUCTORS
	Player(const std::string& team_name,const std::string& player_name);

	void add_goal();
	void add_assist();
	void add_penalty();

	int get_goal() const;
	int get_assist() const;
	int get_penalty()const;
	std::string get_team_name() const;
	std::string get_name()const;
private:
	int m_num_goal;
	int m_num_assist;
	int m_num_penalty;
	std::string m_team_name;
	std::string m_player_name;

};
bool sort_player(const Player& player1, const Player& player2);
//bool sort_by_goal(const Player& player1, const Player& player2);
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "team.h"
#include "player.h"

//std::vector <Team> team_vector;

//finding longest team names to print the right spaces
int longest_tname(const std::vector<Team>& team_vector)
{	
	int length = 0;
	for (unsigned int i = 0; i< team_vector.size(); i++)
	{
		if ((int)team_vector[i].get_name().size() > length)
		{
			length = team_vector[i].get_name().size();
		}
	}
	return length;
}
//longest player name to print the right spaces
int longest_pname(const std::vector<Player>& player_vector)
{	
	int length = 0;
	for (unsigned int i = 0; i< player_vector.size(); i++)
	{
		if ((int)player_vector[i].get_name().size() > length)
		{
			length = player_vector[i].get_name().size();
		}
	}
	return length;
}
//printing the team stats
void print_team(std::vector <Team>& team_vector, std::ofstream& out_str)
{
	int spaces = longest_tname(team_vector);
	out_str<<std::left<<std::setw(spaces+4)<<"Team Name"<<std::setw(4)<<"W"
	<<std::setw(4)<<"L"<<std::setw(4)<<"T"<<std::setw(6)<<"Win%"
	<<std::setw(7)<<"Goals"<<"Penalties"<<std::endl;
	std::sort(team_vector.begin(), team_vector.end(), sort_team);
	
	for (unsigned int i = 0; i<team_vector.size();i++)
	{
		Team team = team_vector[i];
		out_str<<std::left<<std::setw(spaces+2)<<team.get_name()<<
		std::right<<std::setw(3)<<team.get_win()<<std::setw(4)<<team.get_loss()
		<<std::setw(4)<<team.get_tie()<<std::setprecision(2)<<std::fixed<<std::setw(7)
		<<team.calc_win_percent()<<std::setw(7)<<team.get_goal()<<std::setw(11)
		<<team.get_penalty()<<std::endl;
	}
}
//printing the player stats
void print_player_stats(std::vector <Player>& player_vector, const std::vector <Team>& team_vector,
						std::ofstream& out_str)
{
	int spaces = longest_pname(player_vector);
	int teamspace = longest_tname(team_vector);
	out_str<<std::left<<std::setw(spaces+2)<<"Player Name"<<
	std::setw(teamspace+3)<<"Team"<<std::setw(7)<<"Goals"<<std::setw(9)<<"Assists"
	<<"Penalties"<<std::endl;

	std::sort(player_vector.begin(), player_vector.end(), sort_player);
	for (unsigned int i = 0; i<player_vector.size();i++)
	{
		Player player = player_vector[i];
		if(player.get_name() != "BENCH")
		{
			out_str<<std::left<<std::setw(spaces+2)<<player.get_name()<<
			std::setw(teamspace+3)<<player.get_team_name()<<std::right
			<<std::setw(5)<<player.get_goal()<<std::setw(9)<<player.get_assist()
			<<std::setw(11)<<player.get_penalty()<<std::endl;
		}
	}
}
//find the Team
int find_team(const std::vector<Team>& vector, const std::string& name)
{
	for (unsigned int i = 0; i<vector.size();i++)
	{
		if (vector[i].get_name() == name)
		{
			return i;
		}
	}
	return -1;
}
//find the player
int find_player(const std::vector<Player>& vector, const std::string& name,
	            const std::string& team_name)
{
	for (unsigned int i = 0; i<vector.size();i++)
	{ 
		if (vector[i].get_name() == name && vector[i].get_team_name() == team_name)
		{
			return i;
		}
	}
	return -1;
}

//check if the word has the ":" telling us it's the time
bool has_colon(const std::string& word)
{
	for (unsigned int i = 0; i < word.size();i++)
	{
		if (word[i] == ':')
		{
			return true;
		}
	}
	return false;
}

//updating the wins, the losses and the ties to each team
void update_records(std::vector<Team>& team_vector,std::vector<std::string>& score_vector)
{
	int team1 = find_team(team_vector,score_vector[0]);
	int team2 = find_team(team_vector,score_vector[2]);
	if (std::stoi(score_vector[1])<std::stoi(score_vector[3]))
	{
		team_vector[team2].add_win();
		team_vector[team1].add_loss();
	}
	else if (std::stoi(score_vector[1])>std::stoi(score_vector[3]))
	{
		team_vector[team1].add_win();
		team_vector[team2].add_loss();
	}
	else
	{
		team_vector[team1].add_tie();
		team_vector[team2].add_tie();
	}

}

//adding the assists to each time
void add_assist(std::vector<Player>& player_vector, const std::vector<std::string>& line )
{
	for (unsigned int i = 3; i<line.size();i++)
	{
		int index = find_player(player_vector,line[i],line[0]);
		if (index == -1)
		{
			player_vector.push_back(Player(line[0],line[i]));
			player_vector[player_vector.size()-1].add_assist();
		}
		else
		{
			player_vector[index].add_assist();
		}
	}
}

//team = line[0]
//player = line[2]
void add_goals( std::vector<Player>& player_vector,  std::vector<Team>& team_vector,
                std::string team, std::string player)
{
	int index = find_team(team_vector,team);
	team_vector[index].add_goal();
	index = find_player(player_vector,player,team);
	//if it doesn't find it the player in the list already
	if (index == -1)
	{
		player_vector.push_back(Player(team,player));
		player_vector[player_vector.size()-1].add_goal();
	}
	else
	{
		player_vector[index].add_goal();
	}
}
//team = line[0]
//player = line[2]
void add_penalty( std::vector<Player>& player_vector, std::vector<Team>& team_vector, 
	              std::string team, std::string player)
{
	int index = find_team(team_vector,team);
	team_vector[index].add_penalty();
	index = find_player(player_vector,player,team);
	if (index == -1)
	{
		player_vector.push_back(Player(team,player));
		player_vector[player_vector.size()-1].add_penalty();
	}
	else
	{
		player_vector[index].add_penalty();
	}	
}
//printing out the best teams based on goals
void print_custom_stats(std::vector<Team>& team_vector,
						std::ofstream& out_str)
{

	std::sort(team_vector.begin(), team_vector.end(), sort_by_goal);	
	out_str<<"Best teams from the given year:"<<std::endl;	
	for (unsigned int i = 0; i < team_vector.size(); i++)
	{
		out_str<<team_vector[i].get_name()<<std::endl;
	}

}
//parsing the input file and finding the info
void find_info(const std::string& file,std::vector<Team>& team_vector,
			   std::vector<Player>& player_vector)
{
	std::ifstream in_str(file);
	std::vector<std::string> temp;
	std::string word;
	bool check = false;
	while(in_str >> word)
	{
		//skips the date and the period
		in_str >> word >> word >> word >> word;
		if (find_team(team_vector,word) == -1)
		{
			//adds the first team
			team_vector.push_back(Team(word));
		}
		in_str >> word >> word;
		if (find_team(team_vector,word) == -1)
		{
			//adds the second team
			team_vector.push_back(Team(word));
		}
		//until we get to the end of the game
		while(word != "FINAL")
		{
			//middle part where the info is
			while (!has_colon(word))
			{
				in_str >> word;
				if (word == "FINAL")
				{
					check = true;
					break;
				}
			}
			if (check)
			{
				check = false;
				break;
			}
			//putting that info to the line vector
			std::vector<std::string> line;
			for(int i = 0; i<3;i++)
			{
				in_str>>word;
				line.push_back(word);
			}

			in_str>>word;
			if (word == "(")
			{
				in_str>>word;
				while (word != ")")
				{
					line.push_back(word);
					in_str>>word;
				}

			}
			//line[1] is the part of my vector which tells me what to add
			if (line[1] == "goal")
			{
				add_goals(player_vector,team_vector,line[0],line[2]);
				//checks if there is an assist to the goal and add to the right player
				add_assist(player_vector, line);

			}
			//line[1] is the part of my vector which tells me what to add 
			else if (line[1] == "penalty")
				//if line[1] == penalty; add to penalty
			{
				add_penalty(player_vector,team_vector,line[0],line[2]);	
			}
			if(has_colon(word))
			{
				in_str >> word;
			}
			while(!has_colon(word) && word != "FINAL")
			{
				in_str >> word;
			}
		}
		std::vector<std::string> score_vector;
		for(int i = 0; i<4;i++)
		{
			in_str>>word;
			score_vector.push_back(word);
		}
		update_records(team_vector,score_vector);
	}
}

int main(int argc, char* argv[])
{
	//assigning variables to the input
	std::string ifile = argv[1];
	std::string ofile = argv[2];
	std::string mode = argv[3];
	//making class objects
	std::vector<Team> team_vector;
	std::vector<Player> player_vector;

	//checking inputs
	if (argc < 3)
	{
		std::cout<<"Not enough arguments given.\n";
	}
	//parsing the info
	find_info(ifile,team_vector,player_vector);
	std::ofstream out_str(ofile);
	
	//printing stats based on the mode picked by the user.
	if (mode == "--team_stats")
	{
		print_team(team_vector,out_str);
	}
	else if (mode == "--player_stats")
	{
		print_player_stats(player_vector,team_vector,out_str);
	}
	else if(mode == "--custom_stats"){
		print_custom_stats(team_vector,out_str);
	}
	else
	{
		std::cout<<"invalid mode.";
	}
}
#include <string>
//You may add additional typedefs, includes, etc. up here
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "fighter.h"
//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

typedef std::map<std::string, Fighter> fighter_map;
typedef std::map<std::string, std::set<Fighter>> moves_map;
//Feel free to put forward declarations here


//parsing the database file and making my fighter objects 
void parse(std::ifstream& file, fighter_map& fighters)
{
	std::string word;
	std::string name;

	//skipping the top line with the titles
	for(int i = 0; i < 8; i++)
	{
		file >> word;
	}

	//getting the name
	while(file >> name)
	{
		Fighter fighter(name);
		for(int i = 0; i < 7; i++)
		{
			file >> word;
			//inserting te moves with the word
			fighter.insert_move(move_names[i], std::stoi(word));
		}
		//inserting it to my fighter map
		fighters.insert(std::make_pair(name, fighter));
	}
}

//makes the new set for the f and s queries 
std::set<Fighter> make_set(const std::string& move, int order, fighter_map& fighters)
{
	fighter_map::iterator itr = fighters.begin();
	while(itr != fighters.end())
	{
		(itr->second).set_comparison(move, order);
		itr++;
	}

	std::set<Fighter> fighter_set;
	itr = fighters.begin();
	while(itr != fighters.end())
	{
		fighter_set.insert(itr->second);
		itr++;
	}

	return fighter_set;
}

//printing te moves based on what move or all moves
void q(const std::string& name, const std::string& move, const fighter_map& fighters,std::ofstream& out_str)
{
	fighter_map::const_iterator itr = fighters.find(name);
	//error checking, when it doesn't find name until the end, invalid character name
	if(itr == fighters.end())
	{
		out_str << "Invalid character name: " << name << std::endl << std::endl;
	}
	else
	{
		//checking if it wants all moves or one move, if one move- what move?
		if(move == "all")
		{
			(itr->second).print_all_moves(out_str);
		}
		else
		{
			(itr->second).print_move(move,out_str);
		}
	}
}

//the order is if it finds the fastest or the slowest moves which is how it makes the set
void fs(const std::string& move, int limit, fighter_map& fighters,int order, std::ofstream& out_str)
{
	std::set<Fighter> fighter_set = make_set(move, order, fighters);
	std::set<Fighter>::const_iterator itr = fighter_set.begin();
	if(itr->get_frames(move) == -1)
	{
		out_str << "Invalid move name: " << move << std::endl << std::endl;
		return;
	}
	if (order == 0)
	{
		out_str << "-f " << move << " " << limit << std::endl;
	}
	else
	{
		out_str << "-s " << move << " " << limit << std::endl;
	}
	

	for(int i = 0; i < limit; i++)
	{
		if(itr == fighter_set.end())
		{
			break;
		}
		out_str << itr->get_name() << " " << itr->get_frames(move) <<
		std::endl;
		itr++;
	}
	out_str << std::endl;
}

//outputs the fighters that have a startup frame of [startup frame] for [move]
void d(const std::string& move, int frames, fighter_map& fighters,std::ofstream& out_str)
{
	std::set<Fighter> fighter_set = make_set(move, 0, fighters);
	std::set<Fighter>::const_iterator itr = fighter_set.begin();
	while(itr != fighter_set.end())
	{
		if(itr->get_frames(move) == frames)
		{
			out_str << itr->get_name() << std::endl;
		}
		itr++;
	}
	out_str << std::endl;
}

//parsing the input file and running the right command based on the query given 
void run_commands(std::ifstream& file, fighter_map& fighters,std::ofstream& out_str)
{
	std::string query;
	std::string arg1;
	std::string arg2;

	//finding what needs to be done
	while(file >> query)
	{
		//arg1 and arg2 tells us what we need to do based on the query 
		file >> arg1;
		file >> arg2;
		if(query == "-q")
		{
			q(arg1, arg2, fighters,out_str);
		}
		else if(query == "-f")
		{
			fs(arg1, std::stoi(arg2), fighters,0,out_str);
		}
		else if(query == "-s")
		{
			fs(arg1, std::stoi(arg2), fighters,1,out_str);
		}
		else if(query == "-d")
		{
			out_str << "-d " << arg1 << " " << arg2 << std::endl;
			d(arg1, std::stoi(arg2), fighters,out_str);
		}
	}
}
int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}

	///////Fill in the rest of main below:
	//map fo the fighters
	fighter_map fighters;
	//maps for moves
	moves_map moves;
	parse(dbfile, fighters);
	run_commands(infile, fighters, outfile);
	return 0;
}

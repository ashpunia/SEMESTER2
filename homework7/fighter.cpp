#include "fighter.h"
//constructor//
Fighter::Fighter(const std::string& name)
{
	m_name = name;
}

//inserts the move and the frame to the fighter
//arguments: move and frames
//no output just inserts into the map each fighter has
void Fighter::insert_move(const std::string& move, int frames)
{
	m_moves.insert(std::make_pair(move, frames));
}

//prints ALL the moves that the fighter has
//arguments: out_str so it can print into another file
//no output, just prints all the moves
void Fighter::print_all_moves(std::ofstream& out_str) const
{
	std::map<std::string,int>::const_iterator itr = m_moves.begin();
	while(itr != m_moves.end())
	{
		out_str << m_name << " " << itr->first << ": " <<
		itr->second << std::endl;
		itr++;
	}
	out_str << std::endl;
}

//fighter prints out the move that is given in the argument
//arguments: move it needs to print and out_str 
//no output, just prints out what move it wants and the frames
void Fighter::print_move(const std::string& move,std::ofstream& out_str) const
{
	std::map<std::string,int>::const_iterator itr;
	itr = m_moves.find(move);
	if(itr == m_moves.end())
	{
		out_str << "Invalid move name: " << move << std::endl << std::endl;
	}
	else
	{
		out_str << m_name << " " << move << ": " << itr->second <<
		std::endl << std::endl;
	}
}

//get the frames given the move
//argument: move
//output: the number of frames
int Fighter::get_frames(const std::string& move) const
{
	std::map<std::string,int>::const_iterator itr;
	itr = m_moves.find(move);
	if(itr == m_moves.end())
	{
		return -1;
	}
	else
	{
		return itr->second;
	}
}

//returns the name
//no argument
//returns the name of the fighter
std::string Fighter::get_name() const
{
	return m_name;
}

//If order is 0 then we sort by fastest, if 1 then we sort by slowest
//set the comparsion to what we want
void Fighter::set_comparison(const std::string& compare_move, int order)
{
	m_compare_move = compare_move;
	m_order = order;
}

//sort the set based on the order we want(fastest or the slowest)
bool Fighter::operator<(const Fighter& a) const
{
	if(m_order == 0)
	{
		if(this->get_frames(m_compare_move) == a.get_frames(m_compare_move))
		{
			return this->get_name() < a.get_name();
		}
		return this->get_frames(m_compare_move) < a.get_frames(m_compare_move);
	}
	else
	{
		if(this->get_frames(m_compare_move) == a.get_frames(m_compare_move))
		{
			return this->get_name() < a.get_name();
		}
		return this->get_frames(m_compare_move) > a.get_frames(m_compare_move);
	}
}
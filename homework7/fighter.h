#ifndef __fighter_h_
#define __fighter_h_

#include <map>
#include <iostream>
#include <fstream>

class Fighter
{
public:
	//the constructor//
	Fighter(const std::string& name);
	//modifiers//
	void set_comparison(const std::string& compare_move, int order);
	void insert_move(const std::string& move, int frames);
	//print function//
	void print_all_moves(std::ofstream& out_str) const;
	void print_move(const std::string& move,std::ofstream& out_str) const;
	//getter//
	int get_frames(const std::string& move) const;
	std::string get_name() const;
	//overloaded the operator("sorting")//
	bool operator<(const Fighter& a) const;
private:
	std::string m_name;
	std::map<std::string,int> m_moves;
	//a member variable in your Fighter class that will keep track of the current method used for comparison 
	std::string m_compare_move;
	//0 for slowest, 1 for the fastest
	int m_order;
};

#endif
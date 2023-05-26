#ifndef __board_h_
#define __board_h_

#include <iostream>
#include <list>
#include <string>
#include "board.h"

class Board
{
public:
	Board();
	Board(const int& width,const int& length);

	//setters
	void set_width(int& w);
	void set_length(int& l);
	
	//getters
	int get_width() const;
	int get_length() const;
private:
	int m_width;
	int m_length;
};

#endif
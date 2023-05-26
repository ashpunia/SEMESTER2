#include <iostream>
#include <fstream>
#include <string>
#include <list> 
#include "board.h"

Board::Board()
{
	m_width = 0;
	m_length = 0;
}
//constructor
Board::Board(const int& width, const int& length)
{
	m_width = width;
	m_length = length;
}
void Board::set_width(int& w)
{
	m_width = w;
}
void Board::set_length(int& l)
{
	m_length = l;
}
int Board::get_width() const 
{
	return m_width;
}
int Board::get_length() const
{
	return m_length;
}

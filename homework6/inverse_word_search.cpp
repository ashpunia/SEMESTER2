#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

//HELP! S.O.S HELP! S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S HELP!S.O.S
//I DONT UNDERSTAND
//PLEASE GIVE PITY POINTS TA
//I LOVE U TA

void parsing(const std::string& file, std::vector<std::string>& r_words, std::vector<std::string>& f_words, int& width, int& length)
{
	std::ifstream in_str(file);
	
	//checking if my input file opens
	if (!in_str.good()) 
	{
	    std::cerr << "Can't open " << file << " to read.\n";
	    exit(1);
  	}
	std::string word;

	in_str >> word;
	width = std::stoi(word);
	in_str >> word;
	length = std::stoi(word);


  	while (in_str>>word)
  	{
  		//checking where the "+" is so we add them to the words that we will use
  		if (word == "+")
  		{
  			in_str >> word;
  			r_words.push_back(word);
  		}
  		//checking where the words are 
  		if (word == "-")
  		{
  			in_str >> word;
  			f_words.push_back(word);
  		}
  	}

  	//std::cout << width << " " << length << std::endl;
}

void print(const std::vector<std::vector<char>>& board, std::ofstream& out_str)
{
	for(unsigned int i = 0; i < board.size(); i++)
	{
		for(unsigned int j = 0; j < board[i].size(); j++)
		{
			out_str << board[i][j] << " ";
		}
		out_str << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::string ifile = argv[1];
	std::string ofile = argv[2];
	std::string string = argv[3];

	std::ofstream out_str(ofile);
	//making the vectors with strings
	std::vector <std::string> r_words;
	std::vector <std::string> f_words;
	//declaring the width and length
	int width;
 	int length;
 	//parsing
	parsing(ifile,r_words,f_words, width, length);
	//making a board
	std::vector<std::vector<char>> board;
	std::vector<char> temp;
	for (unsigned int k = 0; k < r_words.size(); k++)
	{
		for(unsigned int l = 0; l < r_words[k].size();l++)
		{
			temp.push_back(r_words[k][l]);
		}
		board.push_back(temp);
	}
	print(board,out_str);
}
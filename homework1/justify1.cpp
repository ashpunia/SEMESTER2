#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//dash function just makes the dashes how long depending on the width. 
void dash(int width, std::ofstream& out_str){
	for (int i = 0; i < width+4; i++){
		out_str << "-";
	}

	out_str << std::endl;

}

//taking in the vector of strings called sentence and width. 
//splits the sentence into smaller strings based on the width, adds spaces and then adds 
//spaces for the rest of the width
void flush_left(std::vector<std::string> sentence, int width, std::ofstream& out_str){
	//the number of characters in the word
	int current_size = 0;
	//the very first bar
	out_str<< "| ";
	//going through all the words in the sentence
	for(unsigned int i = 0; i < sentence.size(); i++){
		//the number of words 
		if (sentence[i] == "long"){
			current_size+=4;
			out_str<<"long";
		}
		else{
			current_size+= sentence[i].size() + 1;
			//if the line fits in the line
			if(current_size <= width){
				out_str << sentence[i] << " ";	
			}
			else
			{
				current_size-= sentence[i].size() + 1;
				for(int i = 0; i < width - current_size; i++)
				{
					out_str << " ";
				}
				current_size = 0;
				i--;
				out_str << " |" << std::endl << "| ";
			}
		}
	}
	for(int i = 0; i < width - current_size; i++)
	{
		out_str << " ";
	}
	out_str << " |" << std::endl;
}

//same as flush right but the spaces are on the other side
void flush_right(std::vector<std::string> sentence, int width, std::ofstream& out_str){
	int current_size = 0;
	out_str<< "| ";
	std::string line = "";
	//going through all the words
	for(unsigned int i = 0; i < sentence.size(); i++){
		current_size+= sentence[i].size() + 1;
		if(current_size <= width){
			line += (sentence[i] + " ");	
		} 
		else
		{
			current_size-= sentence[i].size() + 1;
			for(int i = 0; i < width - current_size +1; i++)
			{
				out_str << " ";
			}
			line.pop_back();
			out_str << line;
			line = "";
			current_size = 0;
			i--;
			out_str << " |" << std::endl << "| ";
		}

		if(i == sentence.size() - 1) {
			for(int i = 0; i < width - current_size +1; i++)
			{
				out_str << " ";
			}
			line.pop_back();
			out_str << line << " |" << std::endl;
		}
	}
}

void full_justify(std::vector<std::string> sentence, int width, std::ofstream& out_str){
	int current_size = 0;
	out_str<< "| ";
	std::vector<std::string> line;
	for(unsigned int i = 0; i < sentence.size(); i++){
		//if it's the last word, add just the word to the current size but if it's not
		//then add the space as well
		if((int)sentence[i].size()== width) {
			current_size+= sentence[i].size();
		} else {
			current_size+= sentence[i].size() + 1;
		}
		//if the current size is less than the width so it fits in the line
		if(current_size <= width){
			line.push_back(sentence[i]);	
		} 
		else
		{
			current_size -= sentence[i].size() +2;
			int spaces = width - current_size;
			int remainder = 0;
			//last word shouldn't have any extra spaces
			if(line.size()-1 == 0)
			{
				spaces = 0;
			}
			else
			{
				// spaces if there are uneven(remainder)
				remainder = spaces % (line.size()-1);
				spaces = spaces/(line.size()-1);
			}
			//printing out the actual line
			for (unsigned int i = 0; i < line.size(); i++){
				out_str<<line[i];
				if (i != line.size()-1){	
					out_str<<" ";
					for ( int j  = 0; j < spaces; j++){
						out_str<<" ";
					}
					if(remainder>0){
						out_str<<" ";
						remainder--;
					}
				}
			}
			//clearing the line to make go through the entire paragraph
			line.clear();
			current_size = 0;
			i--;
			out_str << " |" << std::endl << "| ";
		}
	}
	//last line of the excerpt
	for (unsigned int i = 0; i<line.size();i++){
		out_str<<line[i] << " ";
	}
	for(int i = 0; i < width - current_size; i++)
	{
		out_str << " ";
	}
	out_str << " |" << std::endl;
}

int main(int argc, char* argv[])
{
	//assigning variables from the command line
	std::string ifile = argv[1];
	std::string ofile = argv[2];
	std::string str_width = argv[3];
	std::string mode = argv[4];

	//checking if the user input is invalid 
	if (argc < 5)
	{
		std::cout<<"Not enough arguments given.\n";
	}
	

	//turning width which is a string into an int
	int width = std::stoi(str_width);

	//reading from our input files
	std::ifstream in_str(ifile);
	std::vector<std::string> sentence;
	std::string temp;

	//checking if the words are too long for the width and adding hyphens
	while(in_str >> temp){
		if ((int)temp.size() > width){
			int tsize = temp.size();
			int buffer = 0;
			while(tsize>width){
				std::string temp_str = "";
				for (int i = buffer; i < width-1+buffer; i++){
					temp_str += temp[i];
				}
				buffer += width-1;
				temp_str += "-";
				sentence.push_back(temp_str);
				tsize -= width-1;
			}
			std::string temp_str = "";
			for(unsigned int i = buffer; i < temp.size(); i++)
			{
				temp_str += temp[i];
			}
			sentence.push_back(temp_str);
		} else
		{
		sentence.push_back(temp);
		 }
		
	}


	//making sure my file opens 
	std::ofstream out_str(ofile);
 	 if (!out_str.good()) 
 	 {
    	std::cerr << "Can't open " << ifile << " to write.\n";
    	exit(1);
	}
	
	//checking the mode and calling the function based on the user's choice. 
	if (mode == "flush_right")
	{
		dash(width, out_str);
		flush_right(sentence, width, out_str);
		dash(width, out_str);
	}
	else if (mode == "flush_left")
	{
		dash(width, out_str);
		flush_left(sentence, width, out_str);
		dash(width, out_str);
	} else if (mode == "full_justify")
	{
		dash(width, out_str);
		full_justify(sentence, width, out_str);
		dash(width, out_str);
	} else{
		std::cout << "Invalid mode.";
	}
 }
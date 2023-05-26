#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "kmer_map.h"

//Hash function is taken from Lab 11
class hash_string_obj {
public:

  unsigned int operator() ( const std::string& key ) const {
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
  }   
};

void find_matches(const std::string& query, unsigned int allowed_mismatches, 
									const kmer_map<hash_string_obj>& kmers, unsigned int k, 
									const std::string& genome)
{

	//We use the kmer length value to construct a key out of the given query
	//We use that key with the hash map to find all possible positions of matches
	std::string key = query.substr(0, k);
	std::vector<int> positions = kmers.find(key);
	std::vector<std::string> possible_matches;

	//For every possible position, we push back a string starting at the given position
	//with the length of the query to a vector
	for(unsigned int i = 0; i < positions.size(); i++)
	{
		std::string temp_sequence = "";
		for(unsigned int j = 0; j < query.size(); j++)
		{
			temp_sequence += genome[positions[i]+j];
		}
		possible_matches.push_back(temp_sequence);
	}

	//We loop through the vector of strings and compare each string to the query.
	//If the query and string have less than or equal to the allowed amount of 
	//mismatches we print it

	bool match = false;
	for(unsigned int i = 0; i < possible_matches.size(); i++)
	{
		unsigned int mismatches = 0;
		for(unsigned int j = k; j < query.size(); j++)
		{
			if(query[j] != possible_matches[i][j])
			{
				mismatches++;
			}
		}
		if(mismatches <= allowed_mismatches)
		{
			match = true;
			std::cout << positions[i] << " " << mismatches << " " << possible_matches[i] << std::endl;
		}
	}

	//We use the "match" boolean to keep track of whether or not we find any matches.
	//If it is still false after we loop through all possible matches we know that there
	//are no matches for that query
	if(!match)
	{
		std::cout << "No Match" << std::endl;
	}
}

int main()
{
	std::string filename;
	int table_size = 100;
	float occupancy = 0.5;
	int k = 0;
	int mismatches = 0;
	std::string query_string;
	std::string user_input;
	std::vector<std::pair<std::string, int>> queries;
	std::string genome = "";
	while(std::cin >> user_input)
	{
		//finds the word genome and opens that file
		if (user_input == "genome")
		{
			std::cin >> user_input;
			filename = user_input;
			std::ifstream in_str(filename);
			if (!in_str.good()) 
			{
        std::cerr << "Can't open " << user_input << " to read." << std::endl;
        exit(1);
      }
			std::string temp;
			while(in_str)
			{
				in_str >> temp;
				genome += temp;
			}
		}
		//find the table size
		else if (user_input == "table_size")
		{
			std::cin >> user_input;
			table_size = std::stoi(user_input);

		}
		//if there is occcupancy
		else if (user_input == "occupancy")
		{
			std::cin >> user_input;
			occupancy = std::stof(user_input);
		}
		//finding the kmer
		else if (user_input == "kmer")
		{
			std::cin >> user_input;
			k = std::stoi(user_input);

		}
		//finding the query
		else if (user_input == "query")
		{

			//We push back all of the queries to a vector to make outputting all
			//of the matches easier
			std::cin >> user_input;
			mismatches = std::stoi(user_input);
			std::cin >> user_input;
			query_string = user_input;
			queries.push_back(std::make_pair(query_string, mismatches));
			
		}
		else if (user_input == "quit")
		{
			break;
		}
	}

	//We create the actual hash map with the given parameters, feed in the entire genome,
	//and then go through the list of queries using the find_matches function
	kmer_map<hash_string_obj> kmers(table_size, k, occupancy);
	kmers.populate_map(genome);
	for(unsigned int i = 0; i < queries.size(); i++)
	{
		std::cout << "Query: " << queries[i].first << std::endl;
		find_matches(queries[i].first, queries[i].second, kmers, k, genome);
	}
}


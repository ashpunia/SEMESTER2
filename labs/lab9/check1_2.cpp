#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    string s;
    map<int, int> counters;
    std::map<int, int>::iterator it;

    // check 2

    int array[11] = {19, 83, -12, 83, 65, 19, 45, -12, 45, 19, 45};

    for (int i=0; i<12; i++)
    {
        it = counters.find(array[i]); 
        if (it != counters.end())
        {
            it->second = it->second +1;
        }
        else
        {
            counters.insert(counters.begin(), std::pair<int, int>(array[i], 0)); 
        }
    }

    int largest = 0;
    int max = 0; 

    for (it = counters.begin(); it != counters.end(); it++)
    {
        if(it->second > max)
        {
            max = it->second;
            largest = it->first; 
        }
    }

    for (it = counters.begin(); it != counters.end(); it++)
    {
        if (it->second == max)
        {
            std::cout << it->first << std::endl; 
        }
    }

    return 0;
}


#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    string s;
    int s1;
    map<int, int> counters;
    
    // check 1
    //nlog(n)
    while(cin >> s) {
        if(s == "stop")
        {
            break;
        }
        else
        {
            s1 = stoi(s);
            ++counters[s1];
            //inserting(finding in a map): log(n)
        }
        
    }
    
    int mode = 0;
    map<int, int>::iterator it;
    for( it = counters.begin(); it != counters.end(); it++) {
        if(it->second > mode) {
            mode = it->second;
        }
    }
    
    for( it = counters.begin(); it != counters.end(); it++) {
        if(it->second == mode) {
            cout << it->first << ' ';
        }
    }
    cout << endl;    
    return 0;
}

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std;

int getLoopPosition( vector<int>& );
int getMaxValuePosition( vector<int>& );
string toString( const vector<int>& );

int main( void ) {
    vector<int> mem_banks;
    istringstream iss;
    string input;
    int tmp;

    getline( cin, input );
    iss.str( input );
    while( iss >> tmp ){
        mem_banks.push_back( tmp );
    }
    cout << getLoopPosition( mem_banks ) << endl;

    return EXIT_SUCCESS;
}

int getLoopPosition( vector<int>& mem_banks ) {
    unordered_set<string> mem_configs;
    int max_val_idx, blocks, idx;
    int cycles = 0;
 
    while( true ) {
        max_val_idx = getMaxValuePosition( mem_banks );
        if( mem_configs.insert( toString( mem_banks ) ).second == false )
            break;
        blocks = mem_banks[max_val_idx];
        mem_banks[max_val_idx] = 0;
        idx = max_val_idx + 1;
        while( blocks > 0 ) {
            if( idx == mem_banks.size() )
                idx = 0;
            mem_banks[idx] += 1;
            --blocks;
            ++idx;
        }
        ++cycles;
    }
    return cycles;
}

int getMaxValuePosition( vector<int>& mem_banks ) {
    int max_val_idx, max_val = -1;
    for( unsigned int i = 0; i < mem_banks.size(); ++i ) {
        if( mem_banks[i] > max_val ) {
            max_val_idx = i;
            max_val = mem_banks[i];
        }
    }
    return max_val_idx;
}

string toString( const vector<int>& mem_banks ) {
    ostringstream oss;
    for( unsigned int i = 0; i < mem_banks.size(); ++i )
        oss << mem_banks[i] << '-';
    return oss.str();
}   
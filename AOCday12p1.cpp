#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> getGroup( string& );
void addGroup( unordered_set<int>&, const vector< vector<int> >&, const int& );

int main( void ) {
    vector<vector<int>> program_set;
    unordered_set<int> program_group;
    string input;

    program_group.insert( 0 );
    while( getline( cin, input ) ) {
        program_set.push_back( getGroup( input ) );
        if( program_group.find( program_set.size() - 1 ) != program_group.end() )
            addGroup( program_group, program_set, program_set.size() - 1 );
    }
    cout << program_group.size() << endl;

    return EXIT_SUCCESS; 
}

vector<int> getGroup( string& input ) {
    vector<int> group;
    istringstream iss;
    int tmp;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] == '<' || input[i] == '-' || input[i] == '>' || input[i] == ',' ) {
            input[i] = ' ';
        }
    }
    iss.str( input );
    iss >> tmp; //remove first number
    while( iss >> tmp ) {
        group.push_back( tmp );
    }
    return group;
}

void addGroup( unordered_set<int>& program_group, 
               const vector< vector<int> >& program_set,
               const int& program_id ) {
    if( program_id < program_set.size() ) {
        for( unsigned int i = 0; i < program_set[program_id].size(); ++i ) {
            if( program_group.find( program_set[program_id][i] ) == program_group.end() ) {
                program_group.insert( program_set[program_id][i] );
                addGroup( program_group, program_set, program_set[program_id][i] );
            }
        }
    }
}
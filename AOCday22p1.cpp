#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, bool> getInfectionMap( const vector<string>& );
string posToSring( const int&, const int& );
int getInfectionCount( unordered_map<string, bool>&, const int& );
char getRightDir( const char& );
char getleftDir( const char& );
pair<int, int> getNextMove( const char& );

int main( void ) {
    unordered_map<string, bool> infection_map;
    vector<string> grid;
    string input;

    while( cin >> input ) {
        grid.push_back( input );
    }
    infection_map = getInfectionMap( grid );
    cout << getInfectionCount( infection_map, 10000 ) << endl;

    return EXIT_SUCCESS; 
}

unordered_map<string, bool> getInfectionMap( const vector<string>& grid ) {
    unordered_map<string, bool> i_map;
    for( unsigned int row = 0; row < grid.size(); ++row ) {
        for( unsigned int col = 0; col < grid[row].size(); ++col ) {
            if( grid[row][col] == '#' )
                i_map[posToSring( row, col )] = true;
        }
    }
    return i_map;
}

string posToSring( const int& row, const int& col ) {
    ostringstream oss;
    oss << row;
    oss << col;
    return oss.str();
}

int getInfectionCount( unordered_map<string, bool>& infection_map, const int& bursts ) {
    char dir = 'u';
    int row, col;
    int inf_count = 0;    
    row = col = 12;
    for( int b = 0; b < bursts; ++b ) {
        string pos_str = posToSring( row, col );
        if( infection_map.find( pos_str ) != infection_map.end() &&
            infection_map[pos_str] ) {
            dir = getRightDir( dir );
            infection_map[pos_str] = false;
        }
        else {
            dir = getleftDir( dir );
            infection_map[pos_str] = true;
            ++inf_count;
        }
        pair<int, int> move = getNextMove( dir );
        row += move.first;
        col += move.second;
    }
    return inf_count;
}

char getRightDir( const char& dir ) {
    switch( dir ) {
        case 'u': return 'r';
        case 'r': return 'd';
        case 'd': return 'l';
        case 'l': return 'u';
    }
    return '-';
}

char getleftDir( const char& dir ) {
    switch( dir ) {
        case 'u': return 'l';
        case 'l': return 'd';
        case 'd': return 'r';
        case 'r': return 'u';
    }
    return '-';
}

pair<int, int> getNextMove( const char& dir ) {
    switch( dir ) {
        case 'u': return make_pair( -1, 0 );
        case 'l': return make_pair( 0, -1 );
        case 'd': return make_pair( 1, 0 );
        case 'r': return make_pair( 0, 1 );
    }
    return make_pair( 0, 0 );
}
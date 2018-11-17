#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> getGrid( void );
int getStartingPosition( const string& );
int traverseMaze( vector<string>&, const int&, const int& );
pair<int, int> getNewDirection( const vector<string>&, const int&, const int& );

int main( void ) {
    vector<string> grid;
    int x, y;

    grid = getGrid();
    x = getStartingPosition( grid[0] );
    y = 0;
    cout << traverseMaze( grid, x, y ) << endl;

    return EXIT_SUCCESS; 
}

vector<string> getGrid( void ) {
    vector<string> grid;
    string line;
    while( getline( cin, line ) ) {
        grid.push_back( line );
    }
    return grid;
}

int getStartingPosition( const string& row ) {
    for( unsigned int i = 0; i < row.size(); ++i )
        if( row[i] == '|' )
            return i;
    return 0;
}

int traverseMaze( vector<string>& grid, const int& x, const int& y ) {
    pair<int, int> increments( 0, 1 ); //bootstrap
    int steps = 1;
    int x_pos = x;
    int y_pos = y;
    while( true ) {
        if( grid[y_pos][x_pos] == '+' )
            increments = getNewDirection( grid, x_pos, y_pos );
        if( x_pos + increments.first >= grid[y_pos].size() ||
            x_pos + increments.first < 0 ||
            grid[y_pos][x_pos + increments.first] == ' ' )
            break;
        if( y_pos + increments.second >= grid.size() ||
            y_pos + increments.second < 0 ||
            grid[y_pos + increments.second][x_pos] == ' ' )
            break;
        grid[y_pos][x_pos] = '#';
        x_pos += increments.first;
        y_pos += increments.second;
        steps += 1;
    }
    return steps;
}

pair<int, int> getNewDirection( const vector<string>& grid, const int& x_pos, const int& y_pos ) {
    if( x_pos + 1 < grid[y_pos].size() && grid[y_pos][x_pos + 1] != ' ' && grid[y_pos][x_pos + 1] != '#' )
        return make_pair( 1, 0 );
    if( x_pos - 1 >= 0 && grid[y_pos][x_pos - 1] != ' ' && grid[y_pos][x_pos - 1] != '#' )
        return make_pair( -1, 0 );
    if( y_pos + 1 < grid.size() && grid[y_pos + 1][x_pos] != ' ' && grid[y_pos + 1][x_pos] != '#' )
        return make_pair( 0, 1 );
    if( y_pos - 1 >= 0 && grid[y_pos - 1][x_pos] != ' ' && grid[y_pos - 1][x_pos] != '#' )
        return make_pair( 0, -1 );
}
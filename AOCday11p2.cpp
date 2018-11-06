#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split( string& );
int absVal( const int& );
int maxVal( const int&, const int&, const int& );

int main( void ) {
    vector<string> instructions;
    string input;
    int x, y, z, max, tmp;

    cin >> input;
    instructions = split( input );
    x = y = z = max = 0;
    for( unsigned int i = 0; i < instructions.size(); ++i ) {
        if( instructions[i] == "n" ){
            y += 1;
            z += 1;
        }
        else if( instructions[i] == "ne" ){
            z += 1;
            x += 1;
        }
        else if( instructions[i] == "se" ){
            y -= 1;
            x += 1;
        }
        else if( instructions[i] == "s" ){
            z -= 1;
            y -= 1;
        }
        else if( instructions[i] == "sw" ){
            z -= 1;
            x -= 1;
        }
        else { //nw
            y += 1;
            x -= 1;
        }
        tmp = maxVal( absVal( x ), absVal( y ), absVal( z ) );
        if( tmp > max )
            max = tmp;
    }
    cout <<  max << endl;

    return EXIT_SUCCESS; 
}

vector<string> split( string& input ) {
    vector<string> list;
    istringstream iss;
    string tmp;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] == ',' ) {
            input[i] = ' ';
        }
    }
    iss.str( input );
    while( iss >> tmp ) {
        list.push_back( tmp );
    }
    return list;
}

int absVal( const int& val ) {
    return val >= 0 ? val : val * -1; 
}

int maxVal( const int& val1, const int& val2, const int& val3 ){
    if( val1 > val2 )
        return val1 > val3 ? val1 : val3;
    else
        return val2 > val3 ? val2 : val3;
}
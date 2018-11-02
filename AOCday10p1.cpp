#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> split( string& );
void reverseSection( vector<int>&, int, int, int );

int main( void ) {
    string input;
    vector<int> lengths;
    vector<int> numbers;
    int curr_pos, skip;

    cin >> input;
    lengths = split( input );
    for( int n = 0; n < 256; ++n )
        numbers.push_back( n );
    curr_pos = skip = 0;
    for( unsigned int i = 0; i < lengths.size(); ++i  ){
        int end, moves;
        if( curr_pos + (lengths[i] - 1) >= numbers.size() )
            end = (curr_pos + (lengths[i] - 1)) - numbers.size();
        else
            end = curr_pos + (lengths[i] - 1);
        moves = lengths[i] / 2;
        reverseSection( numbers, curr_pos, end, moves );
        if( (curr_pos + lengths[i] + skip) >= numbers.size() )
            curr_pos = (curr_pos + lengths[i] + skip) - numbers.size();
        else
            curr_pos += lengths[i] + skip;
        skip += 1;
    }
    cout << (numbers[0] * numbers[1]) << endl;

    return EXIT_SUCCESS; 
}

vector<int> split( string& input ){
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] == ',' )
            input[i] = ' ';
    }
    istringstream iss( input );
    vector<int> items;
    int tmp;
    while( iss >> tmp ) {
        items.push_back( tmp );
    }
    return items;
}

void reverseSection( vector<int>& numbers, int start, int end, int moves ) {
    int tmp;
    while( moves > 0 ) {
        tmp = numbers[start];
        numbers[start] = numbers[end];
        numbers[end] = tmp;
        if( ++start >= numbers.size() )
            start = 0;
        if( --end < 0 )
            end = numbers.size() - 1;
        --moves;
    }
}
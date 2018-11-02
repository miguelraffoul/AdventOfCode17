#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> toASCIIArray( string& );
void reverseSection( vector<int>&, int, int, int );
string getDenseHash( const vector<int>& );

int main( void ) {
    string input;
    vector<int> lengths;
    vector<int> numbers;
    int curr_pos, skip, rounds;

    cin >> input;
    lengths = toASCIIArray( input );
    for( int n = 0; n < 256; ++n )
        numbers.push_back( n );
    curr_pos = skip = rounds = 0;
    while( rounds < 64 ) {
        for( unsigned int i = 0; i < lengths.size(); ++i  ){
            int end, moves, multi;
            if( curr_pos + (lengths[i] - 1) >= numbers.size() )
                end = (curr_pos + (lengths[i] - 1)) - numbers.size();
            else
                end = curr_pos + (lengths[i] - 1);
            moves = lengths[i] / 2;
            reverseSection( numbers, curr_pos, end, moves );
            if( (curr_pos + lengths[i] + skip) >= numbers.size() ) {
                multi = (curr_pos + lengths[i] + skip) / numbers.size();
                curr_pos = (curr_pos + lengths[i] + skip) - (numbers.size() * multi);
            }
            else
                curr_pos += lengths[i] + skip;
            skip += 1;
        }
        ++rounds;
    }
    cout << getDenseHash( numbers ) << endl;

    return EXIT_SUCCESS; 
}

vector<int> toASCIIArray( string& input ){
    vector<int> items;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        items.push_back( (int)input[i] );
    }
    items.push_back( 17 );
    items.push_back( 31 );
    items.push_back( 73 );
    items.push_back( 47 );
    items.push_back( 23 );
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

string getDenseHash( const vector<int>& numbers ) {
    vector<int> dense_hash;
    int tmp, idx;
    for( int i = 0; i < 16; ++i ) {
        tmp = 0;
        idx = 16 * i;
        for( int j = 0; j < 16; ++j ) {
            tmp ^= numbers[idx + j];
        }
        dense_hash.push_back( tmp );
    }
    ostringstream oss;
    for( unsigned int i = 0; i < dense_hash.size(); ++i )
        oss << std::setw( 2 ) << std::setfill( '0' ) << std::hex << dense_hash[i];
    return oss.str();
}
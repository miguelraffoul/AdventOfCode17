#include <bitset>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> knotHash( string& );
vector<int> toASCIIArray( string& );
vector<int> getSparseHash( const vector<int>& );
void reverseSection( vector<int>&, int, int, int );
vector<int> getDenseHash( const vector<int>& );
string toString( const int& );
void markRegion( vector<string>&, const int&, const int& );

int main( void ) {
    vector<string> grid;
    int region_counter;
    string input;
    
    cin >> input;
    for( int rownum = 0; rownum < 128; ++rownum ){
        string row_key = input + '-' + toString( rownum );
        vector<int> row_hash =  knotHash( row_key );
        string row;
        for( unsigned int i = 0; i < row_hash.size(); ++i ){
            bitset<8> hex_bits( row_hash[i] );
            row += hex_bits.to_string();
        }
        grid.push_back( row );
    }
    region_counter = 0;
    for( unsigned int i = 0; i < grid.size(); ++i ) {
        for( unsigned int j = 0; j < grid[i].size(); ++j ) {
            if( grid[i][j] == '1' ) {
                markRegion( grid, i, j );
                ++region_counter;
            }
        }
    }
    cout << region_counter << endl;

    return EXIT_SUCCESS; 
}

vector<int> knotHash( string& input ) {
    vector<int> lengths = toASCIIArray( input );
    vector<int> sparse_hash = getSparseHash( lengths );
    vector<int> dense_hash = getDenseHash( sparse_hash );
    return dense_hash;
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

vector<int> getSparseHash( const vector<int>& lengths ) {
    vector<int> numbers;
    int curr_pos, skip, rounds;
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
    return numbers;
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

vector<int> getDenseHash( const vector<int>& numbers ) {
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
    return dense_hash;
}

string toString( const int& rownum ) {
    ostringstream oss;
    oss << rownum;
    return oss.str();
}

void markRegion( vector<string>& grid, const int& i, const int& j ) {
    grid[i][j] = 'x';
    if( i > 0 && grid[i - 1][j] == '1' )
        markRegion( grid, i - 1, j );
    if( j > 0 && grid[i][j - 1] == '1' )
        markRegion( grid, i, j - 1 );
    if( i < (grid.size() - 1)&& grid[i + 1][j] == '1'  )
        markRegion( grid, i + 1, j );
    if( j < (grid[i].size() - 1)  && grid[i][j + 1] == '1'  )
        markRegion( grid, i, j + 1 );
}
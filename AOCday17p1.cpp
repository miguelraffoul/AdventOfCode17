#include <cstdlib>
#include <deque>
#include <iostream>

using namespace std;

int main( void ) {
    deque<int> buffer;
    int jumps, values;
    int curr_pos;

    cin >> jumps >> values;
    buffer.push_back( 0 );
    curr_pos = 0;
    for( int i = 1; i <= values; ++i ) {
        if( (curr_pos + jumps) >= buffer.size() )
            curr_pos = (curr_pos + jumps) % buffer.size();
        else
            curr_pos = curr_pos + jumps;
        buffer.insert( buffer.begin() + (curr_pos + 1), i );
        curr_pos += 1;
    }
    if( curr_pos + 1 == buffer.size() )
        cout << buffer[0] << endl;
    else
        cout << buffer[curr_pos + 1] << endl;

    return EXIT_SUCCESS; 
}

#include <cstdlib>
#include <iostream>

using namespace std;

int main( void ) {
    int buffer, jumps, values;
    int curr_pos;

    cin >> jumps >> values;
    curr_pos = 0;
    for( int i = 1; i <= values; ++i ) {
        if( (curr_pos + jumps) >= i )
            curr_pos = (curr_pos + jumps) % i;
        else
            curr_pos = curr_pos + jumps;
        curr_pos += 1;
        if( curr_pos == 1 )
            buffer = i;
    }
    cout << buffer << endl;

    return EXIT_SUCCESS; 
}

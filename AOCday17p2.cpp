#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

int main( void ) {
    stack<int> buffer;
    int jumps, values;
    int curr_pos;

    cin >> jumps >> values;
    buffer.push( 0 );
    curr_pos = 0;
    for( int i = 1; i <= values; ++i ) {
        if( (curr_pos + jumps) >= i )
            curr_pos = (curr_pos + jumps) % i;
        else
            curr_pos = curr_pos + jumps;
        curr_pos += 1;
        if( curr_pos == 1 )
            buffer.push( i );
    }
    cout << buffer.top() << endl;

    return EXIT_SUCCESS; 
}

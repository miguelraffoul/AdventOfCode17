#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

pair<int, int> getLayer( string& );

int main( void ) {
    string input;
    int severity_sum;

    severity_sum = 0;
    while( getline( cin, input ) ) {
        pair<int, int> layer = getLayer( input );
        if( layer.first % ((layer.second * 2) - 2) == 0 ){
            severity_sum += layer.first * layer.second;
        }
    }
    cout << severity_sum << endl;

    return EXIT_SUCCESS; 
}

pair<int, int> getLayer( string& input ) {
    istringstream iss;
    int depth, range;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] == ':' ) {
            input[i] = ' ';
        }
    }
    iss.str( input );
    iss >> depth;
    iss >> range;
    return make_pair( depth, range );
}

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

pair<int, int> getLayer( string& );

int main( void ) {
    vector<pair<int, int> > firewall;
    string input;
    int delay;

    while( getline( cin, input ) ) {
        pair<int, int> layer = getLayer( input );
        firewall.push_back( layer );
    }
    //brute force :c
    delay = 0;
    while( ++delay ) {
        bool detected = false;
        for( unsigned int i = 0; i < firewall.size(); ++i ) {
            if( (firewall[i].first + delay) % ((firewall[i].second * 2) - 2) == 0 ){
                detected = true;
            }
        }
        if( !detected )
            break;
    }
    cout << delay << endl;

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

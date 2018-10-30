#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getScore( const string& );

int main( void ) {
    string input;
    
    cin >> input;
    cout << getScore( input ) << endl;

    return EXIT_SUCCESS;
}

int getScore( const string& input ) {
    vector<char> groups;
    int score = 0;
    bool is_trash = false;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( is_trash == false ) {
            if( input[i] == '!' )
                ++i;
            else if( input[i] == '<' )
                is_trash = true;
            else if( input[i] == '{' ) 
                groups.push_back( input[i] );
            else if ( input[i] == '}' ) {
                score += groups.size();
                groups.pop_back();
            }
        }
        else {
            if( input[i] == '!' )
                ++i;
            else if( input[i] == '>' )
                is_trash = false;
        }
    }
    return score;
}

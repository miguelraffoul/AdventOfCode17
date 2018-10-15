#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

int main( void ) {
    string passphrase;
    int valid_count = 0;

    while( getline( cin, passphrase ) ) {
        istringstream iss( passphrase );
        unordered_set<string> words;
        bool valid_passphrase = true;
        string word;

        while( iss >> word ) {
            if( words.insert( word ).second == false ) {
                valid_passphrase = false;
                break;
            }
        }
        if( valid_passphrase )
            ++valid_count;
    }
    cout << valid_count << endl;

    return EXIT_SUCCESS;
}

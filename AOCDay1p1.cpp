#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main( void ) {
    string input;
    int digit_sum;
    
    cin >> input;
    digit_sum = 0;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        int next_digit = i == (input.size() - 1) ? 0 : (i + 1);
        if( input[i] == input[next_digit] ) {
            digit_sum += input[next_digit] - '0';
        }
    }
    cout << digit_sum << endl;

    return EXIT_SUCCESS;
}
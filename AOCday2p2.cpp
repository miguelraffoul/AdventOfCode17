#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int main( void ) {
    string row;
    int checksum;

    checksum = 0;
    while( getline( cin,  row ) ) {
        istringstream iss( row );
        vector<int> numbers;
        bool continue_flg;
        int tmp;
        
        continue_flg = true;
        while( continue_flg ) {
            iss >> tmp;
            for( unsigned int i = 0; i < numbers.size(); ++i ) {
                if( tmp % numbers[i] == 0 ) {
                    checksum += tmp / numbers[i];
                    continue_flg = false;
                    break;
                }
                if( numbers[i] % tmp == 0 ) {
                    checksum += numbers[i] / tmp;
                    continue_flg = false;   
                    break;
                }
            }
            numbers.push_back( tmp );
        }
    }
    cout << checksum << endl;

    return EXIT_SUCCESS;
}

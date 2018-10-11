#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main( void ) {
	string row;
	int checksum;

	checksum = 0;
	while( getline( cin,  row ) ) {
		istringstream iss( row );
		int min, max, tmp;
		
		iss >> tmp;
		min = max = tmp;
		while( iss >> tmp ) {
			if( tmp > max )
				max = tmp;
			if( tmp < min )
				min = tmp;
		}
		checksum += max - min;
	}
	cout << checksum << endl;

	return EXIT_SUCCESS;
}

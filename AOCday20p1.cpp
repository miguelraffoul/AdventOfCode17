#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<double> getParticle( string& );
double pow2( const double& );

int main( void ) {
    vector<double> particle;
    string input;
    double min_acc, tmp_acc;
    int min_id, p_id;

    p_id = 0;
    while( getline( cin, input ) ) {
        particle = getParticle( input );
        tmp_acc = sqrt( pow2( particle[6] ) + pow2( particle[7] ) + pow2( particle[8] ) );
        if( p_id == 0 ) {
            min_id = 0;
            min_acc = tmp_acc;
        }
        if( tmp_acc < min_acc ) {
            min_acc = tmp_acc;
            min_id = p_id;
        }
        ++p_id;
    }
    cout << min_id << ": " << min_acc << endl;

    return EXIT_SUCCESS; 
}

vector<double> getParticle( string& input ) {
    vector<double> particle;
    istringstream iss;
    double tmp;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] == 'p' || input[i] == 'v' || input[i] == 'a' ||
            input[i] == '=' || input[i] == '<' || input[i] == '>' ||
            input[i] == ',' )
            input[i] = ' ';
    }
    iss.str( input );
    while( iss >> tmp ) {
        particle.push_back( tmp );
    }
    return particle;
}

double pow2( const double& acc ) {
    return acc * acc;
}
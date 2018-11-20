#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> getParticle( string& );
int getCollisionCount( vector< vector<int> >&, const int& );
void updateSpeed( vector<int>& );
void updatePosition( vector<int>& );
string posToString( const vector<int>& );

int main( void ) {
    vector< vector<int> > particles;
    string input;

    while( getline( cin, input ) ) {
        particles.push_back( getParticle( input ) );
    }
    cout << (particles.size() - getCollisionCount( particles, 1000 )) << endl;

    return EXIT_SUCCESS; 
}

vector<int> getParticle( string& input ) {
    vector<int> particle;
    istringstream iss;
    int tmp;
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

int getCollisionCount( vector< vector<int> >& particles, const int& interations ) {
    vector<bool> collisions_detected( particles.size(), false );
    int collision_count = 0;
    for( int it = 1; it <= interations; ++ it ) {
        unordered_map<string, int> positions_table;
        pair<unordered_map<string, int>::iterator, bool> tmp_pair;
        string pos_str;
        for( unsigned int p = 0; p < particles.size(); ++p ) {
            if( !collisions_detected[p] ) {
                updateSpeed( particles[p] );
                updatePosition( particles[p] );
                pos_str = posToString( particles[p] );
                tmp_pair = positions_table.insert( make_pair( pos_str, p ) );
                if( !tmp_pair.second ) {
                    if( !collisions_detected[tmp_pair.first->second] ) {
                        collisions_detected[tmp_pair.first->second] = true;
                        ++collision_count;
                    }
                    collisions_detected[p] = true; 
                    ++collision_count;
                }
            }
        }
    }
    return collision_count;
}

void updateSpeed( vector<int>& particle ) {
    particle[3] += particle[6];
    particle[4] += particle[7];
    particle[5] += particle[8];
}

void updatePosition( vector<int>& particle ) {
    particle[0] += particle[3];
    particle[1] += particle[4];
    particle[2] += particle[5];
}

string posToString( const vector<int>& particle ) {
    ostringstream oss;
    oss << particle[0];
    oss << particle[1];
    oss << particle[2];
    return oss.str();
}
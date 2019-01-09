#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map< int, vector<int> > conn_type_index;
vector< pair<int, int> > connectors;
vector<bool> used_conn;
vector< pair<int, int> > conn_stack;

void parseInput( void );
int getStrongestCombination( const int );
void printConnectorStack( void );

int main( void ) {
    parseInput();
    cout << getStrongestCombination( 0 ) << endl;

    return EXIT_SUCCESS;
}

void parseInput( void ) {
    int tmp1, tmp2, conn_id;
    string input;
    conn_id = 0;
    while( cin >> input ) {
        for( unsigned int i = 0; i < input.size(); ++i ) {
            if( input[i] == '/' )
                input[i] = ' ';
        }
        istringstream iss( input );
        iss >> tmp1 >> tmp2;
        connectors.push_back( make_pair( tmp1, tmp2 ) );
        used_conn.push_back( false );
        if( tmp1 != tmp2 ) {
            conn_type_index[tmp1].push_back( conn_id );
            conn_type_index[tmp2].push_back( conn_id );
        }
        else {
            conn_type_index[tmp1].push_back( conn_id );
        }
        ++conn_id;
    }
}

int getStrongestCombination( const int lead ) {
    vector<int> available_options;
    int strogest_build, tmp_build;
    pair<int, int> tmp_connector;
    available_options = conn_type_index[lead];
    strogest_build = 0;
    for( unsigned int i = 0; i < available_options.size(); ++i ) {
        if( used_conn[available_options[i]] == false ) {
            used_conn[available_options[i]] = true;
            tmp_connector = connectors[available_options[i]];
            //conn_stack.push_back( tmp_connector );
            //printConnectorStack();
            if( tmp_connector.first == lead )
                tmp_build = getStrongestCombination( tmp_connector.second );
            else
                tmp_build = getStrongestCombination( tmp_connector.first );
            if( tmp_build + tmp_connector.first + tmp_connector.second > strogest_build )
                strogest_build = tmp_build + tmp_connector.first + tmp_connector.second;
            //conn_stack.pop_back();
            used_conn[available_options[i]] = false;
        }
    }
    return strogest_build;
}

void printConnectorStack( void ) {
    int sum = 0;
    for( unsigned int c = 0; c < conn_stack.size(); ++c ) {
        cout << conn_stack[c].first << "/" << conn_stack[c].second << "--";
        sum += conn_stack[c].first + conn_stack[c].second;
    }
    cout << "(" << sum << ")" << endl;
}
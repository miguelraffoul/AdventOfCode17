#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> split( string& );
void initialize( unordered_map<char, int>&, string& );
int getSpin( string );
int absVal( const int& );
int getOffsetPosition( const int&, const int&, const int& );
void swapByIndex( unordered_map<char, int>&, string&, string, const int& );
void swapByChar( unordered_map<char, int>&, string&, string );
string applyOffset( const unordered_map<char, int>&, const int& );


int main( void ) {
    unordered_map<string, int> prog_config;
    unordered_map<char, int> prog_positions;
    string input, prog_list, tmp;
    vector<string> instructions;
    int offset, target;

    cin >> input;
    instructions = split( input );
    initialize( prog_positions, prog_list );
    prog_config[prog_list] = 0;
    offset = 0;
    for( unsigned int iter = 1; true; ++iter ) {
        for( unsigned int i = 0; i < instructions.size(); ++i ) {
            switch( instructions[i][0] ) {
                case 's':
                    offset += getSpin( instructions[i] );
                    offset = offset >= prog_list.size() ? offset % prog_list.size() : offset;
                    break;
                case 'x':
                    swapByIndex( prog_positions, prog_list, instructions[i], offset );
                    break;
                case 'p':
                    swapByChar( prog_positions, prog_list, instructions[i] );
                    break;
            }
        }
        tmp = applyOffset( prog_positions, offset ); 
        if( prog_config.find( tmp ) != prog_config.end() ) {
            target =  999999999 % iter;
            for( auto it = prog_config.begin(); it != prog_config.end(); ++it ){
                if( it->second == target )
                    cout << it->first << endl;
            }
            break;
        }
        else
            prog_config[tmp] = iter;
    }
    
    return EXIT_SUCCESS; 
}

vector<string> split( string& input ) {
    vector<string> instructions;
    istringstream iss;
    string tmp;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] == ',' )
            input[i] = ' ';
    }
    iss.str( input );
    while( iss >> tmp ) {
        instructions.push_back( tmp );
    }
    return instructions;
}

void initialize( unordered_map<char, int>& prog_positions, string& prog_list ) {
    prog_list = "cgpfhdnambekjiol";
    for( unsigned int i = 0; i < prog_list.size(); ++i ) {
        prog_positions[prog_list[i]] = i;
    }
}

int getSpin( string instruction ) {
    instruction[0] = ' ';
    return stoi( instruction );
}

int absVal( const int& val ) {
    return val >= 0 ? val : val * -1; 
}

int getOffsetPosition( const int& pos, const int& offset, const int& size ) {
    if( pos - offset >= 0 )
        return pos - offset;
    else
        return size - (absVal( pos - offset ) % size);
}

void swapByIndex( unordered_map<char, int>& prog_positions, string& prog_list, string instruction, const int& offset ) {
    istringstream iss;
    int pos1, pos2;
    char tmp_char;
    for( unsigned int i = 0; i < instruction.size(); ++i ) {
        if( instruction[i] == 'x' || instruction[i] == '/' )
            instruction[i] = ' ';
    }
    iss.str( instruction );
    iss >> pos1 >> pos2;
    pos1 = getOffsetPosition( pos1, offset, prog_list.size() );
    pos2 = getOffsetPosition( pos2, offset, prog_list.size() );
    tmp_char = prog_list[pos1];
    prog_list[pos1] = prog_list[pos2];
    prog_list[pos2] = tmp_char;
    prog_positions[prog_list[pos1]] = pos1;
    prog_positions[prog_list[pos2]] = pos2;
}

void swapByChar( unordered_map<char, int>& prog_positions, string& prog_list, string instruction ) {
    int tmp_pos;
    tmp_pos = prog_positions[instruction[1]];
    prog_positions[instruction[1]] = prog_positions[instruction[3]];
    prog_positions[instruction[3]] = tmp_pos;
    prog_list[prog_positions[instruction[1]]] = instruction[1];
    prog_list[prog_positions[instruction[3]]] = instruction[3];
}

string applyOffset( const unordered_map<char, int>& prog_positions, const int& offset ) {
    string new_prog_list = "cgpfhdnambekjiol";
    int new_pos;
    unordered_map<char, int>::const_iterator it;
    for( it = prog_positions.cbegin(); it != prog_positions.cend(); ++it ) {
        if( it->second + offset >= new_prog_list.size() )
            new_pos = (it->second + offset) % new_prog_list.size(); 
        else
            new_pos = it->second + offset;
        new_prog_list[new_pos] = it->first;
    }
    return new_prog_list;
}
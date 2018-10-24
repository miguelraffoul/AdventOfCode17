#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Program {
    string parent;
    string name;
    int weight;
    vector<string> sub_programs;
};

vector<string> split( string& );
struct Program createProgram( const vector<string>& );
void constructTree( vector<struct Program>&, unordered_map<string, int>& );

int main( void ) {
    vector<struct Program> program_list;
    unordered_map<string, int> program_idex;
    string input;
    int index = 0;
    
    while( getline( cin, input ) ) {
        struct Program new_program = createProgram( split( input ) );
        program_list.push_back( new_program );
        program_idex.insert( make_pair<string, int>( new_program.name, index ) );
        ++index;
    }
    constructTree( program_list, program_idex );
    for( unsigned int i = 0; i < program_list.size(); ++i ){
        if( program_list[i].parent ==  "*" ) {
            cout << program_list[i].name << endl;
        }
    }


    return EXIT_SUCCESS;
}

vector<string> split( string& input ) {
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] == '(' || input[i] == ')' || 
            input[i] == '-' || input[i] == '>' ||
            input[i] == ',' ) {
            input[i] = ' ';
        }
    }
    istringstream iss( input );
    vector<string> list;
    string tmp;
    while( iss >> tmp ) {
        list.push_back( tmp );
    }
    return list;
}

struct Program createProgram( const vector<string>& list ) {
    struct Program new_program;
    new_program.parent = "*";
    new_program.name = list[0];
    new_program.weight = stoi( list[1] );
    if( list.size() > 2 )
        new_program.sub_programs.insert( new_program.sub_programs.begin(), list.begin() + 2, list.end() );
    return new_program;
}

void constructTree( vector<struct Program>& program_list, unordered_map<string, int>& program_idex ) {
    for( unsigned int i = 0; i < program_list.size(); ++i ) {
        for( unsigned int j = 0; j < program_list[i].sub_programs.size(); ++j ) {
            int child_index = program_idex[program_list[i].sub_programs[j]];
            program_list[child_index].parent = program_list[i].name;
        }
    }
}
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
int traverseTree( const string&, vector<struct Program>&, unordered_map<string, int>& );

int main( void ) {
    vector<struct Program> program_list;
    unordered_map<string, int> program_idex;
    string input, root;
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
            root = program_list[i].name;
        }
    }
    cout << "Total tree weight: " << traverseTree( root, program_list, program_idex) << endl;

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
        new_program.sub_programs.insert( 
            new_program.sub_programs.begin(), 
            list.begin() + 2, 
            list.end() 
        );
    return new_program;
}

void constructTree( vector<struct Program>& program_list, 
                    unordered_map<string, int>& program_idex ) {
    for( unsigned int i = 0; i < program_list.size(); ++i ) {
        for( unsigned int j = 0; j < program_list[i].sub_programs.size(); ++j ) {
            int child_index = program_idex[program_list[i].sub_programs[j]];
            program_list[child_index].parent = program_list[i].name;
        }
    }
}

int traverseTree( const string& name, vector<struct Program>& program_list, 
                  unordered_map<string, int>& program_idex ) {
    struct Program curr_program = program_list[program_idex[name]];
    vector<int> sub_programs_weight;
    int cummulative_wight, tmp;
    cummulative_wight = 0;
    for( unsigned int i = 0; i < curr_program.sub_programs.size(); ++i ) {
        tmp = traverseTree( curr_program.sub_programs[i], program_list, program_idex );
        if( i > 0 && sub_programs_weight.back() != tmp ) {
            cout << "*****Weight difference found*****" << endl;
            cout << "Current program: " << name << endl;
            cout << "Weight in previous sub program (" <<  curr_program.sub_programs[i - 1];
            cout << "): " << sub_programs_weight.back() << endl;
            cout << "Weight in current sub program: (" <<  curr_program.sub_programs[i];
            cout << "): "  << tmp << endl;
        }
        cummulative_wight += tmp;
        sub_programs_weight.push_back( tmp );
    }
    return cummulative_wight + curr_program.weight;
}
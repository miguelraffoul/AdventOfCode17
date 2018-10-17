#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void printInstructions( const vector<int>&, const int& );

int main( void ) {
    vector<int> instructions;
    int tmp, steps, curr_inst, next_inst;

    while( cin >> tmp ) {
        instructions.push_back( tmp );
    }
    steps = 0;
    curr_inst = next_inst = 0;
    while( true ) {
        curr_inst = next_inst;
        //printInstructions( instructions, curr_inst );
        next_inst = curr_inst + instructions[curr_inst];
        if( instructions[curr_inst] >= 3 )
            instructions[curr_inst] -= 1;
        else 
            instructions[curr_inst] += 1;
        ++steps;
        if( next_inst >= instructions.size() )
            break;
    }
    cout << steps << endl;

    return EXIT_SUCCESS;
}

void printInstructions( const vector<int>& instructions, const int& curr_inst ) {
    for( unsigned int i = 0; i < instructions.size(); ++i ) {
        if( i == curr_inst )
            cout << instructions[i] << "*  ";
        else
            cout << instructions[i] << "  ";
    }
    cout << endl;
}
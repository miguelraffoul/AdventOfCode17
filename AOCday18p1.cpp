#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> parseInstruction( string& );
void processInstructions( const vector<vector<string> >& );
int getInstructionMap( const string& );
int getValue( const unordered_map<string, long long int>&, const string& );
bool isRegister( const string& );

int main( void ) {
    vector<vector<string> > instructions;
    string input;

    while( getline( cin, input ) ) {
        instructions.push_back( parseInstruction( input ) );
    }
    processInstructions( instructions );

    return EXIT_SUCCESS; 
}

vector<string> parseInstruction( string& input ) {
    istringstream iss( input );
    vector<string> instruction;
    string tmp;
    while( iss >> tmp ) {
        instruction.push_back( tmp );
    }
    return instruction;
}

void processInstructions( const vector<vector<string> >& instructions ) {
    unordered_map<string, long long int> registers;
    string instruction, reg, value;
    int buffer, curr_inst = 0;
    bool stop_flag = false;
    while( !stop_flag ) {
        instruction = instructions[curr_inst][0];
        reg = instructions[curr_inst][1];
        value = instructions[curr_inst].size() > 2 ? instructions[curr_inst][2] : "0";
        if( isRegister( reg ) && registers.find( reg ) == registers.end() )
            registers[reg] = 0;
        switch( getInstructionMap( instruction ) ) {
            case 1:
                buffer = registers[reg];
                ++curr_inst;
                break;
            case 2:
                registers[reg] = getValue( registers, value );
                ++curr_inst;
                break;
            case 3:
                registers[reg] = registers[reg] + getValue( registers, value );
                ++curr_inst;
                break;
            case 4:
                registers[reg] = registers[reg] * getValue( registers, value );
                ++curr_inst;
                break;
            case 5:
                registers[reg] = registers[reg] % getValue( registers, value );
                ++curr_inst;
                break;
            case 6:
                if( registers[reg] != 0 ) {
                    cout << buffer << endl;
                    stop_flag = true;
                }
                ++curr_inst;
                break;
            case 7:
                if( isRegister( reg ) ) {
                    if( registers[reg] > 0 ) 
                        curr_inst += getValue( registers, value );
                    else
                        ++curr_inst; 
                }
                else {
                    if( getValue( registers, reg ) > 0 )
                        curr_inst += getValue( registers, value );
                    else
                        ++curr_inst;
                }
                break;
        }
    }
}

int getInstructionMap( const string& instruction ) {
    if( instruction == "snd" )
        return 1;
    if( instruction == "set" )
        return 2;
    if( instruction == "add" )
        return 3;
    if( instruction == "mul" )
        return 4;
    if( instruction == "mod" )
        return 5;
    if( instruction == "rcv" )
        return 6;
    if( instruction == "jgz" )
        return 7;
}

int getValue( const unordered_map<string, long long int>& registers, const string& value ) {
    if( value[0] >= 'a' && value[0] <= 'z' ) {
        if( registers.find( value ) == registers.end() )
            return 0;
        else 
            return registers.find( value )->second;
    }
    else
        return stoi( value );
}

bool isRegister( const string& reg ) {
    if( reg[0] >= 'a' && reg[0] <= 'z' )
        return true;
    return false;
}
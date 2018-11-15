#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> parseInstruction( string& );
void lauchSessions( const vector<vector<string> >& );
deque<int> processInstructions( const vector<vector<string> >&, unordered_map<string, long long int>&, deque<int>&, int& );
int getInstructionMap( const string& );
int getValue( const unordered_map<string, long long int>&,  const string& );
bool isRegister( const string& );

int main( void ) {
    vector<vector<string> > instructions;
    string input;

    while( getline( cin, input ) ) {
        instructions.push_back( parseInstruction( input ) );
    }
    lauchSessions( instructions );

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

void lauchSessions( const vector<vector<string> >& instructions ) {
    unordered_map<string, long long int> registers0, registers1;
    int curr_inst0, curr_inst1, count0, count1;
    deque<int> buffer0, buffer1;
    registers0["p"] = 0;
    registers1["p"] = 1;
    curr_inst0 = curr_inst1 = count0 = count1 = 0;
    do {
        buffer0 = processInstructions( instructions, registers0, buffer1, curr_inst0 );
        count0 += buffer0.size();
        buffer1 = processInstructions( instructions, registers1, buffer0, curr_inst1 );
        count1 += buffer1.size();
    } while( buffer0.size() > 0 || buffer1.size() > 0 );
    cout << "Thread 0 snd calls: " << count0 <<  endl;
    cout << "Thread 1 snd calls: " << count1 <<  endl;
}

deque<int> processInstructions( 
        const vector<vector<string> >& instructions,
        unordered_map<string, long long int>& registers,
        deque<int>& read_buffer,
        int& curr_inst
    ) {
    string instruction, reg, value;
    deque<int> write_buffer;
    bool stop_flag = false;
    while( !stop_flag ) {
        instruction = instructions[curr_inst][0];
        reg = instructions[curr_inst][1];
        value = instructions[curr_inst].size() > 2 ? instructions[curr_inst][2] : "0";
        if( isRegister( reg ) && registers.find( reg ) == registers.end() )
            registers[reg] = 0;
        switch( getInstructionMap( instruction ) ) {
            case 1:
                write_buffer.push_back( registers[reg] );
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
                if( read_buffer.size() > 0 ) {
                    registers[reg] = read_buffer[0];
                    read_buffer.pop_front();
                    ++curr_inst;
                }
                else {
                    stop_flag = true;
                }
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
    return write_buffer;
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

int getValue( 
        const unordered_map<string, long long int>& registers, 
        const string& value 
    ) {
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
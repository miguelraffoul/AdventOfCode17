#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> split( string& );
void computeIntruction( unordered_map<string, int>&, const vector<string>& );
bool checkCondition( unordered_map<string, int>&, const vector<string>& );

int main( void ) {
    unordered_map<string, int> registers;
    unordered_map<string, int>::iterator it;
    string input;
    int tmp;
    
    while( getline( cin, input ) ) {
        vector<string> instruction = split( input );
        computeIntruction( registers, instruction );
    }
    tmp = registers.begin()->second;
    for( it = registers.begin(); it != registers.end(); ++it ){
        if( it->second > tmp )
            tmp = it->second;
    }
    cout << tmp << endl;

    return EXIT_SUCCESS;
}

vector<string> split( string& input ) {
    istringstream iss( input );
    vector<string> list;
    string tmp;
    while( iss >> tmp ) {
        list.push_back( tmp );
    }
    return list;
}

void computeIntruction( unordered_map<string, int>& registers, const vector<string>& instruction ) {
    if( checkCondition( registers, instruction ) ) {
        if( registers.find( instruction[0] ) == registers.end() )
            registers[instruction[0]] = 0;    

        if( instruction[1] == "inc" )
            registers[instruction[0]] += stoi( instruction[2] );
        else if( instruction[1] == "dec" )
            registers[instruction[0]] -= stoi( instruction[2] );
    }
}

bool checkCondition( unordered_map<string, int>& registers, const vector<string>& instruction ) {
    if( registers.find( instruction[4] ) == registers.end() )
        registers[instruction[4]] = 0;

    if( instruction[5] == "==" )
        return registers[instruction[4]] == stoi( instruction[6] );
    else if( instruction[5] == "!=" )
        return registers[instruction[4]] != stoi( instruction[6] );
    else if( instruction[5] == "<" )
        return registers[instruction[4]] < stoi( instruction[6] );
    else if( instruction[5] == ">" )
        return registers[instruction[4]] > stoi( instruction[6] );
    else if( instruction[5] == "<=" )
        return registers[instruction[4]] <= stoi( instruction[6] );
    else if( instruction[5] == ">=" )
        return registers[instruction[4]] >= stoi( instruction[6] );
    else
        return false;
}
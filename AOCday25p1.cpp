#include <cstdlib>
#include <deque>
#include <iostream>

using namespace std;

int getDiagnosticChecksum( const char&, const int& );
void changeState( deque<char>&, char&, int& );

int main( void ) {
	char initial_state = 'A';
	int steps = 12667664;

	cout << getDiagnosticChecksum( initial_state, steps ) << endl;

	return EXIT_SUCCESS;
}

int getDiagnosticChecksum( const char& initial_state, const int& steps ) {
	char curr_state = initial_state;
	int checksum, curr_pos;
	deque<char> tape;
	checksum = curr_pos = 0;
	tape.push_back( 0 );
	for( int s = 0; s < steps; ++s ) {
		changeState( tape, curr_state, curr_pos );
	}
	for( unsigned int i = 0; i < tape.size(); ++i ) {
		checksum += tape[i];
	}
	return checksum;
}

void changeState( deque<char>& tape, char& curr_state, int& curr_pos ) {
	switch( curr_state ) {
		case 'A':
			if( tape[curr_pos] == 0 ) {
				tape[curr_pos] = 1;
				curr_pos += 1;
				curr_state = 'B';
			}	
			else {
				tape[curr_pos] = 0;
				curr_pos -= 1;
				curr_state = 'C';
			}
			break;
		case 'B':
			if( tape[curr_pos] == 0 ) {
				tape[curr_pos] = 1;
				curr_pos -= 1;
				curr_state = 'A';
			}	
			else {
				tape[curr_pos] = 1;
				curr_pos += 1;
				curr_state = 'D';
			}
			break;
		case 'C':
			if( tape[curr_pos] == 0 ) {
				tape[curr_pos] = 0;
				curr_pos -= 1;
				curr_state = 'B';
			}	
			else {
				tape[curr_pos] = 0;
				curr_pos -= 1;
				curr_state = 'E';
			}
			break;
		case 'D':
			if( tape[curr_pos] == 0 ) {
				tape[curr_pos] = 1;
				curr_pos += 1;
				curr_state = 'A';
			}	
			else {
				tape[curr_pos] = 0;
				curr_pos += 1;
				curr_state = 'B';
			}
			break;
		case 'E':
			if( tape[curr_pos] == 0 ) {
				tape[curr_pos] = 1;
				curr_pos -= 1;
				curr_state = 'F';
			}	
			else {
				tape[curr_pos] = 1;
				curr_pos -= 1;
				curr_state = 'C';
			}
			break;
		case 'F':
			if( tape[curr_pos] == 0 ) {
				tape[curr_pos] = 1;
				curr_pos += 1;
				curr_state = 'D';
			}	
			else {
				tape[curr_pos] = 1;
				curr_pos += 1;
				curr_state = 'A';
			}
			break;
	}
	if( curr_pos == -1 ) {
		tape.push_front( 0 );
		curr_pos = 0;
	}
	if( curr_pos == tape.size() )
		tape.push_back( 0 );
} 


/*
Begin in state A.
Perform a diagnostic checksum after 12667664 steps.

In state A:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state B.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state C.

In state B:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state A.
  If the current value is 1:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state D.

In state C:
  If the current value is 0:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state B.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state E.

In state D:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state A.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the right.
    - Continue with state B.

In state E:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state F.
  If the current value is 1:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state C.

In state F:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state D.
  If the current value is 1:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state A.
*/
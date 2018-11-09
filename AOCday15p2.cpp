#include <cstdlib>
#include <iostream>

using namespace std;

int main( void ) {
    unsigned long long int gen_a_value, gen_a_prev_value; 
    unsigned long long int gen_b_value, gen_b_prev_value;
    unsigned long long int temp_a, temp_b;
    unsigned short a_low, b_low;
    int judge_counter;

    gen_a_prev_value = 883;
    gen_b_prev_value = 879;
    judge_counter = 0;
    for( int i = 0; i < 5000000; ++i ){
        a_low = b_low = 0;
        while( true ) {
            temp_a = gen_a_prev_value * 16807;
            gen_a_value = temp_a % 2147483647;
            gen_a_prev_value = gen_a_value;
            if( gen_a_value % 4 == 0 )
                break;
        }
        while( true ) {
            temp_b = gen_b_prev_value * 48271;
            gen_b_value = temp_b % 2147483647;
            gen_b_prev_value = gen_b_value;
            if( gen_b_value % 8 == 0 )
                break;
        }
        a_low = gen_a_value ^ a_low;
        b_low = gen_b_value ^ b_low;

        if( a_low == b_low )
            ++judge_counter;        
    }
    cout << judge_counter << endl;
    
    return EXIT_SUCCESS; 
}
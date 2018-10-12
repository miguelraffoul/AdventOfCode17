#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int getCurrentPosValue( vector< vector<int> >&, int, int );
//void printGrid( vector< vector<int> >& );

int main( void ) {
    int target, y, x, n;
    vector< vector<int> > grid( 55, vector<int>( 55, 0 ) );

    cin >> target;
    y = x = 27;
    n = 0;
    grid[y][x] = 1;
    while( true ) {
        int temp;
        n += 2;
        x += 1;
        for( unsigned int i = 0; i < n; ++i ) {       
            temp = getCurrentPosValue( grid, (y - i), x );
            if( temp > target ) {
                cout << temp << endl;
                return EXIT_SUCCESS;
            }
            grid[y - i][x] = temp;
        }
        y -= (n - 1);
        x -= 1;
        for( unsigned int i = 0; i < n; ++i ) {
            temp = getCurrentPosValue( grid, y, (x - i) );
            if( temp > target ) {
                cout << temp << endl;
                return EXIT_SUCCESS;
            }
            grid[y][x - i] = temp;
        }
        x -= (n - 1);
        y += 1;
        for( unsigned int i = 0; i < n; ++i ) {
            temp = getCurrentPosValue( grid, (y + i), x );
            if( temp > target ) {
                cout << temp << endl;
                return EXIT_SUCCESS;
            }
            grid[y + i][x] = temp;
        }
        y += (n - 1);
        x += 1;
        for( unsigned int i = 0; i < n; ++i ) {
            temp = getCurrentPosValue( grid, y, (x + i) );
            if( temp > target ) {
                cout << temp << endl;
                return EXIT_SUCCESS;
            }
            grid[y][x + i] = temp;
        }
        x += (n - 1);
        //printGrid( grid );
    }

    return EXIT_SUCCESS;
}

int getCurrentPosValue( vector< vector<int> >& grid, int y, int x ) {
    int my_number = 0;
    my_number += grid[y][x + 1];
    my_number += grid[y - 1][x + 1];
    my_number += grid[y - 1][x];
    my_number += grid[y - 1][x - 1];
    my_number += grid[y][x - 1];
    my_number += grid[y + 1][x - 1];
    my_number += grid[y + 1][x];
    my_number += grid[y + 1][x + 1];
    return my_number;
}

//void printGrid( vector< vector<int> >& grid ) {
//    cout << "--------------------------------------" << endl;
//    for( unsigned int i = 0; i < grid.size(); ++i ){
//        for( unsigned int j = 0; j < grid[i].size(); ++j ) {
//            cout << grid[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "--------------------------------------" << endl;
//}
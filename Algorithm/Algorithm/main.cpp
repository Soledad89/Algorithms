#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Functions.h"


int main( int argc, char* argv[] ) {
    
    std::stack<char> stk;
    convert(stk, 15, 16);
    while (!stk.empty()) {
        printf("%c", (stk.top()));
        stk.pop();
    }
    
    int n = 20; //array length
    if(1 < argc)
        n = atoi(argv[1]);
    if(n < 0) n = 0; //make sure length is non-negative
    int* A = (int*)malloc(n*sizeof(int)); //allocate an array of size n
    unsigned int seed = (unsigned int)time(NULL); //A same seed is used here for comparison between different algorithms
    double x = 2;
    double y = pow_(x, 10);
    printf("y: %lf", y);
    
    printf( "\n== mergeSort algorithm #0 ========\n" );
    randomArray( A, n, seed ); //create a randomized array using the same seed
    printf( "==>  " ); print( A, n );
    mergeSort( A, 0, n ); //sort the array
    printf( "==>  " ); print( A, n );
    int index = binsearch2(A, 10, 0, n);

    printf("index: %d\n", index);
    
    free(A); //release the array
    return 0;
}
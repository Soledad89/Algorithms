#include "queen.h"

RunMode runMode;
int nSolu = 0;
int nCheck = 0;
int N = 0;

int main(int argc, char* argv[])
{
//    if ( argc < 2 ) //
//    { cout << "Usage: " << argv[0] << " <-step | -cont>" << endl; return -1; }
//    if ( !strcmp ( "-step", argv[1] ) ) runMode = Step; //…Ë∂®Œ™µ•≤Ω—› æƒ£ Ω
//    else if ( !strcmp ( "-cont", argv[1] ) ) runMode = Continuous; //…Ë∂®Œ™¡¨–¯—› æƒ£ Ω
//    else { cout << "Unrecognizable running mode" << endl; return -2; }
//
//    //采用蛮力法和剪枝法
//    void ( *pPlaceQueens[] ) ( void ) = {
//        place5Queens_pruning,//
//        place5Queens_BruteForce,//
//    };
//    int num = sizeof(pPlaceQueens)/sizeof(pPlaceQueens[1]);
//    for ( int i = 0; i < num; i++ ) { //
//        nSolu = 0; nCheck = 0; //
//        ( pPlaceQueens[i] ) (); //
//        printf ( "#Queen = %d\t#Solution = %d\t#Check = %d\a\a\n", 5, nSolu, nCheck ); // ‰≥ˆΩ‚
//        getchar();
//    }
    
    //采用迭代（回溯-剪枝）
    N = 8;
    placeQueens(N);
    getchar();
	return 0;
}





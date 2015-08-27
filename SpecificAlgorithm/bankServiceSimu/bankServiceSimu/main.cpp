/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include "simu.h"

int delay;

int main ( int argc, char* argv[] ) {
   if ( argc < 4 ) {  printf ( "Usage: %s <nWin> <servTime> <delay(ms)>\n", argv[0] ); return -1;  }
   srand ( ( unsigned int ) time ( NULL ) );
   delay = atoi ( argv[3] );
   simulate ( atoi ( argv[1] ), atoi ( argv[2] ) );
   return 0;
}
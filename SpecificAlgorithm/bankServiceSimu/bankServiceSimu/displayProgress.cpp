/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include "simu.h"

/******************************************************************************************
 
 ******************************************************************************************/

void printCustomer ( Customer c )
{
    printf ( "%4d", c.time );
}

void printQueue(queue<Customer> q)
{
    queue<Customer> iq(q);
    Customer tmp;
    while (!iq.empty())
    {
        tmp = iq.front();
        printCustomer(tmp);
        iq.pop();
    }
}
void displayProgress ( queue<Customer> windows[], int nWin, int now ) {
   system ( "/usr/bin/clear" );
   printf ( "============ Time: %4d ============\n", now );
   for ( int i = 0; i < nWin; i++ ) {
      printf ( "Window #%c:  ", 'A' + i );
      printQueue(windows[i]); printf ( "\n" );
   }
}

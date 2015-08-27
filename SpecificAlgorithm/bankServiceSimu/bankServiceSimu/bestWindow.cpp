/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

/*DSA*/#include "simu.h"

int bestWindow ( queue<Customer> windows[], int nWin ) { //最简单的策略：选择队列长度最小的那一列
   int minSize = (int) windows[0].size(), optiWin = 0;
   for ( int i = 1; i < nWin; i++ )
      if ( minSize > windows[i].size() )
         {
             minSize = (int) windows[i].size();
             optiWin = i;
         }
   return optiWin;
}
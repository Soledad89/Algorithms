/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include "simu.h"
#include <unistd.h>

void simulate ( int nWin, int servTime ) {              //按指定窗口数、服务总时间模拟银行业务
   queue<Customer>* windows = new queue<Customer>[nWin]; //为每一个窗口创建一个队列
   for ( int now = 0; now < servTime; now++ ) {         //在下班之前，每隔一个单位时间
      if ( rand() % ( 1 + nWin ) ) {                    //新顾客以nWin/(nWin+1)的概率到达
         Customer c ; c.time = 1 + rand() % 98;         //新顾客到达，服务时间随机确定
         c.window = bestWindow ( windows, nWin );       //找出最佳的服务窗口，更精细的策略
         windows[c.window].push( c );               //新顾客加入对应的队列
      }
      for ( int i = 0; i < nWin; i++ )                  //分别检查
         if ( !windows[i].empty() )                     //各非空队列
            if ( --windows[i].front().time <= 0 )      //对首顾客的服务时间减少一个单位
               windows[i].pop();                        //服务完毕的顾客出列，由后继顾客接替
      /*DSA*/displayProgress ( windows, nWin, now );    //显示当前各窗口队列的情况
      /*DSA*/delay > 0 ?                                //若命令行指定的时间间隔为正数
      /*DSA*/  sleep ( delay ) :
      /*DSA*/  getchar();
   } //for
   delete [] windows;
}
/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename Tv, typename Te> //娣卞害浼樺厛鎼滅储DFS绠楁硶锛堝叏鍥撅級
void Graph<Tv, Te>::dfs ( int s ) { //assert: 0 <= s < n
   reset(); int clock = 0; int v = s; //鍒濆
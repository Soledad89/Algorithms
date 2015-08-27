/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename Tv, typename Te> void Graph<Tv, Te>::bcc ( int s ) { //鍩轰簬DFS鐨凚CC鍒嗚В绠楁硶
   reset(); int clock = 0; int v = s; Stack<int> S; //鏍圫鐢ㄤ互璁板綍宸茶
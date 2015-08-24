/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;

typedef  int   Disk;

void displayHanoi();
void hanoi ( int, stack<Disk>&, stack<Disk>&, stack<Disk>& );
void move ( stack<Disk>&, stack<Disk>& );

extern int nDisk; //盘子总数
extern stack<int> Sx, Sy, Sz; //用三个栈模拟三根柱子，每个盘子的半径用整数表示

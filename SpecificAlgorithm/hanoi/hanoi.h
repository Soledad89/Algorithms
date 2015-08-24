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

extern int nDisk; //��������
extern stack<int> Sx, Sy, Sz; //������ջģ���������ӣ�ÿ�����ӵİ뾶��������ʾ

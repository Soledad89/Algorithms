/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include <stack>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;             //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;    //边在遍历树中所属的类型

template <typename Tv>
struct Vertex {                                         //顶点对象（为简化起见，并未严格封装）
   Tv data; int inDegree, outDegree; VStatus status;    //数据、出入度数、状态
   int dTime, fTime; //时间标签
   int parent; int priority;                            //在遍历树中的父节点、优先级数
   Vertex ( Tv const& d = ( Tv ) 0 ) :                  //构造新顶点
      data ( d ), inDegree ( 0 ), outDegree ( 0 ), status ( UNDISCOVERED ),
      dTime ( -1 ), fTime ( -1 ), parent ( -1 ), priority ( INT_MAX ) {} //暂不考虑权重溢出
};

template <typename Te>
struct Edge {                                   //边对象（为简化起见，并未严格封装）
   Te data; int weight; EType type;             //数据、权重、类型
   Edge ( Te const& d, int w ) : data ( d ), weight ( w ), type ( UNDETERMINED ) {} //构造
};

template <typename Tv, typename Te>     //顶点类型、边类型
struct GraphMatrix {
    vector< Vertex< Tv > > V;           //顶点集（向量）
    vector< vector< Edge< Te > * > > E; //边集（邻接矩阵）
    int n;                                   //顶点总数
    int e; //边总数
};

template <typename Tv, typename Te>                             //顶点类型、边类型
void printGraphMatrix( struct GraphMatrix<Tv, Te>& s ) {               //引用
    int inD = 0;
    for ( int i = 0; i < s.n; i++ )
        inD += s.inDegree(i);
    int outD = 0;
    for ( int i = 0; i < s.n; i++ )
        outD += s.outDegree(i);
    printf ( "%s[%d]*(%d, %d):\n", typeid ( s ).name(), &s, s.n, s.e ); //基本信息
    // 标题行
    print ( s.n ); printf ( " " ); print ( inD ); printf ( "|" );
    for ( int i = 0; i < s.n; i++ ) { print ( s.vertex ( i ) ); printf ( "[" ); print ( s.status ( i ) ); printf ( "] " ); }
    printf ( "\n" );
    // 标题行（续）
    print ( outD ); printf ( " " ); print ( s.e ); printf ( "|" );
    for ( int i = 0; i < s.n; i++ ) { print ( s.inDegree ( i ) ); printf ( " " ); }
    printf ( "| dTime fTime Parent Weight\n" );
    // 水平分隔线
    printf ( "-----------+" ); for ( int i = 0; i < s.n; i++ ) printf ( "------" );
    printf ( "+----------------------------\n" );
    // 逐行输出各顶点
    for ( int i = 0; i < s.n; i++ ) {
        print ( s.vertex ( i ) ); printf ( "[" ); print ( s.status ( i ) ); printf ( "] " ); print ( s.outDegree ( i ) ); printf ( "|" );
        for ( int j = 0; j < s.n; j++ )
            if ( s.exists ( i, j ) ) { print ( s.edge ( i, j ) ); print ( s.type ( i, j ) ); }
            else printf ( "     ." );
        printf ( "| " ); print ( s.dTime ( i ) ); printf ( " " ); print ( s.fTime ( i ) );
        printf ( "     " ); if ( 0 > s.parent ( i ) ) print ( "^" ); else print ( s.vertex ( s.parent ( i ) ) );
        printf ( "  " ); if ( INT_MAX > s.priority ( i ) ) print ( s.priority ( i ) ); else print ( " INF" );
        printf ( "\n" );
    }
    printf ( "\n" );
}
//
//  labyrinth.h
//  labythin
//
//  Created by 王波 on 15/8/24.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#ifndef labythin_labyrinth_h
#define labythin_labyrinth_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;

//数据结构
typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status; //迷宫单元状态，原始可用的、在当前路径上的、所有方向均尝试失败后回溯过的、不可使用的（墙）
typedef enum { UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN; //单元的相对邻接方向，四联通方向，也可以是八联通方向，未定、东、南、西、北、无路可通
inline ESWN nextESWN ( ESWN eswn) { return ESWN(eswn + 1); } //依次转入下一个邻接方向

struct Cell { //迷宫格点
    int x, y;
    Status status;
    ESWN incoming, outgoing; //进入、走出方向
};

//全局变量
#define LABY_MAX 24 //最大的迷宫尺寸
Cell laby[LABY_MAX][LABY_MAX]; //迷宫
int labySize;
Cell* startCell;
Cell* goalCell;

//生成随机迷宫
void randLaby() {
    for ( int i = 0; i < labySize; i++ )
        for ( int j = 0; j < labySize; j++ ) {
            laby[i][j].x = i;
            laby[i][j].y = j;
            laby[i][j].incoming   =   UNKNOWN;
            laby[i][j].outgoing   =   UNKNOWN;
            laby[i][j].status = WALL; //边界格点必须是墙
        }
    for ( int i = 1; i < labySize - 1; i++ )
        for ( int j = 1; j < labySize - 1; j++ )
            if ( rand() % 4 ) laby[i][j].status = AVAILABLE; //75%的格点为空可用
    
    startCell = &laby[rand() % ( labySize-2 ) + 1][rand() % ( labySize-2 ) + 1];
    goalCell  = &laby[rand() % ( labySize-2 ) + 1][rand() % ( labySize-2 ) + 1];
    startCell->status = goalCell->status = AVAILABLE; //起始点必须可用
}

//读入迷宫数据
void readLaby ( const char* labyFile ) {
    FILE* fp;
    int labySize;
    if ( !(fp = fopen(labyFile, "r")) )
    { cout << "can't open " << labyFile << endl; exit ( -1 ); }
    
    fscanf(fp, "Laby Size = %d\n", &labySize );
    if ( LABY_MAX < labySize )
    { cout << "Laby size " << labySize << " > " << LABY_MAX << endl; exit ( -1 ); }
    
    int startX, startY;
    fscanf( fp, "Start = (%d, %d)\n", &startX, &startY );
    startCell = &laby[startX][startY];
    
    int goalX, goalY;
    fscanf( fp, "Goal = (%d, %d)\n", &goalX, &goalY );
    goalCell = &laby[goalX][goalY];
    
    for ( int i = 0; i < labySize; i ++ )
        for ( int j = 0; j < labySize; j ++ ) {
            laby[i][j].x = i;
            laby[i][j].y = j;
            int type;
            fscanf ( fp, "%d", &type );
            switch ( type ) {
                case 1:   laby[i][j].status = WALL;      break;
                case 0:   laby[i][j].status = AVAILABLE;   break;
                default:   exit ( -1 );
            }
            laby[i][j].incoming =   UNKNOWN;
            laby[i][j].outgoing =   UNKNOWN;
        }
    fclose(fp);
}



//输出某一迷宫格的信息
void printLabyCell(Cell* elem){
    printf("%d -> (%d, %d) -> %d\n",
           ( (Cell* ) elem ) -> incoming,
           ( (Cell* ) elem ) -> x,
           ( (Cell* ) elem ) -> y,
           ( (Cell* ) elem ) -> outgoing);
}

//显示迷宫
void displayLaby() { //┘└┐┌│─
    static char*   pattern[5][5] = {
        "┼", "┼", "┼", "┼", "┼",
        "┼", "  ", "┌", "─", "└",
        "┼", "┌", "  ", "┐", "│",
        "┼", "─", "┐", "  ", "┘",
        "┼", "└", "│", "┘", "  "
    };
    system ( "/usr/bin/clear" );
    printf ( " " );
    for ( int j = 0; j < labySize; j++ )
        ( j < 10 ) ? printf ( "%X", j ) : printf ( "%c", 'A' - 10 + j ); //打印第一行的列数
    printf ( "\n" );
    for ( int i = 0; i < labySize; i++ )
    {
        ( i < 10 ) ? printf ( "%X", i ) : printf ( "%c", 'A' - 10 + i );
        for ( int j = 0; j < labySize; j++ )
            if ( goalCell == &laby[i][j] )
                printf ( "$" );
            else
                switch ( laby[i][j].status ) {
                    case WALL:          printf ( "█" );   break;
                    case BACKTRACKED:   printf ( "○" );   break;
                    case AVAILABLE:     printf ( " " );   break;
                    default:
                        printf ( "%s", pattern[laby[i][j].outgoing][laby[i][j].incoming]);
                        break;
                }
        printf ( "\n" );
    }
}

//从当前位置转入相邻格点
inline Cell* advance ( Cell* cell) {
    Cell* next;
    switch (cell->outgoing) {
        case EAST:
            next = cell + 1;                next->incoming = WEST; break;
        case SOUTH:
            next = cell + LABY_MAX;         next->incoming = NORTH; break;
        case WEST:
            next = cell - 1;                next->incoming = EAST; break;
        case NORTH:
            next = cell - LABY_MAX;         next->incoming = SOUTH; break;
        default:
            exit(-1);
    }
    return next;
}

//查询当前位置的相邻节点
inline Cell* neighbor ( Cell* cell) {
    switch (cell->outgoing) {
        case EAST:  return  cell + 1;               //向东
        case SOUTH: return  cell + LABY_MAX;        //向南
        case WEST:  return  cell - 1;               //向西
        case NORTH: return  cell - LABY_MAX;        //向北
        default:    exit(-1);
    }
    
}

//迷宫搜寻算法：在格单元s至t之间规划一跳通路（如果的确存在）
bool labyrinth(Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t)
{
    if ((AVAILABLE != s->status) || (AVAILABLE != t->status))
        return false;
    std::stack<Cell*> path;
    s->incoming = UNKNOWN;
    s->status = ROUTE;
    path.push(s);
    
    do{
        system("/usr/bin/clear"); displayLaby(); getchar();
        Cell* c = path.top(); //检查当前栈顶位置
        if ( c == t)    return true; //若已抵达终点，则找到了一跳通路
        
        while ((c->outgoing = nextESWN(c->outgoing)) < NO_WAY)  //逐一检查所有方向
            if (AVAILABLE == neighbor(c)->status)               //试图找到尚未试探的方向
                break;
        if (c->outgoing < NO_WAY)                              //若有的方向还未尝试过
        {
            path.push(c = advance(c));
            c->outgoing = UNKNOWN;
            c->status = ROUTE;
        }else
        {
            c->status = BACKTRACKED; path.pop();         //则向后回溯一步
            
        }
    }while (!path.empty());
    
    return false;
    
}







#endif

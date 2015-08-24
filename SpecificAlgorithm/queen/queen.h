#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stack>
#include <vector>
#include <algorithm>


using namespace std;

#define QUEEN_MAX 20

typedef enum { Continuous, Step } RunMode;

extern RunMode runMode;
extern int nSolu;
extern int nCheck;
extern int N;

//使用蛮力法和剪枝法的头文件
bool collide(int* solu, int k)
{
    nCheck++;
    for (int i = 0; i < k; i++) {
        if ( solu[k] == solu[i] )	return true; //列
        if ( solu[k] - solu[i] == k - i)	return true;//对角线
        if ( solu[k] - solu[i] == i - k)	return true;//反对角线
    }
    return false;
}

void displaySolution(int *solu, int n)
{
    //( Step == runMode ) ? system("clear") : printf("--\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf ( ( j == solu[i] ) ? "#" : "[]" );
        
        printf("\n");
    }
    
    if (Step == runMode)
    {
        cout << nSolu << " solution(s) found after " << nCheck <<
        " check(s)\n";
    }else
        printf("\n");
}

void place5Queens_BruteForce() {
    int solu[5]; //
    int nCandidate = 0;
    for ( solu[0] = 0; solu[0] < 5; solu[0]++ )
        for ( solu[1] = 0; solu[1] < 5; solu[1]++ )
            for ( solu[2] = 0; solu[2] < 5; solu[2]++ )
                for ( solu[3] = 0; solu[3] < 5; solu[3]++ )
                    for ( solu[4] = 0; solu[4] < 5; solu[4]++ ) {
                        nCandidate++;
                        if ( collide ( solu, 0 ) ) continue;
                        if ( collide ( solu, 1 ) ) continue;
                        if ( collide ( solu, 2 ) ) continue;
                        if ( collide ( solu, 3 ) ) continue;
                        if ( collide ( solu, 4 ) ) continue;
                        nSolu++; displaySolution ( solu, 5 );
                    }
    printf ( "%d Queens, %d Solution(s), %d Candidate(s), %dCheck(s)\n\a\a", 5, nSolu, nCandidate, nCheck );
}

void place5Queens_pruning() { //5皇后剪枝
    int solu[5]; //解法
    for ( solu[0] = 0; solu[0] < 5; solu[0]++ )
        if ( !collide ( solu, 0 ) )
            for ( solu[1] = 0; solu[1] < 5; solu[1]++ )
                if ( !collide ( solu, 1 ) )
                    for ( solu[2] = 0; solu[2] < 5; solu[2]++ )
                        if ( !collide ( solu, 2 ) )
                            for ( solu[3] = 0; solu[3] < 5; solu[3]++ )
                                if ( !collide ( solu, 3 ) )
                                    for ( solu[4] = 0; solu[4] < 5; solu[4]++ )
                                        if ( !collide ( solu, 4 ) ) {
                                            nSolu++; displaySolution ( solu, 5 );
                                        }
}

//使用试探-回溯-剪枝法的头文件
struct Queen{
    int x, y;
    Queen (int xx = 0, int yy = 0) : x(xx), y(yy) {};
    bool operator==(Queen const & q) const {
        return ( x == q.x)       //行冲突
        || (y == q.y)            //列冲突
        || ( x + y == q.x + q.y) //沿对角线冲突
        || ( x - y == q.x - q.y);//沿反对脚线冲突
    }
    bool operator!=(Queen const& q) const { return !(*this == q); }
    
};

void displayRow(Queen& q)
{
    printf("%2d: ", q.x);
    int i = 0;
    while (i++ < q.y) printf("[]");
    printf("#");
    while (i++ < N)  printf("[]");
    printf("%2d\n", q.y);
    
}
void display(std::vector<Queen>& S, int nQueen)
{
    //system("clear");
    for_each(S.rbegin(), S.rend(), displayRow);
    if ( nQueen <= S.size())
        cout << nSolu << " solution(s) found after " << nCheck << " check(s)\n";
    //getchar();
    
}

bool findQueen(std::vector<Queen> qVec, const Queen queen)
{
    vector<Queen>::iterator iterQueen;
    bool flag = true;
    
    for (iterQueen = qVec.begin(); iterQueen != qVec.end(); iterQueen++)
        if ((*iterQueen) == queen) { flag = true; break; }
    if (iterQueen == qVec.end())
        flag = false;
    return flag;
}

//这个好理解一些，整个程序是有三个部分组成，都集中于一个do/while语句中
void placeQueens(int N)
{
    std::vector<Queen> solu; //stack storing the solution
    Queen q(0, 0);// start from the original point
    clock_t c_start = clock();
    
    do {
        
        //while ((q.y < N) && findQueen(solu, q)) //通过与已有皇后的比对
        while ((q.y < N) && find(solu.begin(),solu.end(),q) != solu.end()) //这个快多了，这一个部分是最花费时间的
        {
            q.y++; nCheck++;
        }//尝试找到可摆放下一个皇后的列
        
        if (q.y < N ) { //若存在摆放的列，则
            solu.push_back(q); //摆放上当前的皇后，并
            if ( solu.size() >= N ) //若部分解已成为全局解，则通过全局变量nSolu计数
            {
                nSolu++; display(solu, N);
            }
            q.x++;                  //转入下一行
            q.y = 0;                //从0列开始，试探下一个皇后
        }
        

        if ( solu.size() >= N || q.y >= N ) //若已出界，则
        {
            q = solu.back();
            solu.pop_back();
            q.y++;//回溯一行，并继续试探下一列
        }//否则，试探下一行
        
    }while ( (q.x > 0) || (q.y < N)) ; //所有分支均已或穷举或剪枝之后，算法结束,q==(0,N)的时候
    
    clock_t c_end = clock();
    double timeSpended = 1000.0 * (c_end - c_start)/CLOCKS_PER_SEC;
    printf("Time Spended %f (ms)\n", timeSpended);
}


//placeQueens Backup

//void placeQueens(int N)
//{
//    std::vector<Queen> solu; //stack storing the solution
//    Queen q(0, 0);// start from the original point
//    clock_t c_start = clock();
//    
//    do {
//        if ( solu.size() >= N || q.y >= N ) //若已出界，则
//        {
//            q = solu.back();
//            solu.pop_back();
//            q.y++;//回溯一行，并继续试探下一列
//        }else { //否则，试探下一行
//            while ((q.y < N) && findQueen(solu, q)) //通过与已有皇后的比对
//                //while ((q.y < N) && find(solu.begin(),solu.end(),q) != solu.end())
//            {
//                q.y++; nCheck++; //尝试找到可摆放下一个皇后的列
//            }
//            if (q.y < N ) { //若存在摆放的列，则
//                solu.push_back(q); //摆放上当前的皇后，并
//                if ( solu.size() >= N ) //若部分解已成为全局解，则通过全局变量nSolu计数
//                {
//                    nSolu++; display(solu, N);
//                }
//                q.x++;                  //转入下一行
//                q.y = 0;                //从0列开始，试探下一个皇后
//            }
//            
//        }
//    }while ( (q.x > 0) || (q.y < N)) ; //所有分支均已或穷举或剪枝之后，算法结束,q==(0,N)的时候
//    
//    clock_t c_end = clock();
//    double timeSpended = 1000.0 * (c_end - c_start)/CLOCKS_PER_SEC;
//    printf("Time Spended %f (ms)\n", timeSpended);
//}












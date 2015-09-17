/*
 Description
 
 A friend of you is doing research on the Traveling Knight Problem (TKP) where you are to find the shortest closed tour of knight moves that visits each square of a given set of n squares on a chessboard exactly once. He thinks that the most difficult part of the problem is determining the smallest number of knight moves between two given squares and that, once you have accomplished this, finding the tour would be easy.
 Of course you know that it is vice versa. So you offer him to write a program that solves the "difficult" part.
 
 Your job is to write a program that takes two squares a and b as input and then determines the number of knight moves on a shortest route from a to b.
 */


#include <iostream>
#include <queue>
using namespace std;

struct knight{
    int x,y,step;
    int g,h,f;                                      // f = g + h
    bool operator < (const knight & k) const{      //重载比较运算符
        return f > k.f;
    }
}k;
bool visited[8][8];                                //已访问标记(关闭列表)
int x1,y1,x2,y2,ans;                               //起点(x1,y1),终点(x2,y2),最少移动次数ans
int dirs[8][2]={{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}};//8个移动方向
priority_queue<knight> que;                        //最小优先级队列(开启列表)

bool in(const knight & a){                         //判断knight是否在棋盘内
    if(a.x<0 || a.y<0 || a.x>=8 || a.y>=8)
        return false;
    return true;
}
int Heuristic(const knight &a){                    //manhattan估价函数
    return (abs(a.x-x2)+abs(a.y-y2))*10;
}
void Astar(){                                      //A*算法
    knight t,s;
    while(!que.empty()){
        t = que.top(), que.pop(), visited[t.x][t.y] = true;
        if(t.x == x2 && t.y == y2){                 //算法终止条件
            ans = t.step;
            break;
        }
        for(int i = 0; i < 8; i++){
            s.x = t.x+dirs[i][0],s.y = t.y+dirs[i][1];
            if(in(s) && !visited[s.x][s.y]){    //依次判断八个位置的属性是否满足要求，再压入队列中
                s.g = t.g + 23;                 //23表示根号5乘以10再取其ceil
                s.h = Heuristic(s);
                s.f = s.g + s.h;
                s.step = t.step + 1;
                que.push(s);
            }
        }
    }
}

int main__(){
    char line[5];
    while(fgets(line, 6, stdin)){
        x1=line[0]-'a',y1=line[1]-'1',x2=line[3]-'a',y2=line[4]-'1';
        memset(visited,false,sizeof(visited));
        k.x=x1,k.y=y1,k.g=k.step=0,k.h=Heuristic(k),k.f=k.g+k.h;
        while(!que.empty()) que.pop();
        que.push(k);
        Astar();
        printf("To get from %c%c to %c%c takes %d knight moves.\n",line[0],line[1],line[3],line[4],ans);
    }
    return 0;
}


//BFS
int n,sx,sy,ex,ey;
int vis[305][305];
int direction[8][2] = {-1,-2,-2,-1,-2,1,-1,2,1,-2,2,-1,2,1,1,2};
struct node
{
    int x,y,step;
};

int check(int x,int y)
{
    if(x<0 || x>=n || y<0 || y>=n)
        return 1;
    return vis[x][y];
}

void bfs()
{
    memset(vis,0,sizeof(vis));
    node a,next;
    queue<node> Q;
    int i;
    a.x = sx;
    a.y = sy;
    a.step = 0;
    vis[sx][sy] = 1;
    Q.push(a);
    while(!Q.empty())
    {
        a = Q.front();
        Q.pop();
        if(a.x == ex && a.y == ey)
        {
            printf("%d\n",a.step);
            return;
        }
        for(i = 0;i<8;i++)
        {
            next = a;
            next.x = a.x+direction[i][0];
            next.y = a.y+direction[i][1];
            if(check(next.x,next.y))
                continue;
            next.step = a.step+1;
            vis[next.x][next.y] = 1;
            Q.push(next);
        }
    }
}

int main_()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d%d",&n,&sx,&sy,&ex,&ey);
        bfs();
    }
    
    return 0;
}



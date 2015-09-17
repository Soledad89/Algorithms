#include<iostream>
#include<queue>
#include<fstream>
using namespace std; 
const int size = 362880 ; 
int fact( int n )   //calculate the fact of the number of n 
{
    int sum = 1 ; 
    if ( n == 0 ) 
    	return 1 ; 
	else
		for ( int i = 1 ; i < n+1 ; i ++ ) 
			sum*= i ; 
	return sum ; 
}
int hash(const int state[9],int n) // 将全排列映射为对应的hash值(变进制数) 
{
    int count = 0 ,res = 0 ; 
    for ( int i = 0 ; i < n ; i ++)
    {
        count = 0 ; 
        for ( int j = 0 ; j < i ; j++ ) 
        {
            if ( state[j] > state[i] ) 
            	count ++ ;
        }
    	res+= fact(8-state[i])*count ; 
 	}
  return res ;        	
}  
struct node
{
    int board[9];
    int space ; 
};
void get_node(int sum,node &tmp)   //通过hash值计算对应的状态 
{
    for ( int i = 0 ; i < 9 ; i ++ ) 
    	tmp.board[i] = 0 ; 
 	for ( int  i = 1 ; i <= 9 ; i++ ) 
  	{
       int tot = sum / fact(9-i)+1;
       sum %= fact(9-i);
       int loc , count = 0 ; 
       for ( loc = 0 ; loc < 9 ; loc++ )
       {
           if ( !tmp.board[loc] ) 
           {
               count ++; 
               if ( count == tot ) 
               		break ; 
           }
       }
       tmp.board[loc] = i ;
   }    
   for ( int i = 0 ; i < 9 ; i++ ) 
   {
       tmp.board[i]-= 1 ; 
       if ( tmp.board[i] == 0 ) 
       		tmp.space = i ; 
   }
}
int f[size] , d[size] ;
int goal_state[9][2] = {{1,1},{0,0},{0,1},{0,2},{1,2},{2,2},{2,1},{2,0},{1,0}};

int h( const int board[9] ) //h函数：每个数字到其终点所需步数 
{
    int dis = 0 ; 
    for ( int i = 0 ; i < 9 ; i ++ ) 
    {
        int x = i/3 ; 
        int y = i%3 ; 
        if ( board[i] != 0 ) 
        	dis+= abs(x-goal_state[board[i]][0])+abs(y-goal_state[board[i]][1]);
     }
     return dis ; 
}
struct cmp{
    bool operator()(int u , int v )
    {
        return f[u] > f[v] ; 
    }
};

int color[size] ; 
int parent[size] ; 
int move_[size] ; 
int step[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
int target ; 
void a_Star( const node &start)
{
	int goal[9] = {1,2,3,8,0,4,7,6,5};
 	target = hash(goal,9);
	priority_queue<int,vector<int>,cmp> open ; 
    int u = hash(start.board,9);
    int begin = u ; 
    parent[begin] = -1 ; 
    d[u] = 0 ; 
    f[u] = h(start.board);
    open.push(u);
    color[u] = 1; 
    node tmp,cur ; 
    while ( !open.empty())   //A*算法主要部分 
    {
        u = open.top();
        if ( u==target ) 
        {
            return ; 
        }
        open.pop();
        get_node(u,cur);
        int k = cur.space ; 
        int x = k/3 ; 
        int y = k% 3 ; 
        for ( int i = 0 ; i < 4 ; i ++ ) 
        {
            int a= x + step[i][0];
            int b= y + step[i][1];
            if(0<=a && a<=2 && 0<=b && b<=2)
            {                
               		tmp = cur;                
                 	tmp.space = a*3 + b;                
                  	swap(tmp.board[k], tmp.board[tmp.space]);                
                   	int v = hash(tmp.board,9);                
                    if(color[v] == 1 && (d[u] + 1) < d[v]){//结点在open表中                    
                    	move_[v] = i;                    
                     	f[v] = f[v] - d[v] + d[u] + 1;                   
                      	d[v] = d[u] + 1;                    
                       	parent[v] = u;                                       
                        open.push(v);                
                	}                
                 	else if(color[v] == 2 && (d[u]+1)<d[v]){//结点在closed表中                   
                  		move_[v] = i;                    
                    	f[v] = f[v] - d[v] + d[u] + 1;                  
                     	d[v] = d[u] + 1;                    
                      	parent[v] = u;                    
                       	open.push(v);                    
                        color[v] = 1;                
                    }                
                    else if(color[v] == 0){  //结点为未扩展结点                    
                        move_[v] = i;                    
                        d[v] = d[u] + 1;                    
                        f[v] = d[v] + h(tmp.board);                    
                        parent[v] = u;                    
                        open.push(v);                    
                        color[v] = 1;                
                    }            
            }
        	color[u] = 2 ;            
        }        
    }       
}           
bool judge( const int a[9] )  //判断初始状态的逆序数，以确定是否有解 
{
    int count = 0 ; 
    for ( int i = 0 ; i < 9 ; i ++ ) 
    {
        count = 0 ; 
        for ( int j = 0 ; j < i ; j ++ ) 
        {
            if ( a[j] > a[i] )
            	count ++ ; 
         }
     }
     if ( count % 2 == 1 ) 
     	return true ; 
     else 
     	return false ; 
}
void print(int u );
void print();
ofstream fout ; 
int main ( int argc , char * args[] ) 
{
    node start ; 
    int c ; 
    ifstream fin(args[1]);
    fout.open(args[2]);
    for( int i = 0 ; i < 9 ; i ++ ) 
    {
        fin >> c ; 
        if ( c == 0 ) 
        {
            start.board[i] = 0 ; 
            start.space    = i ; 
        }
        else 
        	start.board[i] = c ; 
     }
     if ( judge(start.board)==true ) 
     {
         a_Star(start);
         print();
     }
     else          
     	fout << "no solution" << endl ; 
     return 0 ;    
}                         
void print( int u )//输出函数 
{
    node tmp ; 
    get_node(u,tmp);
    for ( int i = 0 ; i < 9 ; i ++ )
    {
        if ( i% 3 == 0 ) 
        	fout << endl ; 
        fout << tmp.board[i] << " ";
    }
    fout << endl ; 
}

void print()
{
    int n = -1 ; 
    int path[size] ;
    int s = parent[target] ; 
    while ( s!= -1 ) 
	{
	    n++ ; 
	    path[n] = s; 
	    s = parent[s] ; 
	}
 	fout << n+1 << endl ; 
 	for ( int i = n-1 ; i >= 0 ; i -- ) 
       print(path[i]);
   print(target);        
}                       
                         	

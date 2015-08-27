#include <iostream>   
#include <queue>   
#include <string.h>   
#include <vector>   
#include <algorithm>   
using namespace std;  
  
char Table[26];  
  
struct Node  
{  
    int     freq;  
    char    val;  
    Node    * left;  
    Node    * right;  
    Node():left(NULL), right(NULL) , freq(0) , val('0'){}  
};  
  
class Cmp  
{  
public:  
    bool operator() (const Node * a, const Node * b) const  
    {  
        return  a->freq > b->freq;  // 从小到大 ，freq小的优先级别高
    }  
};  
  
priority_queue<Node* , vector<Node*> , Cmp> myQueue;  
  
void BuildTree()  
{  
    for (int i = 0; i < 26; ++ i)  
    {  
        if (Table[i] > 0)  
        {  
            Node * node = new Node();  
            node->freq = Table[i];  
            node->val =(char) (i + 'A');  
            myQueue.push(node);  
        }  
    }  
      
    while (myQueue.size() > 1)  
    {  
        Node * f = myQueue.top();  
        myQueue.pop();  
        Node * s = myQueue.top();  
        myQueue.pop();  
        Node * tmp = new Node();  
        tmp->freq = f->freq + s->freq;  
        tmp->left = f;  
        tmp->right = s;  
        myQueue.push(tmp);  
    }  
    //cout << myQueue.top()->freq<<endl;   
}  
  
struct PrintNode  
{
    char val;
    int freq;
    string code;  
};  
  
vector<PrintNode> vpn;  
bool cmp(const PrintNode & a , const PrintNode & b)  
{  
    return a.freq > b.freq;  
}  
  
void Print( Node * node , string res)  
{  
    if (node == NULL)  
    {  
        return;  
    }  
    if (node->val != '0')  
    {  
        PrintNode pn;  
        pn.val = node->val;  
        pn.freq = node->freq;  
        pn.code = res;  
        vpn.push_back(pn);  
        //cout <<node->val <<" | " << node->freq <<" | "<< res <<endl;   
        return ;  
    }  
    Print(node->left , res + "0");  
    Print(node->right, res + "1");  
    delete node->left;  
    delete node->right;  
}  
  
int main()  
{  
    int N;  
    memset(Table , 0 , sizeof(Table));  
    N = 40;
    
    for (int i = 0; i < N; ++i)  
    {  
        char ch ;  
        ch = rand() % 26 + 'A';
        if (ch >= 'A' && ch <= 'Z')  
        {  
            ++Table[ch - 'A'];  
        }  
    }  
    BuildTree();  
    Node * root = myQueue.top();  
    myQueue.pop();  
    Print(root , "");  
      
    sort(vpn.begin() , vpn.end() , cmp);  
      
    for (int i = 0; i < vpn.size(); ++i)  
    {  
        cout <<vpn[i].val << " "<<vpn[i].freq <<" " << vpn[i].code<<endl;  
    }  
    return 0;  
}  
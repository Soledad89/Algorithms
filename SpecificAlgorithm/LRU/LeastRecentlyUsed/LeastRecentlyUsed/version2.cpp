//
//  version2.cpp
//  LeastRecentlyUsed
//
//  Created by 王波 on 15/8/29.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

struct Node
{
    int key;
    int value;
    Node *pre;
    Node *next;
};


class LRUCache{
private:
    int count;
    int size ;
    map<int,Node *> mp;
    Node *cacheHead;
    Node *cacheTail;
public:
    LRUCache(int capacity) {
        size = capacity;
        cacheHead = NULL;
        cacheTail = NULL;
        count = 0;
    }
    
    int get(int key) {
        if(cacheHead == NULL)
            return -1;
        map<int,Node *>::iterator it = mp.find(key);
        if(it == mp.end())  //如果在Cache中不存在该key， 则返回-1
        {
            return -1;
        }
        else
        {
            Node *p = it->second;
            pushFront(p);    //将节点p置于链表头部
        }
        return cacheHead->value;
    }
    
    void set(int key, int value) {
        if(cacheHead==NULL)   //如果链表为空，直接放在链表头部
        {
            cacheHead = (Node *)malloc(sizeof(Node));
            cacheHead->key = key;
            cacheHead->value = value;
            cacheHead->pre = NULL;
            cacheHead->next = NULL;
            mp[key] = cacheHead;
            cacheTail = cacheHead;
            count++;
        }
        else   //否则，在map中查找
        {
            map<int,Node *>::iterator it = mp.find(key);
            if(it == mp.end())   //没有命中
            {
                if(count == size)  //cache满了
                {
                    if(cacheHead == cacheTail && cacheHead != NULL)  //只有一个节点
                    {
                        mp.erase(cacheHead->key);
                        cacheHead->key = key;
                        cacheHead->value = value;
                        mp[key] = cacheHead;
                    }
                    else
                    {  //交换链尾节点和头结点
                        Node * p = cacheTail;
                        cacheTail->pre->next = cacheTail->next;
                        cacheTail = cacheTail->pre;
                        
                        mp.erase(p->key);
                        
                        p->key= key;
                        p->value = value;
                        
                        p->next = cacheHead;
                        p->pre = cacheHead->pre;
                        cacheHead->pre = p;
                        cacheHead = p;
                        mp[cacheHead->key] = cacheHead;
                    }
                }
                else
                {   //如果缓冲区还没有满，则加入到缓冲区的头结点处
                    Node * p = (Node *)malloc(sizeof(Node));
                    p->key = key;
                    p->value = value;
                    
                    p->next = cacheHead;
                    p->pre = NULL;
                    cacheHead->pre = p;
                    cacheHead = p;
                    mp[cacheHead->key] = cacheHead;
                    count++;
                }
            }
            else
            {
                Node *p = it->second;
                p->value = value;
                pushFront(p);
            }
        }
        
    }
    
    
    void pushFront(Node *cur)   //双向链表删除节点,并将节点移动链表头部，O(1)
    {
        if(count==1)
            return;
        if(cur==cacheHead)
            return;
        
        if(cur==cacheTail)
        {
            cacheTail = cur->pre;
        }
        
        cur->pre->next = cur->next;   //删除节点
        if(cur->next!=NULL)
            cur->next->pre = cur->pre;
        
        cur->next = cacheHead;
        cur->pre = NULL;
        cacheHead->pre = cur;
        cacheHead = cur;
    }
    
    void printCache(){
        
        Node *p = cacheHead;
        while(p!=NULL)
        {
            cout<<p->key<<" ";
            p=p->next;
        }
        cout<<endl;
    }
};


//int main(void)
//{
//    LRUCache cache(3);
//    cache.set(1,1);
//    //cache.printCache();
//    
//    cache.set(2,2);
//    //cache.printCache();
//    
//    cache.set(3,3);
//    cache.printCache();
//    
//    cache.set(4,4);
//    cache.printCache();
//    
//    cout<<cache.get(4)<<endl;
//    cache.printCache();
//    
//    cout<<cache.get(3)<<endl;
//    cache.printCache();
//    cout<<cache.get(2)<<endl;
//    cache.printCache();
//    cout<<cache.get(1)<<endl;
//    cache.printCache();
//    
//    cache.set(5,5);
//    cache.printCache();
//    
//    cout<<cache.get(1)<<endl;
//    cout<<cache.get(2)<<endl;
//    cout<<cache.get(3)<<endl;
//    cout<<cache.get(4)<<endl;
//    cout<<cache.get(5)<<endl;
//    
//    return 0;
//}

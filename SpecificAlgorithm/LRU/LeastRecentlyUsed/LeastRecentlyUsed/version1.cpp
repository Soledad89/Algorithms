//
//  main.cpp
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
    Node *next;
};


class LRUCache{
private:
    int count;
    int size ;
    map<int,Node *> mp;
    Node *cacheList;
public:
    LRUCache(int capacity) {
        size = capacity;
        cacheList = NULL;
        count = 0;
    }
    
    int get(int key) {
        if(cacheList==NULL)
            return -1;
        map<int,Node *>::iterator it=mp.find(key);
        if(it==mp.end())  //如果在Cache中不存在该key， 则返回-1
        {
            return -1;
        }
        else
        {
            Node *p = it->second;
            pushFront1(p);    //将节点p置于链表头部
        }
        return cacheList->value;
    }
    
    void set(int key, int value) {
        if(cacheList==NULL)   //如果链表为空，直接放在链表头部
        {
            cacheList = (Node *)malloc(sizeof(Node));
            cacheList->key = key;
            cacheList->value = value;
            cacheList->next = NULL;
            mp[key] = cacheList;
            count++;
        }
        else   //否则，在map中查找
        {
            map<int,Node *>::iterator it=mp.find(key);
            if(it==mp.end())   //没有命中
            {
                if(count == size)  //cache满了
                {
                    Node * p = cacheList;
                    Node *pre = p;
                    while(p->next!=NULL)
                    {
                        pre = p;
                        p= p->next;
                    }
                    mp.erase(p->key);
                    count--;
                    if(pre==p)         //说明只有一个节点
                        p=NULL;
                    else
                        pre->next = NULL;
                    free(p);
                }
                Node * newNode = (Node *)malloc(sizeof(Node));
                newNode->key = key;
                newNode->value = value;
                
                newNode->next = cacheList;
                cacheList = newNode;
                
                mp[key] = cacheList;
                count++;
            }
            else
            {
                Node *p = it->second;
                p->value = value;
                pushFront1(p);
            }
        }
        
    }
    
    void pushFront1(Node *cur)  //单链表删除节点,并将节点移动链表头部，O(1)
    {
        if(count==1)
            return;
        //先删除cur节点 ，再将cur节点移到链表头部
        Node *curNext = cur->next;
        if(curNext==NULL)  //如果是最后一个节点
        {
            Node * p = cacheList;
            while(p->next!=cur)
            {
                p=p->next;
            }
            p->next = NULL;
            
            cur->next = cacheList;
            cacheList = cur;
        }
        else    //如果不是最后一个节点
        {
            cur->next = curNext->next;
            int tempKey = cur->key;
            int tempValue = cur->value;
            
            cur->key = curNext->key;
            cur->value = curNext->value;
            
            curNext->key = tempKey;
            curNext->value = tempValue;
            
            curNext->next = cacheList;
            cacheList  = curNext;
            
            mp[curNext->key] = curNext;
            mp[cur->key] = cur;
        }
    }
    
    void pushFront(Node *cur)   //单链表删除节点,并将节点移动链表头部，O(n)
    {
        if(count==1)
            return;
        if(cur==cacheList)
            return;
        Node *p = cacheList;
        while(p->next!=cur)
        {
            p=p->next;
        }
        p->next = cur->next;   //删除cur节点
        
        cur->next = cacheList;
        cacheList = cur;
    }
    
    void printCache(){
        
        Node *p = cacheList;
        while(p!=NULL)
        {
            cout<<p->key<<" ";
            p=p->next;
        }
        cout<<endl;
    }
};


int main(void)
{
    LRUCache cache(5);
     cache.set(2,10);
     cache.printCache();
     cache.set(1,11);
     cache.printCache();
     cache.set(2,12);
     cache.printCache();
     cache.set(1,13);
     cache.printCache();
     cache.set(2,14);
     cache.printCache();
     cache.set(3,15);
     cache.printCache();
     cache.set(4,100);
     cache.printCache();
     cout<<cache.get(2)<<endl;
     cache.printCache();
    
    cout<<cache.get(2)<<endl;
    cache.set(2,6);
    cache.printCache();
    cout<<cache.get(1)<<endl;
    cache.set(1,5);
    cache.printCache();
    cache.set(1,2);
    cache.printCache();
    cout<<cache.get(1)<<endl;
    cout<<cache.get(2)<<endl;
    return 0;
}

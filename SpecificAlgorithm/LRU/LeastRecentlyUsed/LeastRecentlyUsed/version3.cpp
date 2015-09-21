//
//  version3.cpp
//  LeastRecentlyUsed
//
//  Created by 王波 on 15/8/29.
//  Copyright (c) 2015年 wangbo. All rights reserved.
//

#include <iostream>
#include <map>
#include <algorithm>
#include <list>
using namespace std;

struct CacheNode
{
    int key;
    int value;
};


class LRUCache{
private:
    int maxSize ;
    list<CacheNode> cacheList;
    map<int, list<CacheNode>::iterator > mp;
public:
    LRUCache(int capacity) {
        maxSize = capacity;
    }
    
    int get(int key) {
        map<int, list<CacheNode>::iterator >::iterator it = mp.find(key);
        if(it == mp.end())      //没有命中
        {
            return -1;
        }
        else  //在cache中命中了
        {
            list<CacheNode>::iterator listIt = mp[key];
            CacheNode newNode;
            newNode.key = key;
            newNode.value = listIt->value;
            cacheList.erase(listIt);               //先删除命中的节点
            cacheList.push_front(newNode);   //将命中的节点放到链表头部
            mp[key] = cacheList.begin();
        }
        return cacheList.begin()->value;
    }
    
    void set(int key, int value) {
        map<int, list<CacheNode>::iterator >::iterator it = mp.find(key);
        if(it==mp.end())   //没有命中
        {
            if(cacheList.size()==maxSize)  //cache满了
            {
                mp.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            CacheNode newNode;
            newNode.key = key;
            newNode.value = value;
            cacheList.push_front(newNode);
            mp[key] = cacheList.begin();
        }
        else  //命中
        {
            list<CacheNode>::iterator listIt = mp[key];
            cacheList.erase(listIt);               //先删除命中的节点
            CacheNode newNode;
            newNode.key = key;
            newNode.value = value;
            cacheList.push_front(newNode);   //将命中的节点放到链表头部
            mp[key] = cacheList.begin();
        }
    }
};


int main(void)
{
    LRUCache cache(3);
    cache.set(1,1);
    
    cache.set(2,2);
    
    cache.set(3,3);
    
    cache.set(4,4);
    
    
    cout<<cache.get(4)<<endl;
    
    cout<<cache.get(3)<<endl;
    cout<<cache.get(2)<<endl;
    cout<<cache.get(1)<<endl;
    
    cache.set(5,5);
    
    cout<<cache.get(1)<<endl;
    cout<<cache.get(2)<<endl;
    cout<<cache.get(3)<<endl;
    cout<<cache.get(4)<<endl;
    cout<<cache.get(5)<<endl;
    
    return 0;
}
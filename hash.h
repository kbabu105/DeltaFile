//
//  hash.hpp
//  Proj4
//
//  Created by Krishna on 6/1/16.
//  Copyright © 2016 Krishna. All rights reserved.
//

#ifndef hash_hpp
#define hash_hpp

//#include <stdio.h>
//HASH TABLES

#include <iostream>
#include <list>
#include <string>
#include <cstdlib>

using namespace std;

////1
//static const size_t InitialFNV = 2166136261U;
//static const size_t FNVMultiple = 16777619;
//
///* Fowler / Noll / Vo (FNV) Hash */
//size_t myhash(const string &s)
//{
//    size_t hash = InitialFNV;
//    for(size_t i = 0; i < s.length(); i++)
//    {
//        hash = hash ^ (s[i]);       /* xor  the low 8 bits */
//        hash = hash * FNVMultiple;  /* multiply by the magic number */
//    }
//    return hash;
//}


//2
//Unordered_MultiMap: prints out all in bucket when given keys
template <typename K, typename V>	//V = valuetypes
//(V-string, K-offset)
class Unordered_MultiMap {
private:
    list<pair<K,V>>* buckets;	//dynamically resizeable array of lists (store more than value, store key!)
    const double load_factor = 0.75;
    size_t m_size;
    int m_count = 0;
    hash<K> m_hash; //hash is a struct; keep as member, use when need object; overloaded (m_hash"fjlkdsfj" gives int we can use)
    
    void rehash() {
        //m_size *= 2;
        
        //make new buckets
        list<pair<K,V>>* new_buckets = new list<pair<K,V>>[m_size*2];
        
        //move all over
        for (int i = 0; i < m_size; i++)	//for all buckets
        {for(pair<K,V>& p : buckets[i]) {	//for all things inside buckets
            size_t h = m_hash(p.first); 	//rehash key
            new_buckets[h%(m_size*2)].push_back(p);	//put in new buckets
        }
        }
        
        m_size *= 2;
        delete [] buckets;
        buckets = new_buckets;	//new_buckets gets deleted once it leaves scope of fxn
        
    }
    
    
public:
    //copy cstr, =, etc. not written
    
    Unordered_MultiMap(size_t nBuckets) : m_size(nBuckets) {      //CHANGE INITIAL SIZE
        buckets = new list<pair<K,V>>[nBuckets];
    }
    
    ~Unordered_MultiMap() {
        delete [] buckets;
    }
    
    void changeSize(size_t newSize)
    {
        if(newSize == 0)
        { cerr << "Number of buckets cannot be 0";
            exit(1);}
        //make new buckets
        list<pair<K,V>>* new_buckets = new list<pair<K,V>>[newSize];
        
        //move all over
        for (int i = 0; i < m_size; i++)	//for all buckets
        {for(pair<K,V>& p : buckets[i]) {	//for all things inside buckets
            size_t h = m_hash(p.first); 	//rehash key
            new_buckets[h%(newSize)].push_back(p);	//put in new buckets
        }
        }
        
        m_size = newSize;
        delete [] buckets;
        buckets = new_buckets;	//new_buckets gets deleted once it leaves scope of fxn
    }
    
    void insert(pair<K,V> p){	//generic not just string and int
        
        
        size_t h = m_hash(p.first);	//h will be random number
        buckets[h%m_size].push_back(p);	//% by size to put in valid index
        
        m_count++;								//this and below must come after
        
        if((m_count/m_size) > load_factor)
            rehash();
    }
    
    list<V> get(K key) {        //get(key) = value
                                //get(string) = offset
        size_t h = m_hash(key);
        list<V> res;
        for (pair<K,V>& p: buckets[h%m_size])
            if(p.first == key)
                res.push_back(p.second);
        return res;
    }
    
    void print() {
        for(int i = 0; i < m_size; i++) {
            cout << "[" << i << "]: ";
            for(pair<K,V>&p : buckets[i])
                cout << "(" << p.first << ", " << p.second << ") ";
            cout << endl;
        }
    }
};



#endif /* hash_hpp */

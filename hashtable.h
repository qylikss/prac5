#ifndef HASHTABLE
#define HASHTABLE

#include "basemap.h"
#include <iostream>

struct TableItem {
    int key, valueIndex;
    bool isDeleted;
    bool isFree;
    TableItem(int key, int valueIndex);
    TableItem();
};

struct HashTable : public BaseMap {
    TableItem *items;
    HashTable();
    void insert(int key, int value);
    BaseMapEntry *find(int key);
    void remove(int key);
    void print();

private:
    TableItem *find_item(int key);
    ~HashTable();
    int hashKey(int key);
    int capacity, length, removed;
    void rehash();
    bool isEmpty(int index);
    bool insertInArray(TableItem *item, TableItem *items, int length);
    bool isEmptyForArray(int index, TableItem *items);
};

#endif

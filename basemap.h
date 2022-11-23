#ifndef BASETREE
#define BASETREE

class BaseMapEntry {
public:
    int key;
    int value;
    BaseMapEntry(int key, int value);
};

class BaseMap {
public:
    virtual void insert(int key, int value) = 0;
    virtual BaseMapEntry *find(int key) = 0;
    virtual void remove(int key) = 0;
    virtual void print() = 0;
};

#endif

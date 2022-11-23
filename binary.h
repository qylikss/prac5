#ifndef BINARY
#define BINARY

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int hash_string(string str);

struct Record {
    string city_name;
    int city_code;
    Record(int city_code, string city_name);
    Record();
    void print();
};

#endif

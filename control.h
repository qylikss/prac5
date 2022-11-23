#ifndef CONTROL
#define CONTROL

#include "basemap.cpp"
#include "binary.cpp"
using namespace std;

struct Control {
    void add_from_bin(int index);
    Record find_by_key(string key);
    void delete_by_key(string key);
    void print_map();
    Control(string filename, BaseMap *map);

private:
    BaseMap *map;
    string filename;
};

#endif

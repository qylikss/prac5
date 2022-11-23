#include "control.h"

Control::Control(string filename, BaseMap *map) {
    this->filename = filename;
    this->map = map;
}

void Control::add_from_bin(int index) {
    Record r = find_in_binary_file_by_index(filename, index);
    int key = hash_string(r.city_name);
    map->insert(key, index);
}

 Record Control::find_by_key(string city_name) {
    int key = hash_string(city_name);
    BaseMapEntry *node = map->find(key);
    if (node == nullptr) {
        cout << "Record with key " << city_name << " was not found\n";
        exit(1);
    }
    return find_in_binary_file_by_index(filename, node->value);
}

void Control::delete_by_key(string city_name) {
    int key = hash_string(city_name);
    BaseMapEntry *node = map->find(key);
    if (node == nullptr) {
        cout << "Record with key " << city_name << " was not found\n";
        exit(1);
    }
    delete_by_index_in_binary_file(filename, node->value);
    map->remove(key);
}

void Control::print_map() { map->print(); }

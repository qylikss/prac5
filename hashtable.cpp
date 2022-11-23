#include "hashtable.h"

using namespace std;

TableItem::TableItem(int key, int valueIndex) {
    this->key = key;
    this->valueIndex = valueIndex;
    this->isDeleted = false;
    this->isFree = false;
}

TableItem::TableItem() {
    this->isDeleted = false;
    this->isFree = true;
}

HashTable::HashTable() {
    this->capacity = 16;
    this->length = 0;
    this->removed = 0;
    this->items = new TableItem[capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->items[i] = TableItem();
    }
}

HashTable::~HashTable() { delete[] this->items; }

int HashTable::hashKey(int key) { return key % this->capacity; }

void HashTable::remove(int key) {
    TableItem *item = this->find_item(key);
    if (item == nullptr) {
        cout << "Error: can not remove item: no such element";
        exit(1);
    }
    item->isDeleted = true;
    this->removed += 1;
}

TableItem *HashTable::find_item(int key) {
    for (int i = this->hashKey(key); i < this->capacity; i++) {
        if (!isEmpty(i) && items[i].key == key) {
            return &(this->items[i]);
        }
    }

    return nullptr;
}

BaseMapEntry *HashTable::find(int key) {
    TableItem *found = find_item(key);
    if (found) {
        return new BaseMapEntry(found->key, found->valueIndex);
    }
    return nullptr;
}

bool HashTable::isEmpty(int index) {
    return isEmptyForArray(index, this->items);
}

bool HashTable::isEmptyForArray(int index, TableItem *items) {
    return items[index].isDeleted || items[index].isFree;
}

bool HashTable::insertInArray(TableItem *item, TableItem *items, int length) {
    int index = this->hashKey(item->key);
    while (!this->isEmptyForArray(index, items)) {
        index += 1;
        if (index >= length) {
            cout << "[Warning] Hashtable index is out of range\n";
            return false;
        }
    }
    items[index] = *item;
    return true;
}

void HashTable::rehash() {
    int newCapacity = this->capacity * 2;
    int newLength = 0;
    TableItem *newItems = new TableItem[newCapacity];
    for (int i = 0; i < this->capacity; i++) {
        if (!this->isEmpty(i)) {
            insertInArray(&(this->items[i]), newItems, newCapacity);
            newLength += 1;
        }
    }

    this->capacity = newCapacity;
    this->length = newLength;
    this->removed = 0;
    delete[] this->items;
    this->items = newItems;
}

void HashTable::insert(int key, int value) {
    if ((this->length) >= (this->capacity * 3 / 4)) {
        this->rehash();
    }

    TableItem *tableItem = new TableItem(key, value);
    bool inserted = insertInArray(tableItem, this->items, this->capacity);
    if (!inserted) {
        rehash();
        insertInArray(tableItem, this->items, this->capacity);
    }
    this->length += 1;
}

void HashTable::print() {
    TableItem item;
    printf("[%i/%i]\n", length - removed, capacity);
    for (int i = 0; i < this->capacity; i++) {
        item = this->items[i];
        if (!item.isDeleted && !item.isFree) {
            printf("%i->%03d:%03d\n", i, item.key, item.valueIndex);
        }
    }
}

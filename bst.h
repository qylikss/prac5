#ifndef BST
#define BST

#include "basemap.h"
#include <iostream>

struct BSTreeNode {
    int key; // Уникальный идентификатор узла
    int value; // Индекс значения записи
    BSTreeNode *right; // // Указатель на правое поддерево
    BSTreeNode *left; // Указатель на левое поддерево
    BSTreeNode();
    BSTreeNode(int key, int value);
};

class BSTree : public BaseMap {
private:
    BSTreeNode *root;
    BSTreeNode *remove_from_node(BSTreeNode *node, int key);
    BSTreeNode *insert_to_node(BSTreeNode *node, BSTreeNode *new_node);
    BSTreeNode *find_from_node(BSTreeNode *node, int key);
    void print_level(BSTreeNode *node, int level);
    BSTreeNode *join(BSTreeNode *first, BSTreeNode *second);

public:
    BSTree();
    void insert(int key, int value);
    void remove(int key);
    BaseMapEntry *find(int key);
    void print();
    void print_node(BSTreeNode *node);
};

#endif

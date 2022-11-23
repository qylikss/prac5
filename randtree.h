#ifndef RANDTREE
#define RANDTREE

#include "basemap.h"
#include <iostream>
using namespace std;

struct TreeNode {
    int key;
    int value;
    int size;
    TreeNode *left;
    TreeNode *right;
    TreeNode();
    TreeNode(int key, int value);
};

int rotations = 0;

class RandomTree : public BaseMap {
private:
    TreeNode *root;
    TreeNode *find_from_node(TreeNode *node, int key);
    TreeNode *insert_to_node(TreeNode *node, TreeNode *new_node);
    int get_size(TreeNode *node);
    void fix_size(TreeNode *node);
    TreeNode *rotate_right(TreeNode *node);
    TreeNode *rotate_left(TreeNode *node);
    TreeNode *insert_root(TreeNode *node, TreeNode *new_node);
    TreeNode *random_insert(TreeNode *node, TreeNode *new_node);
    void print_level(TreeNode *node, int level);
    TreeNode *join(TreeNode *first, TreeNode *second);
    TreeNode *remove_from_node(TreeNode *node, int k);

public:
    RandomTree();
    void insert(int key, int value);
    void print();
    void print_node(TreeNode *node);
    void remove(int key);
    BaseMapEntry *find(int key);
};

#endif

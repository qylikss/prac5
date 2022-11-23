#include "bst.h"
using namespace std;

BSTreeNode::BSTreeNode() {
    left = nullptr;
    right = nullptr;
}

BSTreeNode::BSTreeNode(int key, int value) {
    left = nullptr;
    right = nullptr;
    this->key = key;
    this->value = value;
}

BSTreeNode *BSTree::join(BSTreeNode *first, BSTreeNode *second) {
    if (!first)
        return second;
    if (!second)
        return first;

    first->right = join(first->right, second);
    return first;
}

BSTreeNode *BSTree::remove_from_node(BSTreeNode *node, int k) {
    if (!node)
        return nullptr;
    if (node->key == k) {
        BSTreeNode *remainder = join(node->left, node->right);
        delete node;
        return remainder;
    } else if (k < node->key)
        node->left = remove_from_node(node->left, k);
    else
        node->right = remove_from_node(node->right, k);
    return node;
}

void BSTree::print_node(BSTreeNode *node) {
    if (node == nullptr)
        cout << "nullptr";
    printf("%03d:%03d", node->key, node->value);
}

void BSTree::print_level(BSTreeNode *node, int level) {
    if (node == nullptr)
        return;
    print_level(node->right, level + 1);
    for (int i = 0; i < level; i++)
        cout << "       ";
    print_node(node);
    cout << endl;
    print_level(node->left, level + 1);
}

BSTreeNode *BSTree::insert_to_node(BSTreeNode *node, BSTreeNode *new_node) {
    if (!node)
        return new_node;
    if (node->key > new_node->key)
        node->left = insert_to_node(node->left, new_node);
    else
        node->right = insert_to_node(node->right, new_node);
    return node;
}

BSTreeNode *BSTree::find_from_node(BSTreeNode *node, int key) {
    if (!node)
        return nullptr;
    if (key == node->key)
        return node;
    if (key < node->key)
        return find_from_node(node->left, key);
    return find_from_node(node->right, key);
}

void BSTree::insert(int key, int value) {
    root = insert_to_node(root, new BSTreeNode(key, value));
}

void BSTree::remove(int key) {
    root = remove_from_node(root, key);
}

BaseMapEntry *BSTree::find(int key) {
    BSTreeNode *found = find_from_node(root, key);
    if (!found)
        return nullptr;
    return new BaseMapEntry(found->key, found->value);
}

BSTree::BSTree() { root = nullptr; }

void BSTree::print() {
    print_level(root, 0);
}

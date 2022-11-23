#include "randtree.h"
using namespace std;

TreeNode::TreeNode(int key, int value) {
    left = right = nullptr;
    size = 1;
    this->key = key;
    this->value = value;
}

TreeNode::TreeNode() {
    left = right = nullptr;
    size = 1;
}

RandomTree::RandomTree() { this->root = nullptr; }

BaseMapEntry *RandomTree::find(int key) {
    TreeNode *found = find_from_node(root, key);
    if (!found)
        return nullptr;
    return new BaseMapEntry(found->key, found->value);
}

TreeNode *RandomTree::find_from_node(TreeNode *node, int key) {
    if (!node)
        return nullptr;
    if (key == node->key)
        return node;
    if (key < node->key)
        return find_from_node(node->left, key);
    return find_from_node(node->right, key);
}

TreeNode *RandomTree::insert_to_node(TreeNode *node, TreeNode *new_node) {
    if (!node)
        return new_node;
    if (node->key > new_node->key)
        node->left = insert_to_node(node->left, new_node);
    else
        node->right = insert_to_node(node->right, new_node);
    fix_size(node);
    return node;
}

int RandomTree::get_size(TreeNode *node) {
    if (!node)
        return 0;
    return node->size;
}

void RandomTree::fix_size(TreeNode *node) {
    node->size = get_size(node->left) + get_size(node->right) + 1;
}

TreeNode *RandomTree::rotate_right(TreeNode *node) {
    rotations++;
    TreeNode *new_root = node->left;
    if (!new_root)
        return node;
    node->left = new_root->right;
    new_root->right = node;
    new_root->size = node->size;
    fix_size(node);
    return new_root;
}

TreeNode *RandomTree::rotate_left(TreeNode *node) {
    rotations++;
    TreeNode *new_root = node->right;
    if (!new_root)
        return node;
    node->right = new_root->left;
    new_root->left = node;
    new_root->size = node->size;
    fix_size(node);
    return new_root;
}

TreeNode *RandomTree::insert_root(TreeNode *node, TreeNode *new_node) {
    if (!node)
        return new_node;
    if (new_node->key < node->key) {
        node->left = insert_root(node->left, new_node);
        return rotate_right(node);
    } else {
        node->right = insert_root(node->right, new_node);
        return rotate_left(node);
    }
}

TreeNode *RandomTree::random_insert(TreeNode *node, TreeNode *new_node) {
    if (!node)
        return new_node;
    if (rand() % (node->size + 1) == 0)
        return insert_root(node, new_node);
    if (node->key > new_node->key)
        node->left = insert_to_node(node->left, new_node);
    else
        node->right = insert_to_node(node->right, new_node);
    fix_size(node);
    return node;
}

void RandomTree::insert(int key, int value) {
    root = random_insert(root, new TreeNode(key, value));
}

void RandomTree::print_level(TreeNode *node, int level) {
    if (node == nullptr)
        return;
    print_level(node->right, level + 1);
    for (int i = 0; i < level; i++)
        cout << "       ";
    print_node(node);
    cout << endl;
    print_level(node->left, level + 1);
}

void RandomTree::print_node(TreeNode *node) {
    if (node == nullptr)
        cout << "nullptr";
    printf("%03d:%03d", node->key, node->value);
}

void RandomTree::print() { print_level(root, 0); }

TreeNode *RandomTree::join(TreeNode *first, TreeNode *second) {
    if (!first)
        return second;
    if (!second)
        return first;

    if (rand() % (first->size + second->size) < first->size) {
        first->right = join(first->right, second);
        fix_size(first);
        return first;
    } else {
        second->left = join(first, second->left);
        fix_size(second);
        return second;
    }
}

TreeNode *RandomTree::remove_from_node(TreeNode *node, int k) {
    if (!node)
        return nullptr;
    if (node->key == k) {
        TreeNode *remainder = join(node->left, node->right);
        delete node;
        return remainder;
    } else if (k < node->key)
        node->left = remove_from_node(node->left, k);
    else
        node->right = remove_from_node(node->right, k);
    return node;
}

void RandomTree::remove(int key) { root = remove_from_node(root, key); }

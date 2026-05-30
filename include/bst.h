// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>

template <typename T>
class BST {
 public:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;
    };

 private:
     Node* root;
     Node* addNode(Node* root, const T& data) {
         if (root == nullptr) {
             root = new Node;
             root->data = data;
             root->count = 1;
             root->left = nullptr;
             root->right = nullptr;
         } else if (data > root->data) {
             root->right = addNode(root->right, data);
         } else if (data < root->data) {
             root->left = addNode(root->left, data);
         } else {
             root->count++;
         }
         return root;
     }
     void deleteTree(Node* root) {
         if (root == nullptr)
             return;
         deleteTree(root->left);
         deleteTree(root->right);
         delete root;
     }
     int treeDepth(Node* root) {
         if (root == nullptr)
             return -1;
         return 1 + std::max(treeDepth(root->left), treeDepth(root->right));
     }
     int searchTree(Node* root, const T& data) {
         if (root == nullptr)
             return 0;
         if (data < root->data) {
             return searchTree(root->left, data);
         }
         if (data > root->data) {
             return searchTree(root->right, data);
         }
         return root->count;
     }
     void vectorAddAllNodes(std::vector<Node*>& vector, Node* root) {
         if (root == nullptr)
             return;
         vectorAddAllNodes(vector, root->left);
         vectorAddAllNodes(vector, root->right);
         vector.push_back(root);
     }

 public:
     BST() : root(nullptr) {}
     ~BST() {
         deleteTree(root);
     }
     void insert(const T& data) {
         root = addNode(root, data);
     }
     int depth() {
         return treeDepth(root);
     }
     int search(T value) {
         return searchTree(root, value);
     }
     std::vector<Node*> vectorNodeData() {
         std::vector<Node*> vector;
         vectorAddAllNodes(vector, root);
         return vector;
     }
};

#endif  // INCLUDE_BST_H_

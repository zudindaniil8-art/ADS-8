// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>
#include <utility>
#include <string>

#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string str;
    while (!file.eof()) {
        char ch = file.get();

        if (ch >= 'A' && ch <= 'Z') {
            ch += 32;
            str.push_back(ch);
        } else if (ch >= 'a' && ch <= 'z') {
            str.push_back(ch);
        } else {
            if (!str.empty()) {
                tree.insert(str);
                str.clear();
            }
        }
    }
    if (!str.empty()) {
        tree.insert(str);
    }

    file.close();
}

void nodeVectorSort(std::vector<BST<std::string>::Node*>& vector) {
    for (int i = 0; i < vector.size() - 1; i++) {
        int mini = i;
        for (int j = i + 1; j < vector.size(); j++)
            if (vector[j]->count > vector[mini]->count)
                mini = j;
        std::swap(vector[i], vector[mini]);
    }
}

void printFreq(BST<std::string>& tree) {
    std::vector<BST<std::string>::Node*> vector = tree.vectorNodeData();
    nodeVectorSort(vector);

    std::ofstream output("freq.txt");
    for (auto i : vector)
        output << i->data << " " << i->count << std::endl;

    output.close();
}

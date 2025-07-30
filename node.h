//
// Created by Mr.Nazim on 7/29/2025.
//

#ifndef NODE_H
#define NODE_H

//class to create node
class node {
public:
    char ch;                //character
    int freq;               //frequency of that character

    node* left;             //node's left children
    node* right;            //node's right children

    //constructor overloading
    node(char c, int f);
    node();

    bool compare_nodes(node* a, node* b) {
        if (a->left == a->right) return a->ch > a->ch;
        return a->left > a->right;
    }

    //destructor
    ~node();
};




#endif //NODE_H

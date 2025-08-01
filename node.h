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

    //method to compare frequencies of nodes. Made static to retain the value throughout runtime
    static bool compare_nodes(node* a, node* b);

    //destructor
    ~node();
};




#endif //NODE_H

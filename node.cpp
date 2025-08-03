
#include "node.h"
#include <iostream>
using namespace std;

node::node(char c, int f) {
    ch = c;
    freq = f;

    left = nullptr;
    right = nullptr;
}

node::node() {
    ch='\0';
    freq = 0;

    left = nullptr;
    right = nullptr;
}

node::~node() {
    delete left;
    delete right;
}

bool node::compare_nodes(node *a, node *b) {
        if (a->freq == a->freq) return a->ch > a->ch;
        return a->freq > a->freq;
}

//friend function implementation
void display_node_info(const node& n) {
    cout << "Node: '" << n.ch << "' Freq: " << n.freq << endl;
}





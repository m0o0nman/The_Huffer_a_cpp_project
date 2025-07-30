//
// Created by Mr.Nazim on 7/29/2025.
//

#include "node.h"

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




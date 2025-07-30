//
// Created by Mr.Nazim on 7/29/2025.
//

#include "huffman_base.h"

#include <fstream>

#include "node.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

huffman_base::huffman_base(unordered_map<char, int> f_m, unordered_map<char, string> cd) {
    //initializing protected members of the huffman_base class with a constrcutor
    root = nullptr;
    freq_map = f_m;
    codes = cd;
}


//this unordered map contains the frequency as value for each character as key
void huffman_base::build_frequency_map(const string &text) {
    for (char c: text) {
        freq_map[c]++;      //if the character is encountered, freq++
    }
}

//this method builds the huffman tree which is a min heap
void huffman_base::build_huffman_tree() {
    priority_queue<node*> sorted_char_freq;     //a priority queue to auto sort the char, frequency pair

    //implementing a for loop to go through each value pain in the frequency map and sort by default
    for (auto pair: freq_map) {
        //every value pair in the priority queue is saved as an object of node which has char and freq variables
        //this node pair will later be used to create the huffman tree
        sorted_char_freq.push(new node(pair.first, pair.second));   //priority queue is MAX heap
    }

    //looping through the priority queue to create the huffman tree
    while (sorted_char_freq.size() > 1) {               //iterates until only 1 node remains which is the root
        //the top value pair, which is the lowest, is assigned to left node and the next to lowest to the right node
        node* left = sorted_char_freq.top(); sorted_char_freq.pop();
        node* right = sorted_char_freq.top(); sorted_char_freq.pop();

        //the compare_nodes function checks if the freq is greater or not. If greater, the values the swapped
        if (left->compare_nodes(left, right)) {
            swap(left, right);                //left node is always small
        }

        //creating a parent node with left and right node as children.
        //The parent node's ch is it's children's combined and the value is the sum of the children's values
        node* parent = new node(left->ch + right->ch, left->freq + right->freq);

        //parent's left child is the lowest node and right node is the next to lowest node
        parent ->left = left;
        parent->right = right;
        sorted_char_freq.push(parent);                  //the new node, parent, is pushed in the priority queue/ tree
    }
    //after the loop only the root remains on the priority queue, if any error occurs, the top is then assigned a null pointer
    root = sorted_char_freq.empty() ? nullptr : sorted_char_freq.top();
}
//a recursive function to assign an unique prefix proof binary code for each leaf node or character
void huffman_base::build_codes(node* n, string codes) {
    if (n == nullptr) return;                          //checks if the node is a root or not, if root, the function breaks

    //cheks if the node is a leaf node or not
    //leaf nodes don't have children so left and right are null by definition
    if (n->left == nullptr && n->right == nullptr) {
        //the string is checked if only 1 char is remaining using empty()
        //the empty() checks if only 1 remains and returns true if, only for chars with most frequency
        codes[n->ch] = codes.empty() ? "0" : codes;   //the value for the key char is then assigned 0
    }

    //recursive call of the left child of node n, traverses and appends 0 when goes to left child
    build_codes(n->left, codes + "0");
    //recursive call of the right child of node n, traverses and appends 1 when goes to right child
    build_codes(n->right, codes + "1");
}

void huffman_base::display_code() {
    cout << "\nHuffman Codes:\n";
    for (auto pair: codes) {
        cout <<pair.first<< " : " << pair.second <<endl;
    }
}

encoder::encoder(string t): huffman_base() {
    text = t;
    encoded_str = "";
}

//Inherited class of huffman_base
//process() is a virtual method of huffman_base
//by overriding, runtime/dynamic polymorphism was implemented
void encoder::process() {
    build_frequency_map(text);              //builds the frequency map of the text
    build_huffman_tree();                   //from the frequency map, this method builds the huffman tree (min heap)
    build_codes(root, "");        //traversing the huffman tree, code is assigned to each leaf node carrying a char

    //This for loop iterates over the codes map and assigns code for each character
    //in the text string into the coded string where the message is encoded
    for (char c: text) {
        encoded_str += codes[c];
    }
}
//the function is made const to make the method's attributes immutable after initialization
void encoder::save_to_file(const string& filename) const {
    ofstream out(filename);                         //creates an output stream for the file

    //checks if the file has opened or not
    if (out.fail()) {
        cerr << "Error opening file" << endl;
        return;
    }

    out << encoded_str << "\n";                     //feeding the encoded string into the output file stream

    //this for loop iterates over the unordered map for the char and their huffman code pair
    for (auto pair: codes) {
        //the ASCII value for each char is fed in the stream first for efficiency and reliability
        //then the related char's code is saved as well in the same line
        out << (int)(pair.first) << " " << pair.second << endl;
    }

    out.close();                                    //closes the output file stream, clears heap
}











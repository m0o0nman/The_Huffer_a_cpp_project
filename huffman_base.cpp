#include "huffman_base.h"

#include <fstream>
#include <iomanip>

#include "node.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

huffman_base::huffman_base(unordered_map<char, int> f_m, unordered_map<char, string> cd) {
    //initializing protected members of the huffman_base class with a constructor
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
    // Create a comparator for min heap based on frequency
    auto compare = [](node* a, node* b) {
        return a->freq > b->freq;  // Min heap: smaller frequencies have higher priority
    };

    priority_queue<node*, vector<node*>, decltype(compare)> sorted_char_freq(compare);

    //implementing a for loop to go through each value pain in the frequency map and sort by default
    for (auto pair: freq_map) {
        //every value pair in the priority queue is saved as an object of node which has char and freq variables
        //this node pair will later be used to create the huffman tree
        sorted_char_freq.push(new node(pair.first, pair.second));
    }

    // FIX 2: Handle edge case of single character
    if (sorted_char_freq.size() == 1) {
        root = sorted_char_freq.top();
        return;
    }

    //looping through the priority queue to create the huffman tree
    while (sorted_char_freq.size() > 1) {
        //the top value pair, which is the lowest, is assigned to left node and the next to lowest to the right node
        node* left = sorted_char_freq.top(); sorted_char_freq.pop();
        node* right = sorted_char_freq.top(); sorted_char_freq.pop();

        // FIX 3: Remove unnecessary comparison and swap (min heap handles this)
        // The compare_nodes function is not needed since we're using proper min heap

        //creating a parent node with left and right node as children.
        //The parent node's ch is combined frequency, not combined characters
        node* parent = new node('\0', left->freq + right->freq);  // Use null char for internal nodes

        //parent's left child is the lowest node and right node is the next to lowest node
        parent->left = left;
        parent->right = right;
        sorted_char_freq.push(parent);
    }

    //after the loop only the root remains on the priority queue
    root = sorted_char_freq.empty() ? nullptr : sorted_char_freq.top();
}

//a recursive function to assign an unique prefix proof binary code for each leaf node or character
void huffman_base::build_codes(node* n, string code) {
    if (n == nullptr) return;

    //cheks if the node is a leaf node or not
    //leaf nodes don't have children so left and right are null by definition
    if (n->left == nullptr && n->right == nullptr) {
        //Handle single character case
        codes[n->ch] = code.empty() ? "0" : code;
        return;
    }

    //recursive call of the left child of node n, traverses and appends 0 when goes to left child
    build_codes(n->left, code + "0");
    //recursive call of the right child of node n, traverses and appends 1 when goes to right child
    build_codes(n->right, code + "1");
}

void huffman_base::display_code() const {
    cout << "\nHuffman Codes:\n";
    for (auto pair: codes) {
        cout << pair.first << " : " << pair.second << endl;
    }
}

encoder::encoder(string t): huffman_base({}, {}) {  // FIX 4: Initialize with empty maps
    text = t;
    encoded_str = "";
}

//Inherited class of huffman_base
//process() is a virtual method of huffman_base
//by overriding, runtime/dynamic polymorphism was implemented
void encoder::process() {
    // FIX 5: Clear previous data
    freq_map.clear();
    codes.clear();

    build_frequency_map(text);              //builds the frequency map of the text
    build_huffman_tree();                   //from the frequency map, this method builds the huffman tree (min heap)
    build_codes(root, "");          //traversing the huffman tree, code is assigned to each leaf node carrying a char

    //This for loop iterates over the codes map and assigns code for each character
    //in the text string into the coded string where the message is encoded
    encoded_str.clear();  // Clear previous encoded string
    for (char c: text) {
        encoded_str += codes[c];
    }
}

//the function is made const to make the method's attributes immutable after initialization
void encoder::save_to_file(const string& filename) const {
    ofstream out(filename);                         //creates an output stream for the file

    //checks if the file has opened or not
    if (out.fail()) {
        cerr << "Error opening file. Try again." << endl;
        return;
    }

    out << encoded_str << endl;                     //feeding the encoded string into the output file stream

    //this for loop iterates over the unordered map for the char and their huffman code pair
    for (auto pair: codes) {
        //the ASCII value for each char is fed in the stream first for efficiency and reliability
        //then the related char's code is saved as well in the same line
        out << (int)(pair.first) << " " << pair.second << endl;
    }

    out.close();                                    //closes the output file stream, clears heap
}

//overloaded save to file function for appending to existing file.
void encoder::save_to_file(const string &filename, const bool append_mode) const {
    ofstream out;

    //checks if the user has selected append mode or not.
    if (append_mode) {
        out.open(filename, ios::app);
    } else {
        out.open(filename);
    }

    if (out.fail()) {
        cerr << "Error opening file. Try again" << endl;
        return;
    }

    out << encoded_str << endl;
    for (auto pair: codes) {
        out << (int)pair.first << " " << pair.second << endl;
    }

    out.close();
}

void encoder::show_packing_density() const {
    const double size_of_normal_str = text.size() * 8;
    const double size_of_encoded_str = encoded_str.size();
    const double packing_density = (size_of_encoded_str/size_of_normal_str) * 100;

    cout << fixed << setprecision(2);
    cout << "\nPacking Density: " << packing_density << "%" << endl;
}

decoder::decoder(string s, unordered_map<string, char> r_c) : huffman_base({}, {}) { 
    encoded_str = s;
    reversed_codes = r_c;
}

void decoder::code_decoder(const string &encoded_filename){
    ifstream in(encoded_filename);              //creating an input file stream

    //error handling
    if (!in) {
        cerr << "Error Loading file. Try again" << endl;
        return;
    }

    //reads the first line from the encoded file which is the encoded message and stores in encoded_str
    getline(in, encoded_str);
    int ascii;                                  //for storing the ascii value of the chars from the file
    string code;                                //huffman code to store in the map

    //clearing previous data
    reversed_codes.clear();
    codes.clear();

    //from the input stream, the integer is fed into ascii and string into the code variables
    while (in >> ascii >> code) {
        reversed_codes[code] = (char)ascii;
        codes[(char)ascii] = code;  // Also populate codes for display
    }

    in.close();                                 //closing the input file stream
}

void decoder::process() {
    //completes the decoder process to decode and display the message
    string current_code = "";
    string decoded_text = "";

    for (char bit : encoded_str) {
        current_code += bit;
        if (reversed_codes.find(current_code) != reversed_codes.end()) {
            decoded_text += reversed_codes[current_code];  //adds the decoded character
            current_code = "";  //resets for next character
        }
    }

    cout << "Decoded Text: " << decoded_text << endl;
}

huffman_base::~huffman_base() = default;

encoder::~encoder() = default;

decoder::~decoder() = default;
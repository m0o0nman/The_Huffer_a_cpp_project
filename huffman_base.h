#ifndef HUFFMAN_BASE_H
#define HUFFMAN_BASE_H
#include <unordered_map>
#include <string>
#include "node.h"

using namespace std;
class huffman_base {
protected:
    node* root;                                 //root of the huffman tree
    unordered_map<char, int> freq_map;          //unordered map for frequency with key as char
    unordered_map<char, string> codes;          //unordered map for huffman code with key as char

    //makes an unordered map for char frequency, character is key and it;s frequency is value
    void build_frequency_map(const string& text);
    //builds the huffman tree from the frequency map
    void build_huffman_tree();
    //builds the code for each character from the huffman tree
    void build_codes(node* n, string code);
public:
    //displays the code for each character
    void display_code();
    virtual void process() = 0;

    huffman_base(unordered_map <char, int> f_m, unordered_map<char, string> cd);
};

class encoder: public huffman_base {
private:
    string text;
    string encoded_str;

public:
    //constructor
    explicit encoder(string t);
    //function to save coded data into a file
    void save_to_file(const string& filename) const;
    //overloaded function to appened into existing file
    void save_to_file(const string& filename, bool append_mode) const;
    //shows how efficiently the data was compressed
    void show_packing_density() const;
    //overridden virtual function to implement the process of building huffman tree
    void process() override;
};

class decoder : public huffman_base {
private:
    string encoded_str;
    unordered_map<string, char> reversed_codes;

public:
    decoder(string s, unordered_map<string, char> r_c);

};


#endif //HUFFMAN_BASE_H

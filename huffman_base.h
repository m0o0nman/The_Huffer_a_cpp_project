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
    void display_code() const;
    //virtual function to process the encoding/decoding through polymorphism
    virtual void process() = 0;
    virtual ~huffman_base();

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
    //overloaded function to append into existing file
    void save_to_file(const string& filename, bool append_mode) const;
    //shows how efficiently the data was compressed
    void show_packing_density() const;
    //overridden virtual function to implement the process of building huffman tree through polumorphism
    void process() override;
    ~encoder() override;
};

class decoder : public huffman_base {
private:
    string encoded_str;                             //stores the encoded message
    unordered_map<string, char> reversed_codes;     //huffman code and its char pair with the code being the key

public:
    //constructor to initialize member variables
    decoder(string s, unordered_map<string, char> r_c);
    //decoding the huffman code and retrieving the chars
    void code_decoder(const string& encoded_filename);
    //overridden virtual function to implement the process of decoding the encoded message
    void process() override;
    ~decoder() override;

};


#endif //HUFFMAN_BASE_H

#include "login_signup.h"
#include <iostream>
#include <chrono>
#include <queue>
#include <random>
#include <fstream>
#include <functional>
#include <sstream>
#include <iomanip>
#include <unordered_map>

using namespace std;

Login_Signup::Login_Signup(unordered_map<string, pair<string, string>>& ud, string& fn) : user_database(ud), filename(fn) {

}

string Login_Signup::generate_salt(const size_t length) {

    //character set to randomly pick from
    static const string char_set = "012345678ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    //A pseudo random number generator (PRNG) with a seed of the time difference between the moment of initialization to epoch
    mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> dist(0, char_set.size() - 1);

    string salt;

    for (int i = 0; i < length; i++) {
        //the dist object selects a number with the predefined range from the PRNG and picks a char from char_set
        salt += char_set[dist(generator)];
    }

    return salt;

}

string Login_Signup::generate_hash(const string &password, const string &salt) {
    hash<string> hasher;        //An object of the hash class template which hashes strings
    size_t hash_value = hasher(password + salt);

    stringstream ss;            //ss is a string stream object which creates a stream of string
    ss << hex <<hash_value;     //the hash value, an unsigned integer, is turned into hexadecimal and then fed to the stream

    return ss.str();            //The stream is then converted into a string
}

bool Login_Signup::username_exists(const string& username) const {
    return user_database.count(username) > 0;
}

bool Login_Signup::register_user(string username, string password) {
    if (username_exists(username)) {
        return false;
    }

    if (username.empty() || password.empty()) {
        return false;
    }
        //If user is not found then salt is generated and password is hashed
        string salt = generate_salt();
        string hashed_password = generate_hash(password, salt);

        //The username is saved as the key in the unordered map. And the salt and password is saved as a pair two strings.
        user_database[username] = make_pair(salt, hashed_password);
        save_to_file();
        return true;
}

bool Login_Signup::verify_login(const string &username, const string &password) {
    //An iterator is used to access the key value(username) and the pair(salt and hashed password)
    auto it = user_database.find(username);
    if (it == user_database.end()) {
        cerr << "   Username not found" << endl;
        return false;                                                       //If the username doesn't exist, returns false
    }

        string retrieved_salt = it -> second.first;                     //The salt is in the second part's(pair) first element
        string stored_hash = it -> second.second;                       //The stored hash is the second part's(pair) second element
        string computed_hash = generate_hash(password, retrieved_salt);    //A new hash is made using user input for password and the retireved salt for that username

        return computed_hash == stored_hash;
}

void Login_Signup::save_to_file() {   //Saves new user data into the file
    ofstream file(filename);                                //A file object is created

    if (!file) {
        cerr << "Error opening file: "<< filename <<endl;  //Prints error if the input stream couldn't read the file
    } else {
        //An iterator is used to first load the new user;s info then it is fed into the file stream
        for (const auto& entry : user_database) {
            file << entry.first << ":" <<entry.second.first << ":" <<entry.second.second <<endl;
        }
    }
}

bool Login_Signup::load_from_file() {  //Loads info(username, salt, hashed password) into the unordered map
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: "<< filename <<endl;    //Prints error if the input stream couldn't read the file
    } else {
        string line;

            while (getline(file, line)) {                //Reads line by line into the file
            size_t colon_1 = line.find(':');                 //Each value is seperated by a colon so the position of the colon is taken
            size_t colon_2 = line.find(':',colon_1 + 1);

            //The string::npos is a constant of size_t used to indicate that the find() method didn't find the argument
            //So, if the colon positions are not found the following block of copying username, salt and hahsed passord
            //from the file and feeding into the unordered map is not performed
            if (colon_1 != string::npos && colon_2 != string::npos) {
                //The substr(start, len) function takes 2 parameters, starting index and length
                string username = line.substr(0, colon_1);                          //The index of 0 to index till position of colon_1(say 5) is username
                string salt = line.substr(colon_1 + 1, colon_2 - colon_1 - 1);      //The next index of colon_1(5 + 1) to the index before colon_2(say 13 - 1) - colon_1 (5) == 13 - 1 - 5 = 6, so 7 indexes will be read (salt)
                string hashed_password = line.substr(colon_2 + 1);                    //The hashed password stretches from the next index of colon_2 to the end of string

                //The substrings are stored in the private user_database
                user_database[username] = make_pair(salt, hashed_password);
            }
        }
    }
    return true;
}
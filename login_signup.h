#ifndef LOGIN_SIGNUP_H
#define LOGIN_SIGNUP_H

#include <string>
#include <unordered_map>

using namespace std;
class Login_Signup {
    string& filename;
    unordered_map<string, pair<string, string>>& user_database;


    //Function to generate salt randomly
    static string generate_salt(size_t length = 7);
    //Function to crate a password by hashing user input and generated salt
    static string generate_hash(const string& password, const string& salt);

public:
    //Functions for user authentification
    bool username_exists(const string& username) const;                                      //Check if username already exists
    bool register_user(string username, string password);            //Registers new user, saves user info(username, salt, hashed password) into file
    bool verify_login(const string& username, const string& password);      //Varifies login by matching username, affiliated salt and the hashed password

    //Functions to save or retrieve user data
    void save_to_file();
    bool load_from_file();
    //constructor
    Login_Signup(unordered_map<string, pair<string, string>> &ud, string &fn);
};


#endif //LOGIN_SIGNUP_H

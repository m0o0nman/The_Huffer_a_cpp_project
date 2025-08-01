#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <windows.h>
#include "login_signup.h"
#include "huffman_base.h"

using namespace std;

void display_title();
int get_input();

int main() {
    display_title();

    // Initialize Login_Signup system with proper constructor parameters
    unordered_map<string, pair<string, string>> user_database;
    string user_file = "users.txt";
    Login_Signup user(user_database, user_file);
    user.load_from_file();

    // Main authentication loop (similar to test.cpp)
    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit" << endl;
        int opt = get_input();

        if (opt == 1) {
            // Registration flow
            string uname, pass;
            cout << "Username: ";
            cin.ignore();
            getline(cin, uname);
            cout << "Password: ";
            getline(cin, pass);

            if (user.register_user(uname, pass)) {
                cout << "Registered Successfully!\n";
            } else {
                cout << "Username already exists!\n";
            }
        }
        else if (opt == 2) {
            // Login flow
            string uname, pass;
            cout << "Username: ";
            cin.ignore();
            getline(cin, uname);
            cout << "Password: ";
            getline(cin, pass);

            if (user.verify_login(uname, pass)) {
                cout << "Login successful! Welcome, " << uname << "\n";

                // Huffman operations loop (after successful login)
                while (true) {
                    cout << "\n1. Encode Message\n2. Decode Message\n3. Logout\nChoose: ";
                    int choice = get_input();

                    if (choice == 1) {
                        // Encoding flow
                        string input_text, encoded_file_name;
                        cout << "Enter message: ";
                        cin.ignore();
                        getline(cin, input_text);
                        cout << "Save encoded message to (e.g. encoded.txt): ";
                        getline(cin, encoded_file_name);

                        // Create encoder with proper constructor (just the text)
                        encoder enc(input_text);
                        enc.process();
                        enc.save_to_file(encoded_file_name);
                        enc.show_packing_density();
                        enc.display_code();
                        cout << "\nMessage encoded successfully to " << encoded_file_name << endl;
                    }
                    else if (choice == 2) {
                        // Decoding flow
                        string encoded_filename;
                        cout << "Enter file to decode: ";
                        cin.ignore();
                        getline(cin, encoded_filename);

                        // Create decoder with proper constructor parameters
                        unordered_map<string, char> empty_reversed_codes;
                        decoder dec("", empty_reversed_codes);
                        dec.code_decoder(encoded_filename);
                        dec.display_code();
                        dec.process();
                    }
                    else if (choice == 3) {
                        // Logout
                        cout << "Logging out...\n";
                        break;
                    }
                }
            } else {
                cout << "Login failed!\n";
            }
        }
        else if (opt == 3) {
            // Exit program
            break;
        }
    }

    // Save user data before exit (Login_Signup saves automatically in register_user)
    cout << "Thank you for using The Huffer!\n";
    return 0;
}

void display_title() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    string title = "The Huffer";
    int padding = (consoleWidth > title.length()) ? (consoleWidth - title.length()) / 2 : 0;

    // Setting text color to green
    SetConsoleTextAttribute(hConsole, 10);
    cout << string(padding, ' ') << title << endl;

    // Resetting text color
    SetConsoleTextAttribute(hConsole, 7);
}

int get_input() {
    int choice;
    while (true) {
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice >= 1 && choice <= 3) {
            return choice;
        }
        cout << "Enter a number between 1 and 3\n";
    }
}
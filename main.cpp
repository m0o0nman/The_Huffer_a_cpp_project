#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <windows.h>
#include "login_signup.h"
#include "huffman_base.h"

void display_title();
int ip();
using namespace std;
int main() {
    display_title();

    //Initialize Login_Signup
    std::unordered_map<std::string, std::pair<std::string, std::string>> user_database;
    std::string user_file = "users.txt";
    Login_Signup auth(user_database, user_file);
    auth.load_from_file();

    //User Authentication Loop
    bool logged_in = false;
    while (!logged_in) {
        cout << "\n1. Login\n2. Register\n3. Exit\n";
        int choice = ip();

        //handling login
        if (choice == 1) {

            //verifying username and password
            string username, password;
            cout << "Username: ";
            cin >> username;
            cin.ignore();

            cout << "Password: ";
            cin >> password;
            cin.ignore();

            if (auth.verify_login(username, password)) {
                logged_in = true;
                cout << "Login successful!\n";
            } else {
                cout << "Invalid username or password.\n";
            }

            //encode decode flow
            if (auth.verify_login(username, password)) {
                cout << "Login successful!\nWelcome " << username << endl;
                cout <<"\n1. Encode message\n2. Decode message\n3. Exit\n";
                int option = ip();

                //encode flow
                if (option == 1) {
                    //taking message to encode
                    string input_msg, encoded_filename;
                    cout << "Enter message: ";
                    getline(cin, input_msg);
                    cout << "Save encoded message to(ex: example.txt): ";
                    getline(cin, input_msg);

                    //encoding
                    encoder enc(input_msg);
                    enc.process();
                    enc.save_to_file(encoded_filename);
                    enc.show_packing_density();
                    cout <<"\nMessage encoded successfully at " << encoded_filename <<endl;
                } else if (choice == 2) {
                    string encoded_file;
                    cout << "Enter filename (ex: example.txt):";
                }
            }

        //handling registration
        } else if (choice == 2) {

            //taking username and passwords
            string username, password;
            cout << "Choose a username: ";
            cin >> username;
            cout << "Choose a password: ";
            cin >> password;
            if (auth.register_user(username, password)) {
                cout << "Registration successful!\n";
            } else {
                cout << "Username already exists.\n";
            }
        } else if (choice == 3) {

            //taking file name to decode
            string encoded_filename;
            cout << "Enter encoded filename(ex: example.txt): ";
            getline(cin, encoded_filename);

            //decoding flow
            decoder dec("", {});
            dec.code_decoder(encoded_filename);
            dec.process();
            std::cout << "File decoded successfully!\n";
        } else {

        }
    }

    // 3. Huffman Coding Loop
    while (true) {
        cout << "\n1. Encode message\n2. Decode message\n3. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            // Handle encoding
            string message, original_filename, output_filename;
            cout << "Enter the message to encode: ";
            cin.ignore(); // To consume the newline character left by std::cin
            getline(cin, message);

            std::cout << "Enter the name for the file to save(Ex: example.txt): ";
            std::cin >> original_filename;

            // Save the original message
            std::ofstream out_original(original_filename);
            out_original << message;
            out_original.close();
            std::cout << "Original message saved to " << original_filename << "\n";

            std::cout << "Enter the name for the encoded file: ";
            std::cin >> output_filename;

            // Create an encoder and process the message
            encoder enc(message);
            enc.process();
            enc.save_to_file(output_filename);
            enc.show_packing_density();
            std::cout << "File encoded successfully!\n";

        } else if (choice == 2) {
            // Handle decoding
            std::string encoded_filename;
            std::cout << "Enter the name of the file to decode: ";
            std::cin >> encoded_filename;

            // Create a decoder and process the file
            decoder dec("", {});
            dec.code_decoder(encoded_filename);
            dec.process();
            std::cout << "File decoded successfully!\n";

        } else if (choice == 3) {
            break; // Exit the Huffman loop
        }
    }

    return 0;
}

void display_title() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    std::string title = "The Huffer";
    int padding = (consoleWidth > title.length()) ? (consoleWidth - title.length()) / 2 : 0;

    //setting text color to green
    SetConsoleTextAttribute(hConsole, 10);

    std::cout << std::string(padding, ' ') << title << std::endl;

    //resetting text color
    SetConsoleTextAttribute(hConsole, 7);
}

int ip() {
    int choice;

    while (true) {
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= 3) {
            return choice;
        }
        cerr << "Enter a number between 1 and 3" <<endl;
    }
}
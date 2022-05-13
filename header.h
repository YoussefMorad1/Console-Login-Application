#ifndef ASSINGMENT4_HEADER_H
#define ASSINGMENT4_HEADER_H

#include <string>
#include <map>
#include <set>

using std::string;

struct user_profile
{
    string ID, name, email, phone_number, password;
};




                                         // Starting Program Functions

bool check_system_load(); // checks the system files are loaded successfully
void load_profiles_to_map(); // loads all system to the program

void welcomeScreen(); // shows welcome screen and the available options
string take_menu_choice(); // take the user's option and check it's a valid one





                                        // Registering New User Functions

// The MAIN Register Function (takes Name input, Writes new user to all files and to map, calls other register functions)
void personalInfo();

    // Takes input for UserName and checks its pattern
    string allUsername();
    // Checks if USerName was used before
    void readUsername(const string& uname);

    // prints the requirements for a strong password
    void show_pass_req();
    // takes a password input twice and check they match
    string pass_match();
        // checks the password is strong
        string take_strong_pass();

    // Takes input for Email and checks its pattern
    string allEmail();
        // Checks that email wasn't used before
        void readEmail(const string& email);

    // Takes input for Mobile Number and checks its pattern (Egyptian Phone Number)
    string allMob();
        // Checks that number wasn't used before
        void readMob(const string& mob);

    // Function appends a specific string to a specific file
    void writeAll(const string& type, const string& file_name);

    // Function takes keeps taking input in a string until it matches a pattern (returns the matched string)
    string check(const string& pattern);
    // Function checks if string has no space
    bool check_space(string name);
    // Function takes compare a string with a pattern
    bool check_noCIN(const string& name,const string& checkPatt);



                                        // Login Functions

// Main Login Function
string login();

    // takes user's input for UserName and checks if it exists, (user has only 3 attempts)
    string take_login_ID();

    // takes user's input for Password and checks it's the correct pass, (user has only 3 attempts)
    string take_login_pass(const string& current_user_name);


                                    // Changing Password Functions

// Main Change Password Function
string change_pass();

    // creates a set of all old passwords
    void create_pass_set(const string& curr_user);

    // takes input of the last profile's password and checks it is correct
    string entering_last_pass(const string& current_pass);

    // takes input (twice) of the new password, makes sure it's strong,
    // makes sure the 2 input Passwords match, makes sure this password doesn't match an old pass
    string entering_new_pass();

    // add the new password to profiles-file under the specified user
    void add_pass_to_fProfiles(const string& curr_user, const string& new_pass);

    // add the new password to all-passwords-file for the specified user
    void add_pass_to_fPasswords(const string& curr_user, const string& new_pass);




                                    // repetitive used Functions

// take input hidden with '*' while being taken
string take_hidden_input();

// and encrypting, decrypting function to save our data securely
string encrypt_decrypt(const string& str, int key);



#endif //ASSINGMENT4_HEADER_H

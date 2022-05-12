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

bool check_system_load();

string take_hidden_input();

void load_profiles_to_map();

void welcomeScreen();
string take_menu_choice();

string encrypt_decrypt(const string& str, int key);

string login();
    string take_login_ID();
    string take_login_pass(const string& current_user_name);

string change_pass();
    void create_pass_set(const string& curr_user);
    string entering_last_pass(const string& current_pass);
    string entering_new_pass();
    void add_pass_to_fPasswords(const string& curr_user, const string& new_pass);
    void add_pass_to_fProfiles(const string& curr_user, const string& new_pass);


void personalInfo();

    string check(string name,string pattern); //
    bool check_space(string name);

    void allUsername();
        void readUsername();

    void show_pass_req();
        string pass_match();
        string take_strong_pass();

    void allEmail();
        void readEmail();

    void allMob();
        void readMob();

    void writeAll(string type, string file_name);

#endif //ASSINGMENT4_HEADER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <set>
#include <conio.h>
using namespace std;



bool check_system_load();

string take_hidden_input();
void dont_close();

struct user_profile
{
    string ID, name, email, phone_number, password;
//    user_profile(string&  id, string& name_, string& mail, string& number, string& pass)
//        : ID{id}, name{name_}, email{mail}, phone_number{number}, password{pass}
//    {
//    }
};


void add_profile_to_file(const user_profile& target_profile);


map <string, user_profile> profile_map;
void load_profiles_to_map();

string login();
    string take_login_ID();
    string take_login_pass(const string& current_user_name);

string change_pass();
    set <string> pass_set;
    void create_pass_set(const string& curr_user);
    string entering_last_pass(const string& current_pass);
    string entering_new_pass();
    void add_pass_to_fPasswords(const string& curr_user, const string& new_pass);
    void add_pass_to_fProfiles(const string& curr_user, const string& new_pass);


fstream fProfiles;
fstream fPasswords;
const string fProfiles_name = "profiles.txt";
const string fPasswords_name = "passwords.txt";

int main()
{
    fProfiles.open(fProfiles_name);
    char c; string s;
    while(c = fProfiles.get()){
        s += c;
    }
    cout << s;
    dont_close();
}

bool check_system_load(){
    fProfiles.open(fProfiles_name);
    fPasswords.open(fPasswords_name);

    if(fProfiles.fail() || fPasswords.fail()){
        fProfiles.close();
        fPasswords.close();
        cout << "Failed to load the system.. Make sure both (" << fProfiles_name << ") and ("
        << fPasswords_name << ") files do exist.. and Try Again!\n";
        return false;
    }
    else{
        fProfiles.close();
        fPasswords.close();
        return true;
    }
}

string take_hidden_input(){
    char p;
    string pass;
    p = _getch();
    while( p != '\r' ){
        if(isdigit(p) || isalpha(p) || isspace(p) || ispunct(p)){
            cout << '*';
            pass += p;
        }
        else if(p == '\b'){
            cout << "\b \b";
            pass.pop_back();
        }
        p = _getch();
    }
    cout << '\n';
    return pass;
}

void dont_close(){
    cout << "\npress any key to exit..";
    getch();
}

void add_profile_to_file(const user_profile& target_profile){

    fProfiles.open(fProfiles_name, ios::app);

    fProfiles << '\n' << target_profile.ID << '\n' << target_profile.name << '\n'
    << target_profile.email << '\n' << target_profile.phone_number << '\n'
    << target_profile.password << '\n';

    fProfiles.close();

}

void load_profiles_to_map(){

    fProfiles.open(fProfiles_name, ios::in);

    string temp_line, temp_map_key;
    int i = -1;
    while(!fProfiles.eof()){
        getline(fProfiles, temp_line);
        if(i == 0){
            temp_map_key = temp_line;
            profile_map[temp_map_key].ID = temp_line;
        }
        else if(i == 1){
            profile_map[temp_map_key].name = temp_line;
        }
        else if (i == 2){
            profile_map[temp_map_key].email = temp_line;
        }
        else if (i == 3){
            profile_map[temp_map_key].phone_number = temp_line;
        }
        else if (i == 4){
            profile_map[temp_map_key].password = temp_line;
            i = -2;
        }
        i++;
    }

//    for(auto elem : profile_map){
//        cout << elem.first;
//        cout << " ID: " << elem.second.ID <<  "  name: " <<  elem.second.name << "  email: "
//        << elem.second.email << "  numb: " << elem.second.phone_number
//        << "  pass: " << elem.second.password << '\n';
//    }

    fProfiles.close();
}

string take_login_ID(){

    string in_user_name;
    cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('=') << "\n"
         << setw(20) << setfill(' ') << "UserName(ID): ";

    cin >> in_user_name;

    while (profile_map.find(in_user_name) == profile_map.end()){

        cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('-') << "\n";
        cout << "UserName(ID) Wasn't Found..\nTry again or Enter 0 to go back\n"
             << setw(20) << setfill(' ') << "User Name (ID): ";

        cin >> in_user_name; //*add option to just fall back to main menu

        if(in_user_name == "0"){
            return "0";
        }
    }

    cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('=') << "\n\n";
    return in_user_name;

}


string take_login_pass(const string& current_user_name){

    string in_pass;
    cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('=') << "\n"
         << setw(20) << setfill(' ') << "Password: ";



    bool correct_pass = false;
    for(int i = 2; i > -1; --i){

        in_pass = take_hidden_input();

        if(profile_map[current_user_name].password == in_pass){
            correct_pass = true;
            break;
        }

        if(i == 0)
            break;

        cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('-') << "\n"
             << "Wrong Password.. You have ONLY " << i << " more attempts!\n" << setw(20) << setfill(' ') << "Password: ";

    }

    cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('=') << "\n\n";

    if(correct_pass)
        return in_pass;
    else
        return "0";
}


string login(){

    string in_user_name = take_login_ID();

    if(in_user_name == "0"){
        return "0";
    }


    string in_pass = take_login_pass(in_user_name);


    if(in_pass != "0"){
        cout << "Successful login, Welcome " << profile_map[in_user_name].name << "!\n";
        return in_user_name;
    }
    else{
        cout << "Sorry, You are denied to access the system..\nYou will be returned to the main menu";
        return "0"; //*I should use this 0 as a sign to return to main menu
    }

}

void create_pass_set(const string& curr_user){
    fPasswords.open(fPasswords_name);

    string current_pass;
    bool is_ID = false, id_found = false;
    while (!fPasswords.eof()) {
        string line;
        getline(fPasswords, line);

        if (is_ID) {
            if (line == curr_user) {
                id_found = true;
            } else if (!pass_set.empty()) {
                break;
            }
        }

        if (id_found && !line.empty() && !is_ID) {
            pass_set.insert(line);
            if (pass_set.size() == 1) {
                current_pass = line;
            }
        }

        is_ID = line.empty(); // after every empty line an ID
    }
    fPasswords.close();
}

string entering_last_pass(const string& current_pass){

    cout << setw(20) << setfill(' ') << "Enter you last Password: ";

    for (int i = 2; i > -1; --i) {

        string user_last_pass = take_hidden_input();

        if (user_last_pass == current_pass) {
            return user_last_pass;
        }

        if (i == 0) {
            return "0";
        }

        cout << "Wrong Password.. You have ONLY " << i << " more attempts!\n" << setw(20) << setfill(' ')
             << "Enter you last Password: ";

    }
    return "0";

}

string entering_new_pass(){

    cout << setw(20) << setfill(' ') << "Now Enter your new Password: ";
    string new_pass = take_hidden_input();

    while (pass_set.find(new_pass) != pass_set.end() or new_pass == "0") {
        if(new_pass == "0"){
            return "0";
        }
        cout << "This Password matches an old Password..\nPlease Enter a new Password (or 0 to go back):\n";
        new_pass = take_hidden_input();
    }

    cout << setw(20) << setfill(' ') << "ReEnter your new Password: ";
    string repeated_new_pass = take_hidden_input();

    while (new_pass != repeated_new_pass) {

        if(new_pass == "0" or repeated_new_pass == "0"){
            return "0";
        }

        cout << "\nSorry the 2 Passwords don't match!\nTry Again! (or Enter 0 to go back)\n";

        cout << setw(20) << setfill(' ') << "Now Enter your new Password (or 0 to go back):\n";
        new_pass = take_hidden_input();

        while (pass_set.find(new_pass) != pass_set.end() or new_pass == "0") {
            if(new_pass == "0"){
                return "0";
            }
            cout << "This Password matches an old Password..\nPlease Enter a new password: ";
            new_pass = take_hidden_input();
        }

        cout << setw(20) << setfill(' ') << "ReEnter your new Password: ";
        repeated_new_pass = take_hidden_input();

    }

    pass_set.insert(new_pass);

    return new_pass;
}

void add_pass_to_fPasswords(const string& curr_user, const string& new_pass) {

    fPasswords.close();
    fPasswords.open(fPasswords_name);

    string strOfNewFile;
    bool first_line = true;
    while (!fPasswords.eof()) {
        string line;
        getline(fPasswords, line);

        if (first_line) {
            strOfNewFile += line;
            first_line = false;
        } else {
            strOfNewFile += '\n';
            strOfNewFile += line;
        }

        if (line == curr_user) {
            strOfNewFile += '\n';
            strOfNewFile += new_pass;
        }
    }

    fPasswords.close();
    fPasswords.open(fPasswords_name, ios::out);
    fPasswords << strOfNewFile;
    fPasswords.close();

}

void add_pass_to_fProfiles(const string& curr_user, const string& new_pass){

    fProfiles.close();
    fProfiles.open(fProfiles_name);

    string strOfNewFile;
    bool first_line = true;
    bool found_id = false;
    int i = 0;
    while(!fProfiles.eof()){
        string line;
        getline(fProfiles, line);

        if(line == curr_user){
            found_id = true; // i = 0 when line = id, so it will be 4 when line = pass
        }

        if(first_line){
            strOfNewFile += line;
            first_line = false;
        }
        else if (i == 4){
            strOfNewFile += '\n';
            strOfNewFile += new_pass;
        }
        else{
            strOfNewFile += '\n';
            strOfNewFile += line;
        }

        if(found_id)
            i++;
    }

    fProfiles.close();
    fProfiles.open(fProfiles_name, ios::out);
    fProfiles << strOfNewFile;
    fProfiles.close();

}

string change_pass(){

    string target_user_id = login();

    if(target_user_id == "0"){
        return "0";
    }

    create_pass_set(target_user_id);

    string last_pass = entering_last_pass(profile_map[target_user_id].password);

    if(last_pass == "0") {
        return "0";
    }

    string new_pass = entering_new_pass();

    if(new_pass == "0"){
        return "0";
    }

    add_pass_to_fPasswords(target_user_id, new_pass);

    add_pass_to_fProfiles(target_user_id, new_pass);


    cout << "Your Password was updated successfully!\n";
    return "1";

}




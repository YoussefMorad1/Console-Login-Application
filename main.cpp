#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <conio.h>
using namespace std;

struct user_profile
{
    string ID, name, email, phone_number, password;
};

bool check_system_load();

string take_hidden_input();

map <string, user_profile> profile_map;
void load_profiles_to_map();

void welcomeScreen();
string take_menu_choice();

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


void personalInfo();

    string check(string name,string pattern);
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
    string uname, mob, email;

fstream fProfiles;
fstream fPasswords;
const string fProfiles_name = "profiles.txt";
const string fPasswords_name = "passwords.txt";

int main()
{
    if(!check_system_load()){
        return 0;
    }

    load_profiles_to_map();

    while(true) {
        welcomeScreen();

        string choice = take_menu_choice();

        if(choice == "1"){
            personalInfo();
        }
        else if(choice == "2"){

            if(login() == "0"){
                continue;
            }

        }
        else if(choice == "3"){

            if(change_pass() == "0"){
                continue;
            }

        }
        else if(choice == "4"){
            break;
        }
    }

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

void welcomeScreen(){
    cout << "Welcome User!\n\n" << setw(40) << setfill('=') << "\n";

    cout << setw(10) << setfill(' ') << left << "||" << setw(20) << setfill(' ') << "1. Register"
        << setw(10) << setfill(' ') << right << "||\n" ;

    cout << setw(10) << setfill(' ') << left << "||" << setw(20) << setfill(' ') << "2. Login"
         << setw(10) << setfill(' ') << right << "||\n" ;

    cout << setw(10) << setfill(' ') << left << "||" << setw(20) << setfill(' ') << "3. Change Password"
         << setw(10) << setfill(' ') << right << "||\n" ;

    cout << setw(10) << setfill(' ') << left << "||" << setw(20) << setfill(' ') << "4. Exit"
         << setw(10) << setfill(' ') << right << "||\n" ;

    cout << setw(40) << setfill('=') << "\n" << "\n";
}

string take_menu_choice(){
    string option;
    cout << ">>";
    cin >> option;

    while(option != "1" && option != "2" && option != "3" && option != "4"){
        cout << "Invalid Input.. Please choose a number from the Menu\n>>";
        cin >> option;
    }

    return option;
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
        else if(p == '\b' && !pass.empty()){
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

//___________________________________

string check(string name,string pattern) {
    while (true) {
        cin.clear();
        cin.sync();
        getline(cin, name);
        regex patterns(pattern);
        if(regex_match(name,patterns)){
            cout<<endl;
            break;
        }
        else{
            cout<<"Invalid....Try again"<<endl;
            continue;
        }

    }
    return name;
}

bool check_noCIN(string name,string checkPatt) {
    regex patternz(checkPatt);
    if (regex_match(name,patternz)) {
        return true;
    }
    else {
        return false;
    }
}

//make email used once
void readEmail() {
    string fileMails;

    //read file
    fProfiles.open("profiles.txt");

    while (fProfiles.good()) {
        fProfiles >> fileMails;

        //if email been registered before
        regex similar (fileMails);
        if(regex_match(email,similar)) {
            cout<<"This email already has an accout.."<<endl;
            fProfiles.close();
            allEmail();
        }
        else {
            continue;
        }
    }
    fProfiles.close();
}

void writeAll(string type, string file_name) {
    fProfiles.open(file_name,ios::out|ios::app);
    fProfiles<<type<<'\n';
    fProfiles.close();
}

bool check_space(string name) {
    for(int i=0;i<name.length();i++) {
        if (name[i]!=32) {
            return true;
        }
    }
}

void allEmail() {
    cout<<"Please enter your email"<<endl;
    while(true) {
        getline(cin, email);
        if (check_noCIN(email,"(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+") && check_space(email)) {
            readEmail();
            break;
        }
        else {
            cout << "Please enter a valid email..Try again" << endl;
            continue;
        }
    }
}

//-----------------------------------------------------------
//make username used once
void readUsername() {
    string fileMails;

    //read file
    fProfiles.open("profiles.txt");

    while (fProfiles.good()) {
        fProfiles >> fileMails;

        //if username has been used before
        regex similar (fileMails);
        if(regex_match(uname,similar)){
            cout<<"This username is already used before.."<<endl;
            fProfiles.close();
            allUsername();
        }
        else {
            continue;
        }
    }
    fProfiles.close();
}

void allUsername() {
    cout<<"Please enter a Username"<<endl;
    while(true) {
        getline(cin, uname);
        if (check_noCIN(uname,"[A-Za-z0-9_.]+") && check_space(uname)) {
            readUsername();
            break;
        }
        else {
            cout << "Please enter a valid Username..Try again" << endl;
            continue;
        }
    }
}

//---------------------------------------------------------------------------------------------------------
//make mobile number used once
void readMob() {
    string fileMails;

    //read file
    fProfiles.open("profiles.txt");

    while (fProfiles.good()) {
        fProfiles >> fileMails;

        //if mobile number has been used before
        regex similar (fileMails);
        if(regex_match(mob,similar)){
            cout<<"This Mobile number is already used before.."<<endl;
            fProfiles.close();
            allMob();
        }
        else {
            continue;
        }
    }
    fProfiles.close();
}

void allMob() {
    cout<<"Please enter your Mobile number "<<endl;
    while(true) {
        getline(cin, mob);
        if (check_noCIN(mob,"01(0|1|2|5)[0-9]{8}") && check_space(mob)) {
            readMob();
            break;
        }
        else {
            cout << "Please enter a valid Mobile number..Try again" << endl;
            continue;
        }
    }
}

//---------------------------------------------------------------------------------------
//Pesonal information function
void personalInfo() {
    string fname, pass, lname;

    cout << "Please enter the following:\nFirst Name-->";
    fname = check(fname, "[a-zA-z-]+");

    cout << "Last Name-->";
    lname = check(lname, "[a-zA-z- ]+");

    //username
    allUsername();
    cout<<"\nUsername Accepted\n"<<endl;

    // password
    show_pass_req();
    pass = pass_match();
    cout << endl;

    //email
    allEmail();
    cout<<"\nEmail Accepted\n"<<endl;

    //mobile number
    allMob();
    cout<<"\nMobile Number Accepted\n"<<endl;

    // write all info to Profile_file
    writeAll('\n'+uname, fProfiles_name);
    writeAll(fname+' '+lname, fProfiles_name);
    writeAll(email, fProfiles_name);
    writeAll(mob, fProfiles_name);
    writeAll(pass, fProfiles_name);

    writeAll('\n'+uname, fPasswords_name);
    writeAll(pass, fPasswords_name);


    cout<<"Personal information has been filled successfully"<<endl;
}


void show_pass_req() {
    cout << "Strong password requirements:\n";
    cout << "1. At least 12 characters.\n";
    cout << "2. A mixture of both uppercase and lowercase letters.\n";
    cout << "3. A mixture of letters and numbers.\n";
    cout << "4. At least one special character (!, @, ?, ..)\n";
}


string take_strong_pass() {
    string pass;
    bool upper = false;
    bool lower = false;
    bool number = false;
    bool special = false;
    bool strong = false;

    regex upper_exp{"[A-Z]+"};
    regex lower_exp{"[a-z]+"};
    regex number_exp{"[0-9]+"};
    regex special_exp{"[$&+,:;=?@#|'<>.^*()%!-]+"};

    while (!strong) {
        cout << "Enter a password: ";
        pass = take_hidden_input();

        if (pass.length() < 12) {
            cout << "Invalid Password. Please Try Again.\n";
        }
        else {
            upper = regex_search(pass, upper_exp);
            lower = regex_search(pass, lower_exp);
            number = regex_search(pass, number_exp);
            special = regex_search(pass, special_exp);

            if (upper+lower+number+special < 4) {
                cout << "Invalid Password. Please Try Again.\n";
            }
            else {
                strong = true;
            }
        }
    }
    return pass;
}

string pass_match() {
    string pass, pass2;
    bool match = false;
    while (!match) {
        pass = take_strong_pass();
        cout << "Enter password again to verify: ";
        pass2 = take_hidden_input();
        if (pass == pass2) {
            cout << "Strong Password Saved.\n";
            match = true;
        }
        else {
            cout << "Passwords do not match. Please Try Again.\n";
        }
    }
    return pass;
}




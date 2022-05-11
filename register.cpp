#include <iostream>
#include <regex>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <set>
#include <conio.h>

using namespace std;
void welcomeScreen();
string take_menu_choice();
void personalInfo();
string check(string name,string pattern);
void readEmail();
void allEmail();
void readUsername();
void allUsername();
void readMob();
void allMob();
void writeAll(string type);
bool check_space(string name);
void show_pass_req();
string take_hidden_input();
string take_strong_pass();
string pass_match();
string uname,mob,email;
fstream file;

int main() {
    while(true) {
        welcomeScreen();
        string choice = take_menu_choice();

        if(choice == "1") { 
            personalInfo();
        }
        break;
    }
}


string check(string name,string pattern) {
    while (true) {
        cin>>name;
        cin.ignore();
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
    file.open("profiles.txt");

    while (file.good()) {
        file >> fileMails;

        //if email been registered before
        regex similar (fileMails);
        if(regex_match(email,similar)) {
            cout<<"This email already has an accout.."<<endl;
            file.close();
            allEmail();
        }
        else {
            continue;
        }
    }
    file.close();
}

void writeAll(string type) {
    file.open("profiles.txt",ios::out|ios::app);
    file<<type<<'\n';
    file.close();
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
        file.open("profiles.txt");

        while (file.good()) {
            file >> fileMails;

            //if username has been used before
            regex similar (fileMails);
            if(regex_match(uname,similar)){
                cout<<"This username is already used before.."<<endl;
                file.close();
                allUsername();
            }
            else {
                continue;
            }
        }
        file.close();
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
    file.open("profiles.txt");

    while (file.good()) {
        file >> fileMails;

        //if mobile number has been used before
        regex similar (fileMails);
        if(regex_match(mob,similar)){
            cout<<"This Mobile number is already used before.."<<endl;
            file.close();
            allMob();
        }
        else {
            continue;
        }
    }
    file.close();
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
    lname = check(lname, "[a-zA-z-]+");

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

    // write all info to file
    writeAll('\n'+uname);
    writeAll(fname+' '+lname);
    writeAll(email);
    writeAll(mob);
    writeAll(pass);

    cout<<"Personal information has been filled successfully"<<endl;
}

void welcomeScreen() {
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

string take_menu_choice() {
    string option;
    cout << ">>";
    cin >> option;
    cin.ignore();
    while(option != "1" && option != "2" && option != "3" && option != "4"){
        cout << "Invalid Input.. Please choose a number from the Menu\n>>";
        cin >> option;
        cin.ignore();
    }

    return option;
}

void show_pass_req() {
    cout << "Strong password requirements:\n";
    cout << "1. At least 12 characters.\n";
    cout << "2. A mixture of both uppercase and lowercase letters.\n";
    cout << "3. A mixture of letters and numbers.\n";
    cout << "4. At least one special character (!, @, ?, ..)\n";
}

string take_hidden_input() {
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
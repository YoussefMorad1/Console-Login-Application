#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <map>
#include <set>
#include <conio.h>
using namespace std;

string take_hidden_input();
void dont_close();


struct user_profile
{
    string ID, name, email, phone_number, password;
};

void add_profile_to_file(const user_profile& target_profile);
void load_profiles_to_map();
string login();
void change_pass();


fstream fProfiles;
fstream fPasswords;

map <string, user_profile> profile_map;

int main()
{
    load_profiles_to_map();
    change_pass();
    dont_close();
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
    int s;
    s = getch();
}

void add_profile_to_file(const user_profile& target_profile){

    fProfiles.open("profiles.txt", ios::app);

    fProfiles << '\n' << target_profile.ID << '\n' << target_profile.name << '\n' << target_profile.email << '\n'
    << target_profile.phone_number << '\n' << target_profile.password << '\n';

    fProfiles.close();

}

void load_profiles_to_map(){

    fProfiles.open("profiles.txt", ios::in);

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
//        cout << " ID: " << elem.second.ID <<  " name: " <<  elem.second.name << " email: "
//        << elem.second.email << " numb: " << elem.second.phone_number << " pass: " << elem.second.password << '\n';
//    }

    fProfiles.close();
}

string login(){


    string in_user_name;
    cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('=') << "\n"
         << setw(20) << setfill(' ') << "UserName(ID): ";

    cin >> in_user_name;

    while (profile_map.find(in_user_name) == profile_map.end()){

        cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('-') << "\n";
        cout << "UserName(ID) Wasn't Found..\n"
        << setw(20) << setfill(' ') << "User Name (ID): ";

        cin >> in_user_name; //*add option to just fall back to main menu

    }

    cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('=') << "\n\n";



    string in_pass;
    cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('=') << "\n"
         << setw(20) << setfill(' ') << "Password: ";



    bool correct_pass = false;
    for(int i = 2; i > -1; --i){

        in_pass = take_hidden_input();

        if(profile_map[in_user_name].password == in_pass){
            correct_pass = true;
            break;
        }

        if(i == 0)
            break;

        cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('-') << "\n"
        << "Wrong Password.. You have ONLY " << i << " more attempts!\n" << setw(20) << setfill(' ') << "Password: ";

    }

    cout << setw(20) << setfill(' ') << "" << setw(30) << setfill('=') << "\n\n";

    if(correct_pass){
        cout << "Successful login, Welcome " << profile_map[in_user_name].name << "!\n";
        return in_user_name;
    }
    else{
        cout << "Sorry, You are denied to access the system..\nYou will be returned to the main menu";
        return "0"; //*I should use this 0 as a sign to return to main menu
    }

}

void change_pass(){

    string target_user_id = login();

    if(target_user_id != "0"){

        fPasswords.open("passwords.txt");
        set <string> pass_set;


        string current_pass;
        bool is_ID = false, id_found = false;
        while(!fPasswords.eof()){
            string line;
            getline(fPasswords, line);

            if(is_ID){
                if(line == target_user_id){
                    id_found = true;
                }
                else if(!pass_set.empty()){
                    break;
                }
            }

            if(id_found && !line.empty() && !is_ID){
                pass_set.insert(line);
                if(pass_set.size() == 1){
                    current_pass = line;
                }
            }

            is_ID = line.empty(); // after every empty line an ID
        }

        cout << setw(20) << setfill(' ') << "Enter you last Passowrd: ";

        bool correct_oldPass = false;
        for(int i = 2; i > -1; --i){

            string user_last_pass = take_hidden_input();

            if(user_last_pass == current_pass){
                correct_oldPass = true;
                break;
            }

            if(i == 0)
                break;

             cout << "Wrong Password.. You have ONLY " << i << " more attempts!\n" << setw(20) << setfill(' ')
             << "Enter you last Passowrd: ";

        }

        if(correct_oldPass){ //*else go back to main menu

            cout << setw(20) << setfill(' ') << "Now Enter your new Password: ";
            string new_pass = take_hidden_input();

            while(pass_set.find(new_pass) != pass_set.end()){
                cout << "This Password matches an old Password..\nPlease Enter a new password: ";
                new_pass = take_hidden_input();
            }

            cout << setw(20) << setfill(' ') << "ReEnter your new Password: ";
            string repeated_new_pass = take_hidden_input();

            while(new_pass != repeated_new_pass){
                cout << "\nSorry the 2 input Passowrds don't match!\nTry Again!\n";

                cout << setw(20) << setfill(' ') << "Now Enter your new Password: ";
                new_pass = take_hidden_input();

                while(pass_set.find(new_pass) != pass_set.end()){
                    cout << "This Password matches an old Password..\nPlease Enter a new password: ";
                    new_pass = take_hidden_input();
                }

                cout << setw(20) << setfill(' ') << "ReEnter your new Password: ";
                repeated_new_pass = take_hidden_input();
            }

            pass_set.insert(new_pass);

            fPasswords.close();
            fPasswords.open("passwords.txt");

            string strOfNewFile; bool first_line = true;
            while(!fPasswords.eof()){
                string line;
                getline(fPasswords, line);

                if(first_line) {
                    strOfNewFile += line;
                    first_line = false;
                }
                else{
                    strOfNewFile += '\n';
                    strOfNewFile += line;
                }

                if(line == target_user_id){
                    strOfNewFile += '\n';
                    strOfNewFile += new_pass;
                }
            }

            fPasswords.close();
            fPasswords.open("passwords.txt", ios::out);
            fPasswords << strOfNewFile;


            fProfiles.close();
            fProfiles.open("profiles.txt");

            strOfNewFile = "";
            first_line = true;
            bool found_id = false;
            int i = 0;
            while(!fProfiles.eof()){
                string line;
                getline(fProfiles, line);

                if(line == target_user_id){
                    found_id = true; // i = 0 when line = id so it will be 4 when line = pass
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
            fProfiles.open("profiles.txt", ios::out);
            fProfiles << strOfNewFile;

            cout << "Your Password was updated successfully!\n";

        }

    }
}

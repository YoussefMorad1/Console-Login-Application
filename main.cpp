#include "header.h"

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


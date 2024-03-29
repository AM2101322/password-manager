#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CSV.h"
using namespace std;

int main()
{
    string users_file = "user_file";

    string choice; // Changed to string type
    cout << "what would you like to do \n"
         << "1. make a new user \n"
         << "2. log in to a user \n";
    getline(cin >> ws, choice);

    int choice_num = stoi(choice); // Convert choice to an integer

    if (choice_num == 1)
    {
        create_user(users_file);
        return 0;
    }
    if (choice_num == 2)
    {
        string user_username;
        string user_pass;
        string key = "123";

        cout << "what is your username: ";
        verify_password(users_file, user_username, user_pass);

        if (verify_password)
        {
            string action;
            cout << " welcom back "<< user_username <<" what would you like to do \n"
            << "1. add a password to your file\n"
            << "2. see an old password\n"
            << "3. edit an old password\n"
            << "4. deleat a password\n" 
            << "5. see all your passwords: \n";
            getline(cin >> ws, action);

            int action_num = stoi(action);
            if (action_num == 1)
            {
                create_file(user_username,key);
            }
            if (action_num == 2)
            {
                string website;
                cout << "for what website: ";
                getline(cin >> ws, website);
                get_password(user_username, website, key);
            }
            if (action_num == 3)
            {   string website;
                string new_password;
                cout << "for what website: ";
                getline(cin >> ws, website);
                cout << "what is the new password: ";
                getline(cin >> ws, new_password);
                edit_password(user_username, website,new_password);
            }
             if (action_num == 4)
             {
                string website;
                cout << "for what website: ";
                getline(cin >> ws, website);
                delete_password(user_username, website);
             }
             if (action_num == 5)
             {
                display_file(user_username,key);
             }
        }
        else {
            cout << "Password verification failed." << endl;
        }

        return 0;
    }
    else{
        cout << " chose 1 or 2 ";
    }
    return 0;
}
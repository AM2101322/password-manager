#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CSV.h"
using namespace std;

int main()
{
    string file_name;
    string website;
    string website_c;
    string new_pass;
    string password_c;
    
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
    }
    if (choice_num == 2)
    {
        cout << "what is your username: ";
        verify_password(users_file); 
        

    
    }
    else{
        cout << " chose 1 or 2 ";
    }
    return 0;
}



//make users 
//https://youtu.be/fTdkqOS5_ro?si=qTB7xvjQmR5Sj0gt 👆👇
// give users passwords
// save user passwords 
// encrypt the password
// (make yser that the location of the file is saved with the username and password) 
// make sure the user can get the password back 
// make it save what the password is for 
// save the password on a file (encrypt)
// the user selects what password they want
//(use CSV for this 👆👇)
// after the user selected the password is saved on the clip bord

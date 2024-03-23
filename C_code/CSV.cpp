#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CSV.h"
using namespace std;

void create_file(const string& file_name) {
    ifstream fin(file_name);
    if (fin.fail()) {
        // File doesn't exist, create a new one
        ofstream fout(file_name);
        if (!fout.is_open()) {
            cout << "Error creating file." << endl;
            return;
        }
        fout.close();
        fin.open(file_name);
    }

    string website, password;
    cout << "Enter the website you are saving the password for: " << endl;
    getline(cin >> ws, website);

    // Check if the website already exists
    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string existing_website = line.substr(0, pos);
            if (existing_website == website) {
                cout << "Website already exists. Password not added." << endl;
                fin.close();
                return;
            }
        }
    }
    fin.close();

    cout << "Enter the password: " << endl;
    getline(cin >> ws, password);

    // Append the new website and password to the file
    ofstream fout(file_name, ios::out | ios::app);
    if (!fout.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    fout << website << "," << password << "\n";
    fout.close();

    cout << "Password added successfully." << endl;
}
void create_user(const string& file_name) {
    ifstream fin(file_name);
    if (fin.fail()) {
        // File doesn't exist, create a new one
        ofstream fout(file_name);
        if (!fout.is_open()) {
            cout << "Error creating file." << endl;
            return;
        }
        fout.close();
        fin.open(file_name);
    }

    string user, password;
    cout << "what is your username: " << endl;
    getline(cin >> ws, user);

    // Check if the user already exists
    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string existing_user = line.substr(0, pos);
            if (existing_user == user) {
                cout << "user alrady exists" << endl;
                fin.close();
                return;
            }
        }
    }
    fin.close();

    cout << "Enter the password for your user : " << endl;
    getline(cin >> ws, password);

    // Append the new user and password to the file
    ofstream fout(file_name, ios::out | ios::app);
    if (!fout.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    fout << user << "," << password << "\n";
    fout.close();

    cout << "user added successfully." << endl;
}
string get_password(const string& file_name, const string& target_website) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        return "";
    }

    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string website = line.substr(0, pos);
            string password = line.substr(pos + 1);
            if (website == target_website) {
                fin.close();
                cout << "The password for " << website << " is " << password << endl;
                return password;
            }
        }
    }

    fin.close();
    cout << "No website with that name." << endl;
    return ""; // Website not found
}

void edit_password(const string& file_name, const string& target_website, const string& new_password) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    bool found = false; // Flag to indicate if the website was found and password updated

    ofstream fout("temp.txt");
    if (!fout.is_open()) {
        cout << "Error creating temp file." << endl;
        fin.close();
        return;
    }

    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string website = line.substr(0, pos);
            string password = line.substr(pos + 1);
            if (website == target_website) {
                password = new_password;
                found = true; // Set found to true if website is found and password updated
            }
            fout << website << "," << password << "\n";
        }
    }

    fin.close();
    fout.close();

    if (!found) {
        cout << "No website with that name found. Password not updated." << endl;
        return;
    }

    if (remove(file_name.c_str()) != 0) {
        cout << "Error deleting old file." << endl;
        return;
    }

    if (rename("temp.txt", file_name.c_str()) != 0) {
        cout << "Error renaming file." << endl;
        return;
    }

    cout << "Password for " << target_website << " updated successfully." << endl;
}


void display_file(const string& file_name) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    cout << "Contents of the file:" << endl;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    fin.close();
}

void delete_password(const string& file_name, const string& target_website) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    ofstream fout("temp.txt");
    if (!fout.is_open()) {
        cout << "Error creating temp file." << endl;
        fin.close();
        return;
    }

    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string website = line.substr(0, pos);
            if (website != target_website) {
                fout << line << endl; // Write line to temp file if website doesn't match
            }
        }
    }

    fin.close();
    fout.close();

    if (remove(file_name.c_str()) != 0) {
        cout << "Error deleting old file." << endl;
        return;
    }

    if (rename("temp.txt", file_name.c_str()) != 0) {
        cout << "Error renaming file." << endl;
        return;
    }

    cout << "Password for " << target_website << " deleted successfully." << endl;
}

bool verify_password(const string& file_name, string& username, string& password) {
    int attempts = 5;

    cout << "Enter your user: ";
    getline(cin >> ws, username);

    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        return false;
    }

    bool user_found = false;
    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string stored_user = line.substr(0, pos);
            if (stored_user == username) {
                user_found = true;
                break;
            }
        }
    }
    fin.close();

    if (!user_found) {
        cout << "User does not exist." << endl;
        return false;
    }

    while (attempts > 0) {
        cout << "Enter the password for " << username << ": ";
        getline(cin >> ws, password);

        fin.open(file_name);
        if (!fin.is_open()) {
            cout << "Error opening file." << endl;
            return false;
        }

        bool password_matched = false;
        while (getline(fin, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string stored_user = line.substr(0, pos);
                string stored_password = line.substr(pos + 1);
                if (stored_user == username && stored_password == password) {
                    password_matched = true;

                }
            }
        }
        fin.close();

        if (password_matched) {
            cout << "Password verified successfully." << endl;
            return true;
        } else {
            attempts--;
            if (attempts > 0) {
                cout << "Wrong password. " << attempts << " attempts left." << endl;
            } else {
                cout << "You have exceeded the maximum number of attempts." << endl;
            }
        }
    }

    return false;
}

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // For remove and rename functions

using namespace std;

void create_file(const string& file_name) {
    fstream fout;
    fout.open(file_name, ios::out | ios::app);
    if (!fout.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string website, password;
    cout << "Enter the website you are saving the password for: " << endl;
    getline(cin >> ws, website);

    cout << "Enter the password: " << endl;
    getline(cin >> ws, password);

    fout << website << "," << password << "\n";
    fout.close();
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
                cout<< "the password for "<< website << " is " << password << endl;
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
            }
            fout << website << "," << password << "\n";
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

    cout << "Password for " << target_website << " updated successfully." << endl;
}

int main() {
    string file_name;
    cout << "Enter the file name: " << endl;
    getline(cin >> ws, file_name);
    create_file(file_name);

    string website;
    cout << "Enter the website you want the password for: " << endl;
    getline(cin >> ws, website);
    get_password(file_name,website);

    string password_c;
    cout << "what password do you want to change: " << endl;
    getline(cin >> ws, password_c);
    string new_pass;
    cout << "what pass do u want is the now password: " << endl;
    getline(cin >> ws, new_pass);
    edit_password(file_name,password_c,new_pass);

    return 0;
}

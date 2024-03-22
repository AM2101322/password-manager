#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // For remove and rename functions

using namespace std;

void create_file(const string& file_name) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string website, password;
    cout << "Enter the website you are saving the password for: " << endl;
    getline(cin >> ws, website);

    // Check if the website already exists in the file
    string line;
    while (getline(fin, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            string existing_website = line.substr(0, pos);
            if (existing_website == website) {
                cout << "Website already exists." << endl;
                return;
            }
        }
    }

    fin.close();

    // If the website does not exist, prompt for password and add it to the file
    ofstream fout(file_name, ios::out | ios::app);
    if (!fout.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    cout << "Enter the password: " << endl;
    getline(cin >> ws, password);

    fout << website << "," << password << "\n";
    fout.close();

    cout << "Password added successfully." << endl;
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
int main() {
    string file_name;
    cout << "Enter the file name: " << endl;
    getline(cin >> ws, file_name);
   
    string website;
    cout << "Enter the website you want the password for: " << endl;
    getline(cin >> ws, website);


    string password_c;
    cout << "what password do you want to change: " << endl;
    getline(cin >> ws, password_c);

    string new_pass;
    cout << "what pass do u want is the now password: " << endl;
    getline(cin >> ws, new_pass);
    edit_password(file_name,password_c,new_pass);
    

    delete_password(file_name, website);

    display_file(file_name);

    return 0;
}

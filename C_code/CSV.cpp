#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void create_file(std::string file_name) {
    // file pointer
    fstream fout;

    // Read the input
    int i;
    std::string password;
    std::string website;

    // opens an existing csv file or creates a new file.
    fout.open(file_name, ios::out | ios::app); // Use file_name variable here

    cout << "what is the website you are saving the password for: " << endl;
    std::getline(std::cin >> std::ws, website);
    

    
   
    cout << "what is the password: " << endl;
    std::getline(std::cin >> std::ws, password);
    
    // Insert the data to file
    fout << website << ","
        << password
         << "\n";
    

    // Close the file
    fout.close();
}


int main() {
    std::string file_name;
    cout << "Enter the file name: " << endl;
    std::getline(std::cin >> std::ws, file_name);
    create(file_name);
    return 0;
}

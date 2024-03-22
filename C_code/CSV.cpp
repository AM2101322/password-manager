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
void read_file(std::string file_name) 
{ 

	// File pointer 
	fstream fin; 

	// Open an existing file 
	fin.open("file_name", ios::in); 

	// Get the roll number 
	// of which the data is required 
	int rollnum, roll2, count = 0; 
	cout << "Enter the roll number "
		<< "of the student to display details: "; 
	cin >> rollnum; 

	// Read the Data from the file 
	// as String Vector 
	vector<string> row; 
	string line, word, temp; 

	while (fin >> temp) { 

		row.clear(); 

		// read an entire row and 
		// store it in a string variable 'line' 
		getline(fin, line); 

		// used for breaking words 
		stringstream s(line); 

		// read every column data of a row and 
		// store it in a string variable, 'word' 
		while (getline(s, word, ', ')) { 

			// add all the column data 
			// of a row to a vector 
			row.push_back(word); 
		} 

		// convert string to integer for comparision 
		roll2 = stoi(row[0]); 

		// Compare the roll number 
		if (roll2 == rollnum) { 

			// Print the found data 
			count = 1; 
			cout << "Details of Roll " << row[0] << " : \n"; 
			cout << "Name: " << row[1] << "\n"; 
			cout << "Maths: " << row[2] << "\n"; 
			cout << "Physics: " << row[3] << "\n"; 
			cout << "Chemistry: " << row[4] << "\n"; 
			cout << "Biology: " << row[5] << "\n"; 
			break; 
		} 
	} 
	if (count == 0) 
		cout << "Record not found\n"; 
} 


int main() {
    std::string file_name;
    cout << "Enter the file name: " << endl;
    std::getline(std::cin >> std::ws, file_name);
    create(file_name);
    return 0;
}

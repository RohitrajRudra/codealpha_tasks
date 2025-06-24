
//TASK -2 LOGIN AND REGISTRATION SYSTEM


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to check if username already exists
bool isUsernameTaken(const string& username) {
    ifstream file("users.txt");
    string user, pass;
    while (file >> user >> pass) {
        if (user == username) {
            return true;
        }
    }
    return false;
}

// Registration function
void registerUser() {
    string username, password;

    cout << "=== Registration ===" << endl;
    cout << "Enter username: ";
    cin >> username;

    // Check for duplicates
    if (isUsernameTaken(username)) {
        cout << "Error: Username already taken!" << endl;
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Store in file
    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "Registration successful!" << endl;
}

// Login function
void loginUser() {
    string username, password;
    bool success = false;

    cout << "=== Login ===" << endl;
    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    string user, pass;

    while (file >> user >> pass) {
        if (user == username && pass == password) {
            success = true;
            break;
        }
    }
    file.close();

    if (success) {
        cout << "Login successful! Welcome, " << username << "." << endl;
    } else {
        cout << "Error: Invalid username or password." << endl;
    }
}

// Main menu
int main() {
    int choice;

    while (true) {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Register\n2. Login\n3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

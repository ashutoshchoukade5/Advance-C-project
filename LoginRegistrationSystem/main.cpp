
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> loadUserData(const string& filename) {
    unordered_map<string, string> users;
    ifstream file(filename);
    if (file.is_open()) {
        string username, password;
        while (file >> username >> password) {
            users[username] = password;
        }
        file.close();
    }
    return users;
}

void saveUserData(const unordered_map<string, string>& users, const string& filename) {
    ofstream file(filename, ofstream::trunc);
    if (file.is_open()) {
        for (const auto& pair : users) {
            file << pair.first << " " << pair.second << endl;
        }
        file.close();
    }
}

bool registerUser(unordered_map<string, string>& users, const string& filename) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "Username already exists." << endl;
        return false;
    }
    cout << "Enter password: ";
    cin >> password;
    users[username] = password;
    saveUserData(users, filename);
    return true;
}

bool loginUser(const unordered_map<string, string>& users) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    if (users.find(username) != users.end() && users.at(username) == password) {
        cout << "Login successful." << endl;
        return true;
    } else {
        cout << "Invalid username or password." << endl;
        return false;
    }
}

int main() {
    const string filename = "users.txt";
    unordered_map<string, string> users = loadUserData(filename);

    int choice;
    do {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users, filename);
                break;
            case 2:
                loginUser(users);
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

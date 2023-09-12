#include <iostream>
#include <string>
#include <map>
#include <cstdlib> 
#include <algorithm> 
#include <ctime> 
#include <random> 
#include <fstream> 
using namespace std;


string ShuffleString(const string& input) {
    string shuffled = input;
    shuffle(shuffled.begin(), shuffled.end(), mt19937(time(0))); 
    return shuffled;
}


string GeneratePassword(const string& keywords, int length) {
    string shuffledKeywords = ShuffleString(keywords);
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    string password;

 
    int randomIndex = rand() % 26; 
    password += 'A' + randomIndex;

    randomIndex = rand() % 10; 
    password += '0' + randomIndex;

    randomIndex = rand() % 14; 
    password += "!@#$%^&*"[randomIndex];

    for (int i = 3; i < length; ++i) {
        if (i < shuffledKeywords.length()) {
            password += shuffledKeywords[i];
        } else {
            randomIndex = rand() % characters.length();
            password += characters[randomIndex];
        }
    }

    password = ShuffleString(password);

    return password;
}


void SavePasswordsToFile(const map<string, string>& passwords) {
    ofstream file("passwords.txt");
    if (file.is_open()) {
        for (const auto& entry : passwords) {
            file << entry.first << " " << entry.second << "\n";
        }
        file.close();
    } else {
        cerr << "Error: Unable to open the file for saving passwords.\n";
    }
}

void LoadPasswordsFromFile(map<string, string>& passwords) {
    ifstream file("passwords.txt");
    if (file.is_open()) {
        string customName, password;
        while (file >> customName >> password) {
            passwords[customName] = password;
        }
        file.close();
    } else {
        cerr << "Warning: Unable to open the file for loading passwords. It may not exist yet.\n";
    }
}

void DeletePassword(map<string, string>& passwords, const string& name) {
    auto it = passwords.find(name);
    if (it != passwords.end()) {
        passwords.erase(it);
        cout << "Password deleted successfully!\n";
        SavePasswordsToFile(passwords);
    } else {
        cout << "Password not found.\n";
    }
}

int main() {
    map<string, string> passwordStorage;

    LoadPasswordsFromFile(passwordStorage);

    while (true) {
        int choice;
        cout << "Menu:\n";
        cout << "1. Generate Password\n";
        cout << "2. Store Password\n";
        cout << "3. Display Stored Passwords\n";
        cout << "4. Delete Password\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string keywords;
                cout << "Enter keywords: ";
                cin >> keywords;

                int passwordLength;
                cout << "Select password length: ";
                cin >> passwordLength;

                string generatedPassword = GeneratePassword(keywords, passwordLength);
                cout << "Generated Password: " << generatedPassword << "\n";
                break;
            }
            case 2: {
                string customName;
                cout << "Enter a custom name for the password: ";
                cin >> customName;

                string generatedPassword;
                cout << "Enter the password: ";
                cin >> generatedPassword;

                passwordStorage[customName] = generatedPassword;
                cout << "Password stored successfully!\n";
                break;
            }
            case 3: {
                cout << "Stored Passwords:\n";
                for (const auto& entry : passwordStorage) {
                    cout << "Name: " << entry.first << ", Password: " << entry.second << "\n";
                }
                break;
            }
            case 4: {
                string nameToDelete;
                cout << "Enter the name of the password to delete: ";
                cin >> nameToDelete;
                DeletePassword(passwordStorage, nameToDelete);
                break;
            }
            case 5:
                cout << "Goodbye!\n";
                SavePasswordsToFile(passwordStorage);
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


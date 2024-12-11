#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <regex>
using namespace std;
class User {
private:
string email;
string username;
string password;
public:
    User() {}
User(const string& email, const string& user, const string& pass)
: email(email), username(user), password(pass) {
    }
    string getEmail() const { 
        return email;
    }
    string getUsername() const {
        return username; 
    }
    string getPassword() const { 
        return password;
    }
    void saveToFile() {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
    file << email << " " << username << " " << password << endl;
    file.close();
        }
    }
    static bool emailExists(const string& email) {
    ifstream file("users.txt");
    string fileEmail, fileUser, filePass;
    while (file >> fileEmail >> fileUser >> filePass) {
    if (fileEmail == email) {
    return true;
            }
        }
        return false;
    }
    static bool authenticate(const string& email, const string& password) {
    fstream file("users.txt");
    string fileEmail, fileUser, filePass;
    while (file >> fileEmail >> fileUser >> filePass) {
    if (fileEmail == email && filePass == password) {
    return true;
            }
        }
     return false;
    }
    static bool resetPassword(const string& email, const string& newPassword) {
    ifstream file("users.txt");
    ofstream tempFile("temp.txt");
    bool userFound = false;
    string fileEmail, fileUser, filePass;
    while (file >> fileEmail >> fileUser >> filePass) {
    if (fileEmail == email) {
      userFound = true;
    tempFile << fileEmail << " " << fileUser << " " << newPassword << endl;
            }
            else {
                tempFile << fileEmail << " " << fileUser << " " << filePass << endl;
            }
        }
        file.close();
        tempFile.close();
        remove("users.txt");
        rename("temp.txt", "users.txt");
        return userFound;
    }
};
class System {
private:
    bool validateEmail(const string& email) {
        const regex emailRegex(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
        return regex_match(email, emailRegex);
    }
public:
    void registerUser() {
        string email, username, password;
        cout << "\n--- Registration ---\n";
        cout << "Enter email: ";
        cin >> email;
        if (!validateEmail(email)) {
            cout << "Invalid email format. Please include '@' and a valid domain.\n";
            return;
        }
        if (User::emailExists(email)) {
            cout << "Email already exists. Try a different one.\n";
            return;
        }
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        User newUser(email, username, password);
        newUser.saveToFile();
        cout << "Registration successful!\n";
    }
    void loginUser() {
        string email, password;
        cout << "\n--- Login ---\n";
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;

        if (User::authenticate(email, password)) {
            cout << "Login successful! Welcome, " << email << "!\n";
        }
        else {
            cout << "Invalid email or password.\n";
        }
    }
    void forgotPassword() {
        string email, newPassword;
        cout << "\n--- Forgot Password ---\n";
        cout << "Enter your email: ";
        cin >> email;
    if (User::emailExists(email)) {
            cout << "Enter your new password: ";
            cin >> newPassword;
    if (User::resetPassword(email, newPassword)) {
                cout << "Password reset successful!\n";
            }
            else {
                cout << "Error resetting password. Please try again.\n";
            }
        }
        else {
            cout << "Email not found.\n";
        }
    }
void displayMenu() {
        int choice;
        do {
            cout << "\n--- Main Menu ---\n";
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Forgot Password\n";
            cout << "4. Exit\n";
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
                forgotPassword();
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }
};
int main() {
    System system;
    system.displayMenu();
    return 0;
}
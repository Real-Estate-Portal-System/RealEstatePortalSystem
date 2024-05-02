#include "Admin.h"
#include "welcome.h"
#include "User.h"
#include "PropertyManager.h"
#include <iostream>
#include <fstream>
using namespace std;
//The Hash map to store user data
static ::unordered_map<string, Admin > admins;

Admin::Admin() : isAdmin(true) {}
Admin::Admin(const string& username, const string& password,
    const string& fname, const string& lname, bool isAdmin) :
    username(username), password(password),
    fname(fname), lname(lname), isAdmin(isAdmin) {}

string Admin::getAdminUsername()const {
    return username;
}
string Admin::getAdminPassword()const {
    return password;
}
string Admin::getAdminFname()const {
    return fname;
}
string Admin::getAdminLname()const {
    return lname;
}
bool Admin::isAdminUser() const {
    return isAdmin;
}

void Admin::loadAdminDataFromFile(const string& admin_data) {
    ifstream inFile(admin_data);
    if (!inFile) {
        // Error opening file
        cerr << "Error: Unable to open file '" << admin_data << "' for reading." << endl;

        return;
    }
    string saved_username, saved_password, saved_fname, saved_lname;

    while (inFile >> saved_username >> saved_password >> saved_fname >> saved_lname) {
        admins[saved_username] = Admin(saved_username, saved_password, saved_fname, saved_lname);
    }

    inFile.close();
}
void Admin::writeAdminDataToFile(const string& admin_data) {
    ofstream outFile(admin_data);
    if (!outFile) {
        // Error opening file
        cerr << "File not found!" << endl;
        return;
    }

    for (const auto& pair : admins) {
        const Admin& user = pair.second;
        outFile << user.getAdminUsername() << '\t'
            << user.getAdminPassword() << '\t'
            << user.getAdminFname() << '\t'
            << user.getAdminLname() << '\t' << endl;
    }

    outFile.close();
}
bool Admin::signupAdmin() {
    string username, password, hashpassword, fname, lname;
    bool isAdmin = true;

    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists
    if (admins.find(username) != admins.end()) {
        system("cls");
        cout << "Username already exists. Please choose another username." << endl;
        return false;
    }

    cout << "Enter password: ";
    cin >> password;
    hashpassword = hash_djb2(password);

    cout << "Enter first name: ";
    cin >> fname;
    cout << "Enter last name: ";
    cin >> lname;

    admins[username] = Admin(username, hashpassword, fname, lname, isAdmin);
    system("cls");
    cout << "Sign up successful, please login" << endl;
    return true;
}
bool Admin::loginAdmin() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    // Check if username exists
    if (admins.find(username) == admins.end()) {
        system("cls");
        cout << "User not found." << endl;
        welcome_page_admin();
        return false;

    }

    cout << "Enter password: ";
    cin >> password;
    string hashedPassword = hash_djb2(password); // Hash the entered password

    // Check if password matches
    if (admins[username].getAdminPassword() == hashedPassword) {
        system("cls");
        cout << "Login successful!" << endl;
        Admin admin = admins[username];
        admin.admin_menu();
        return true;
    }
    else {
        system("cls");
        cout << "Incorrect password." << endl;
        welcome_page_admin();
        return false;
    }
}

void Admin::admin_menu() {

    bool exitFlag = false;

    PropertyManager manager;
    int choice;

    cout << "Hello , @" << username << endl << endl;
    while (!exitFlag) {
        cout << "*************************" << endl << endl;
        cout << "1.Personal Info" << endl;
        cout << "2.Create new admin" << endl;
        cout << "3.User Management" << endl;
        cout << "4.Manage Listings:" << endl;
        cout << "5.Log out" << endl;

        cin >> choice;

        switch (choice) {
            case 1:
                 system("cls");
                 Admin::admin_personal_info(username);
                 break;
            case 2:
                 system("cls");
                 Admin::createNewAdmin();
                 break;
            case 3:
                 system("cls");
                 user_management();
                 break;

            case 4:
                 manager.propertyManagerAdmin();
                 system("cls");
                 //welcome_page_admin();
                 break;
            case 5:
                 system("cls");
                 exitFlag = true;
                // welcome_page_admin();
                 break;

        }
    }
}
void Admin::admin_personal_info(const string& username) {

    cout << "Username:" << username << '\t';
    cout << "First Name:" << fname << '\t';
    cout << "Last Name:" << lname << endl;


    int answer;
    cout << "Do you want to update info? " << endl;
    cout << "1: Yes " << endl;
    cout << "2: No " << endl;

    cin >> answer;
    switch (answer) {
    case 1:
    { string newPassword, newFirstName, newLastName, hashpassword;

    cout << "Enter new password: ";
    cin >> newPassword;
    hashpassword = hash_djb2(newPassword);

    cout << "Enter new first name: ";
    cin >> newFirstName;

    cout << "Enter new last name: ";
    cin >> newLastName;

    // Call updateInfo function with the collected input
    if (admin_updateInfo(hashpassword, newFirstName, newLastName)) {
        system("cls");
        cout << "User information updated successfully!" << endl;
    }
    else {
        cout << "Failed to update user information. Please try again." << endl;
    }
    }
    break;
    case 2:
        system("cls");

        break;

    default: {
        system("cls");
        cout << "Invalid choice, try again!" << endl;
        admin_personal_info(username);
    }
    }
}
bool Admin::admin_updateInfo(const string& newPassword, const string& newFirstName, const string& newLastName) {


    if (newPassword.empty() && newFirstName.empty() && newLastName.empty()) {
        // No updates provided
        return false;
    }
    this->password = newPassword.empty() ? password : newPassword;
    this->fname = newFirstName.empty() ? fname : newFirstName;
    this->lname = newLastName.empty() ? lname : newLastName;
    admins[username] = Admin(username, newPassword, newFirstName, newLastName, isAdmin);
    return true;
}
void Admin::createNewAdmin() {
    string username, password, fname, lname;
    bool isAdmin = true;

    cout << "Enter username for the new admin: ";
    cin >> username;

    // Check if username already exists
    if (admins.find(username) != admins.end()) {
        cout << "Username already exists. Please choose another username." << endl;
        return;
    }

    cout << "Enter password for the new admin: ";
    cin >> password;

    cout << "Enter first name for the new admin: ";
    cin >> fname;

    cout << "Enter last name for the new admin: ";
    cin >> lname;

    // Create new admin and add to the map
    admins[username] = Admin(username, password, fname, lname, isAdmin);

    system("cls");
    cout << "New admin created successfully!" << endl;
    welcome_page_admin();
}

void Admin::user_management() {
    char answer = 'y';
    int choice;
    cout << "User Management Portol " << endl;
    cout << "1: Create new users " << endl;
    cout << "2: Update user account " << endl;
    cout << "3: Exit " << endl;

    cin >> choice;
    switch (choice) {
    case 1:        
        while (answer == 'y' || answer == 'Y') {
            User::signup();
            cout << "Do you want to add more? (y / n) " << endl;
            cin >> answer;
        }
        system("cls");
        user_management();
        break;
    case 2:   
    {
        system("cls");
        update_user_info();
        break;
    }
    
    
    case 3:
        system("cls");
        admin_menu();
        break;
    default: {
        system("cls");
        cout << "Invalid choice, try again!" << endl;
        user_management();
    }
    }
}

int Admin::countAdmins() {
    int adminsCount = 0;
    for (const auto& pair : admins) {
        const Admin& user = pair.second;
        // Check if the user is not an admin
        if (!user.isAdminUser()) {
            adminsCount++;
        }
    }
    return adminsCount;
}

void welcome_page_admin() {
    bool exitFlag = false;

    while (!exitFlag) {
        cout << "\t\t\t***Admin Portal***\n" << endl;
        cout << "\t\t\t1. Sign Up" << endl;
        cout << "\t\t\t2. Login" << endl;
        cout << "\t\t\t3. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
           case 1:{
            system("cls");
            Admin::signupAdmin();
            welcome_page_admin();
            break;
            }
           case 2:{
            system("cls");
            Admin::loginAdmin();
            break;
           }
           case 3: {
            // Exit
            exitFlag = true;
            system("cls");
            welcome_page();
            break;
           }
        }
    }
}


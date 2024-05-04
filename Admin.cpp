#include "Admin.h"
#include "welcome.h"
#include "User.h"
#include "PropertyManager.h"
#include <iostream>
#include <fstream>

using namespace std;

// The hash map to store user data
static ::unordered_map<string, Admin> admins;

// Default constructor for Admin class
Admin::Admin() : isAdmin(true) {}

// Parameterized constructor for Admin class
Admin::Admin(const string& username, const string& password,
    const string& fname, const string& lname, bool isAdmin) :
    username(username), password(password),
    fname(fname), lname(lname), isAdmin(isAdmin) {}

// Getter for admin username
string Admin::getAdminUsername() const {
    return username;
}

// Getter for admin password
string Admin::getAdminPassword() const {
    return password;
}

// Getter for admin first name
string Admin::getAdminFname() const {
    return fname;
}

// Getter for admin last name
string Admin::getAdminLname() const {
    return lname;
}

// Getter for admin status
bool Admin::isAdminUser() const {
    return isAdmin;
}

// Load admin data from file and populate the hash map
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

// Write all the admin data from the hash map to file
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

// Sign up a new admin
bool Admin::signupAdmin() {
    // Variables to store user input
    string username, password, hashpassword, fname, lname;
    bool isAdmin = true; // Assuming this indicates the user is an admin

    // Prompt user to enter username
    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists in the admins map
    if (admins.find(username) != admins.end()) {
        system("cls");
        cout << "Username already exists. Please choose another username." << endl;
        return false; // Return false to indicate sign-up failure
    }

    // Prompt user to enter password
    cout << "Enter password: ";
    cin >> password;

    // Hash the password (assuming hash_djb2 is a hashing function)
    hashpassword = hash_djb2(password);

    // Prompt user to enter first name
    cout << "Enter first name: ";
    cin >> fname;

    // Prompt user to enter last name
    cout << "Enter last name: ";
    cin >> lname;

    // Create a new Admin object and add it to the admins map
    admins[username] = Admin(username, hashpassword, fname, lname, isAdmin);

    // Clear the screen and inform the user that sign-up was successful
    system("cls");
    cout << "Sign up successful, please login" << endl;
    return true; // Return true to indicate sign-up success

}

// Admin login
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

// Admin menu after login
void Admin::admin_menu() {
    bool exitFlag = false;
    PropertyManager manager;
    int choice;

    cout << "Hello, " << username << "!" << endl << endl;
    while (!exitFlag) {
        cout << "\t********* ADMIN MENU ************\n" << endl << endl;
        cout << "\t\t1. Personal Information" << endl;
        cout << "\t\t2. Create New Admin Account" << endl;
        cout << "\t\t3. User Management" << endl;
        cout << "\t\t4. Manage Listings" << endl;
        cout << "\t\t5. Log Out\n" << endl;


        cout << "Please enter your selection: ";
        while (!(cin >> choice) || choice < 1 || choice > 5 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please choose a number from 1 to 5: ";
        }

        switch (choice) {
        case 1:
            // Display admin personal information
            system("cls");
            Admin::admin_personal_info(username);
            break;
        case 2:
            // Create a new admin
            system("cls");
            Admin::createNewAdmin();
            break;
        case 3:
            // Open user management portal
            system("cls");
            user_management();
            break;
        case 4:
            // Open property manager for admin
            manager.propertyManagerAdmin();
            system("cls");
            break;
        case 5:
            // Logout admin
            system("cls");
            cout << "\nSee you around soon, ADMIN!\n\n" << endl;
            exitFlag = true;
            break;
        }
    }
}

// Update admin personal info
void Admin::admin_personal_info(const string& username) {
    // Display current user information
    cout << "Username: " << username << '\t';
    cout << "First Name: " << fname << '\t';
    cout << "Last Name: " << lname << endl;

    // Prompt the user for action
    int answer;
    cout << "Do you want to update your information?" << endl;
    cout << "1: Yes" << endl;
    cout << "2: No" << endl;
    cout << "Please enter your choice (1 or 2): ";

    // Validate user input
    while (!(cin >> answer) || answer < 1 || answer > 2 || cin.peek() != '\n' || cin.peek() == '.') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter 1 or 2: ";
    }

    // Process user's choice
    switch (answer){
    case 1: {
        string newPassword, newFirstName, newLastName, hashpassword;

        cout << "Enter your new password: ";
        cin >> newPassword;
        hashpassword = hash_djb2(newPassword);

        cout << "Enter your new first name: ";
        cin >> newFirstName;

        cout << "Enter your new last name: ";
        cin >> newLastName;

        // Call updateInfo function with the collected input
        if (admin_updateInfo(hashpassword, newFirstName, newLastName)) {
            system("cls");
            cout << "Your information has been updated successfully!" << endl;
        }
        else {
            cout << "Failed to update your information. Please try again." << endl;
        }
        break;
    }
    case 2:
        system("cls");
        break;
    default: {
        system("cls");
        cout << "Invalid choice. Please try again." << endl;
        // Display personal info again for reference
        admin_personal_info(username);
        break;
    }

    }

}

// Update admin information
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

// Create new admin
void Admin::createNewAdmin() {
    string username, password, fname, lname;
    bool isAdmin = true;

    cout << "Please enter a username for the new admin: ";
    cin >> username;

    // Check if the username already exists
    if (admins.find(username) != admins.end()) {
        cout << "Username already exists. Please choose another username." << endl;
        return;
    }

    cout << "Please enter a password for the new admin: ";
    cin >> password;

    cout << "Please enter the first name of the new admin: ";
    cin >> fname;

    cout << "Please enter the last name of the new admin: ";
    cin >> lname;

    // Create new admin and add to the map
    admins[username] = Admin(username, password, fname, lname, isAdmin);

    system("cls");
    cout << "New admin created successfully!" << endl;
    welcome_page_admin();
}

// Admin user management
void Admin::user_management() {
    char answer = 'y';
    int choice;

    cout << "\t***** User Management Portal *****\n" << endl;
    cout << "\t\t1. Create New User Account" << endl;
    cout << "\t\t2. Update User Account Information" << endl;
    cout << "\t\t3. Exit\n" << endl;

    cout << "Please Enter Your Choice: ";
    while (!(cin >> choice) || choice < 1 || choice > 3 || cin.peek() != '\n' || cin.peek() == '.') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number from 1 to 3: ";
    }

    switch (choice) {
    case 1:
        // Loop for creating multiple users
        while (answer == 'y' || answer == 'Y') {
            User::signup();
            cout << "Do you want to add more? (y / n) " << endl;
            cin >> answer;
        }
        system("cls");
        user_management();
        break;
    case 2:
        // Update user account
        system("cls");
        update_user_info();
        break;
    case 3:
        // Exit user management portal
        system("cls");
        cout << "\nLooking forward to seeing you again soon!\n\n" << endl;
        admin_menu();
        break;
    default: {
        system("cls");
        cout << "Invalid choice, try again!" << endl;
        user_management();
    }
    }
}

// Count total number of admins
int Admin::countAdmins() {
    int adminsCount = admins.size();
    return adminsCount;
}

// Welcome page for admin with signup and login options
void welcome_page_admin() {
    bool exitFlag = false;

    while (!exitFlag) {
        cout << "\t\t****** ADMIN PORTAL ******\n" << endl;
        cout << "\t\t\t1. Sign Up" << endl;
        cout << "\t\t\t2. Login" << endl;
        cout << "\t\t\t3. Exit\n" << endl;

        int choice;

        cout << "Please Enter Your Choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 3 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 3: ";
        }

        switch (choice) {
        case 1: {
            system("cls");
            Admin::signupAdmin();
            welcome_page_admin();
            break;
        }
        case 2: {
            system("cls");
            Admin::loginAdmin();
            break;
        }
        case 3: {
            // Exit
            exitFlag = true;
            system("cls");
            cout << "\nThank you, ADMIN! We look forward to seeing you again soon!\n\n" << endl;
            welcome_page();
            break;
        }
        }
    }
}
